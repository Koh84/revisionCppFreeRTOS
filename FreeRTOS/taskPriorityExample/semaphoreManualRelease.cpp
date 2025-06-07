#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t binarySemaphore;

void Task1(void* pvParameters) {
    while (1) {
        printf("Task1: Waiting for semaphore...\n");
        if (xSemaphoreTake(binarySemaphore, portMAX_DELAY) == pdTRUE) {
            printf("Task1: Got semaphore, using resource...\n");
            vTaskDelay(pdMS_TO_TICKS(1000));  // Simulate resource usage
            printf("Task1: Releasing semaphore.\n");
            xSemaphoreGive(binarySemaphore);  // Release semaphore after done
        }
        vTaskDelay(pdMS_TO_TICKS(500));  // Some delay before next attempt
    }
}

void Task2(void* pvParameters) {
    while (1) {
        printf("Task2: Waiting for semaphore...\n");
        if (xSemaphoreTake(binarySemaphore, portMAX_DELAY) == pdTRUE) {
            printf("Task2: Got semaphore, using resource...\n");
            vTaskDelay(pdMS_TO_TICKS(500));  // Simulate resource usage
            printf("Task2: Releasing semaphore.\n");
            xSemaphoreGive(binarySemaphore);  // Release semaphore after done
        }
        vTaskDelay(pdMS_TO_TICKS(700));  // Some delay before next attempt
    }
}

void app_main() {
    // Create binary semaphore, initially "given" (available)
    binarySemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(binarySemaphore);  // Make it available initially

    xTaskCreate(Task1, "Task1", 2048, NULL, 2, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 2, NULL);
}
