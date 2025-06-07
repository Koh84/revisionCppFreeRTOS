#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAX_TASKS 3
#define HIGHEST_PRIORITY (configMAX_PRIORITIES - 1)
#define LOW_PRIORITY 1

typedef struct {
    TaskHandle_t handle;
    TickType_t deadline;
    const char *name;
    TickType_t period;  // Task period in ticks
} TaskDeadline_t;

TaskDeadline_t tasks[MAX_TASKS];

// Forward declarations
void TaskFunction(void *pvParameters);
void EDF_Manager(void *pvParameters);

void app_main(void) {
    // Initialize tasks info
    tasks[0].name = "Task1";
    tasks[0].period = pdMS_TO_TICKS(200);
    tasks[1].name = "Task2";
    tasks[1].period = pdMS_TO_TICKS(350);
    tasks[2].name = "Task3";
    tasks[2].period = pdMS_TO_TICKS(500);

    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].deadline = xTaskGetTickCount() + tasks[i].period;
        xTaskCreate(TaskFunction, tasks[i].name, 2048, &tasks[i], LOW_PRIORITY, &tasks[i].handle);
    }

    // Create the EDF Manager task (highest priority)
    xTaskCreate(EDF_Manager, "EDF_Manager", 2048, NULL, HIGHEST_PRIORITY, NULL);
}

void TaskFunction(void *pvParameters) {
    TaskDeadline_t *taskInfo = (TaskDeadline_t *)pvParameters;
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1) {
        // Simulate work (e.g. 50 ms)
        printf("%s running at %u ms\n", taskInfo->name, (unsigned int)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(50));

        // Wait until next period (this updates lastWakeTime)
        vTaskDelayUntil(&lastWakeTime, taskInfo->period);

        // Update next deadline based on the updated lastWakeTime
        taskInfo->deadline = lastWakeTime + taskInfo->period;

        printf("%s updated deadline to %u ms\n", taskInfo->name, (unsigned int)(taskInfo->deadline * portTICK_PERIOD_MS));

        // Lower own priority to LOW_PRIORITY
        vTaskPrioritySet(NULL, LOW_PRIORITY);
    }
}

void EDF_Manager(void *pvParameters) {
    (void)pvParameters;
    while (1) {
        TickType_t now = xTaskGetTickCount();

        // Find task with earliest deadline
        int earliestIndex = -1;
        TickType_t earliestDeadline = 0xFFFFFFFF;

        for (int i = 0; i < MAX_TASKS; i++) {
            if (tasks[i].handle != NULL) {
                if (tasks[i].deadline >= now && tasks[i].deadline < earliestDeadline) {
                    earliestDeadline = tasks[i].deadline;
                    earliestIndex = i;
                }
            }
        }

        // Update priorities
        for (int i = 0; i < MAX_TASKS; i++) {
            if (tasks[i].handle != NULL) {
                if (i == earliestIndex) {
                    vTaskPrioritySet(tasks[i].handle, HIGHEST_PRIORITY - 1); // Just below Manager task
                } else {
                    vTaskPrioritySet(tasks[i].handle, LOW_PRIORITY);
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // Run manager every 100 ms
    }
}
