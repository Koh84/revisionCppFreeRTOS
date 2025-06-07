#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"

#define NUM_WORKER_TASKS 4

TaskHandle_t taskHandles[NUM_WORKER_TASKS]; // 0: B, 1: C, 2: D, 3: E
SemaphoreHandle_t workSemaphore;

void doWork(const char *taskName) {
    printf("%s: Working...\n", taskName);
    vTaskDelay(pdMS_TO_TICKS(10));  // Simulate work for 10 ms
}

void WorkerTask(void *pvParameters) {
    const char *taskName = (const char *)pvParameters;

    while (1) {
        // Wait for notification from dispatcher
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        doWork(taskName);
    }
}

void DispatcherTask(void *pvParameters) {
    int nextOtherIndex = 1;  // Start with TaskC (index 1)
    bool notifyBNext = true;

    while (1) {
        // Wait for ISR to give semaphore indicating work available
        xSemaphoreTake(workSemaphore, portMAX_DELAY);

        if (notifyBNext) {
            xTaskNotifyGive(taskHandles[0]); // Notify TaskB
            notifyBNext = false;
        } else {
            xTaskNotifyGive(taskHandles[nextOtherIndex]); // Notify C, D, or E

            nextOtherIndex++;
            if (nextOtherIndex >= NUM_WORKER_TASKS) {
                nextOtherIndex = 1;   // Wrap to TaskC
                notifyBNext = true;   // Next round starts with TaskB
            }
        }
    }
}

// Simulated ISR - gives 4 semaphores indicating 4 work units available
void IRAM_ATTR timer_isr_simulator() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    for (int i = 0; i < 4; i++) {
        xSemaphoreGiveFromISR(workSemaphore, &xHigherPriorityTaskWoken);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void app_main() {
    workSemaphore = xSemaphoreCreateCounting(10, 0);

    // Create worker tasks: B, C, D, E
    xTaskCreate(WorkerTask, "TaskB", 2048, "TaskB", 3, &taskHandles[0]); // Highest priority
    xTaskCreate(WorkerTask, "TaskC", 2048, "TaskC", 2, &taskHandles[1]);
    xTaskCreate(WorkerTask, "TaskD", 2048, "TaskD", 2, &taskHandles[2]);
    xTaskCreate(WorkerTask, "TaskE", 2048, "TaskE", 2, &taskHandles[3]);

    // Create dispatcher task (priority 4, highest to ensure quick dispatch)
    xTaskCreate(DispatcherTask, "Dispatcher", 2048, NULL, 4, NULL);

    // Simulate ISR triggering after some delay
    vTaskDelay(pdMS_TO_TICKS(1000));
    timer_isr_simulator();  // Give 4 semaphores, starts notification sequence

    // Keep main task alive
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
