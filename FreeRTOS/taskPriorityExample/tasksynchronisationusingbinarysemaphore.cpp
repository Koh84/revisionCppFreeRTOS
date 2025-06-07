/*
why don't we use task notification instead? like xTaskNotifyGive and ulTaskNotifyTake

Great question! Using task notifications instead of binary semaphores for synchronization in FreeRTOS is often recommended because:

Advantages of Task Notifications over Binary Semaphores
Lower overhead:
Task notifications are built into the task control block itself, so they don’t require separate memory allocation like semaphores. This makes them very lightweight and fast.

Simpler API:
Functions like xTaskNotifyGive() and ulTaskNotifyTake() are simpler to use when you just want to signal one task.

Direct to the task:
Task notifications send directly to a specific task handle, so you don’t have to manage semaphore handles and create semaphore objects.

Better performance:
Since task notifications avoid kernel objects and queues, they typically have lower latency.

When to use binary semaphore instead?
You want to synchronize multiple tasks or multiple event producers (task notifications are one-to-one).

You want to share the semaphore between ISRs and tasks, and potentially multiple tasks wait on the same semaphore.

You want to use semaphore features like priority inheritance (with mutexes).

Or if your design or existing codebase already uses semaphores.

// Task 1
void Task1(void *pvParameters) {
    while (1) {
        printf("Task1: Waiting for notification...\n");
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Task1: Got notification! Doing work...\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Task 2
void Task2(void *pvParameters) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task2: Notifying Task1...\n");
        xTaskNotifyGive(task1Handle);
    }
}

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t syncSemaphore;

void Task1(void *pvParameters) {
    while (1) {
        printf("Task1: Waiting for semaphore...\n");
        // Wait indefinitely for semaphore from Task2
        if (xSemaphoreTake(syncSemaphore, portMAX_DELAY) == pdTRUE) {
            printf("Task1: Got semaphore! Doing work...\n");
            // Simulate some work
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

void Task2(void *pvParameters) {
    while (1) {
        // Wait for 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task2: Giving semaphore...\n");
        xSemaphoreGive(syncSemaphore);  // Signal Task1 to run
    }
}

void app_main() {
    // Create a binary semaphore
    syncSemaphore = xSemaphoreCreateBinary();

    if (syncSemaphore == NULL) {
        printf("Failed to create semaphore!\n");
        return;
    }

    // Create two tasks
    xTaskCreate(Task1, "Task1", 2048, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 1, NULL);
}
