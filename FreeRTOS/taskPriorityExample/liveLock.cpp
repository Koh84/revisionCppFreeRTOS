/*
3. Livelock
What it is:
A livelock is similar to deadlock in that tasks can’t make progress, but here the tasks keep actively changing their state in response to each other without making useful progress.

Why it’s bad:
Tasks are not blocked but still cannot complete their work, wasting CPU time.

Example:
Two tasks repeatedly detect a conflict and keep backing off and retrying without ever succeeding.
Fix:
Add a small delay (vTaskDelay) in the else branch, so the tasks back off and let the other task complete:

c
Copy
Edit
else {
    vTaskDelay(pdMS_TO_TICKS(1)); // backoff to avoid livelock
}

*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <stdio.h>

SemaphoreHandle_t xMutex;

void TaskA(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xMutex, (TickType_t)0) == pdTRUE) {
            printf("TaskA: Got the mutex\n");
            // Simulate some work
            vTaskDelay(pdMS_TO_TICKS(10));
            xSemaphoreGive(xMutex);
        } else {
            // No delay here → TaskA will try again immediately
            printf("TaskA: Failed to get mutex, retrying immediately\n");
        }
    }
}

void TaskB(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xMutex, (TickType_t)0) == pdTRUE) {
            printf("TaskB: Got the mutex\n");
            // Simulate some work
            vTaskDelay(pdMS_TO_TICKS(10));
            xSemaphoreGive(xMutex);
        } else {
            // No delay here → TaskB will try again immediately
            printf("TaskB: Failed to get mutex, retrying immediately\n");
        }
    }
}

void app_main() {
    xMutex = xSemaphoreCreateMutex();

    xTaskCreate(TaskA, "TaskA", 2048, NULL, 1, NULL);
    xTaskCreate(TaskB, "TaskB", 2048, NULL, 1, NULL);
}
