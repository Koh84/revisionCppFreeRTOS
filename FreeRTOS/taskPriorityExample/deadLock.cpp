/*
2. Deadlock
What it is:
A deadlock happens when two or more tasks wait indefinitely for each other to release resources. None can proceed because each one holds a resource the other needs.

Why it’s bad:
The involved tasks get stuck forever, halting part of the system.

Example:
Task A holds Mutex 1 and waits for Mutex 2. Task B holds Mutex 2 and waits for Mutex 1. Both wait forever.

How to fix this deadlock?
The fundamental fix is to avoid circular wait by enforcing a consistent locking order. Both tasks must acquire the mutexes in the same order every time.

void TaskA(void *pvParameters) {
    while (1) {
        xSemaphoreTake(mutex1, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(10));  // Simulate work

        printf("TaskA waiting for mutex2\n");
        xSemaphoreTake(mutex2, portMAX_DELAY);  // Now safe: always acquire mutex1 first

        printf("TaskA got mutex2\n");

        xSemaphoreGive(mutex2);
        xSemaphoreGive(mutex1);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TaskB(void *pvParameters) {
    while (1) {
        // Lock mutex1 first, then mutex2 (same order as TaskA)
        xSemaphoreTake(mutex1, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(10));  // Simulate work

        printf("TaskB waiting for mutex2\n");
        xSemaphoreTake(mutex2, portMAX_DELAY);

        printf("TaskB got mutex2\n");

        xSemaphoreGive(mutex2);
        xSemaphoreGive(mutex1);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <stdio.h>

SemaphoreHandle_t mutex1, mutex2;

void TaskA(void *pvParameters) {
    while (1) {
        xSemaphoreTake(mutex1, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(10));  // Simulate work

        printf("TaskA waiting for mutex2\n");
        xSemaphoreTake(mutex2, portMAX_DELAY);  // Deadlock here if TaskB holds mutex2
        printf("TaskA got mutex2\n");

        xSemaphoreGive(mutex2);
        xSemaphoreGive(mutex1);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TaskB(void *pvParameters) {
    while (1) {
        xSemaphoreTake(mutex2, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(10));  // Simulate work

        printf("TaskB waiting for mutex1\n");
        xSemaphoreTake(mutex1, portMAX_DELAY);  // Deadlock here if TaskA holds mutex1
        printf("TaskB got mutex1\n");

        xSemaphoreGive(mutex1);
        xSemaphoreGive(mutex2);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main() {
    mutex1 = xSemaphoreCreateMutex();
    mutex2 = xSemaphoreCreateMutex();

    xTaskCreate(TaskA, "TaskA", 2048, NULL, 1, NULL);
    xTaskCreate(TaskB, "TaskB", 2048, NULL, 1, NULL);
}
