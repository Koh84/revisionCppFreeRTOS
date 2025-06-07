/*
1. Race Condition
What it is:
A race condition occurs when two or more tasks or threads access shared data at the same time without proper synchronization, and the final outcome depends on the unpredictable order in which the accesses happen.

Why it’s bad:
The shared data can become corrupted or inconsistent because the tasks interfere with each other.

Example:
Two tasks incrementing the same counter variable without a mutex—both read the same value before incrementing, leading to lost updates.
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

int sharedCounter = 0;

void Task1(void *pvParameters) {
    while (1) {
        int temp = sharedCounter;   // Read
        temp++;                     // Increment
        vTaskDelay(pdMS_TO_TICKS(10)); // Simulate context switch here
        sharedCounter = temp;       // Write back
        printf("Task1 incremented to %d\n", sharedCounter);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void Task2(void *pvParameters) {
    while (1) {
        int temp = sharedCounter;   // Read
        temp++;                     // Increment
        vTaskDelay(pdMS_TO_TICKS(10)); // Simulate context switch here
        sharedCounter = temp;       // Write back
        printf("Task2 incremented to %d\n", sharedCounter);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void app_main() {
    xTaskCreate(Task1, "Task1", 2048, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 1, NULL);
}
