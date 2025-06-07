// When to use Event Groups?
// When you want a task to wait for one or more events (bits) to be set before proceeding.

// When multiple tasks or ISRs can set different event bits.

// When you want to wait for any or all of several event bits.

// When you want to efficiently manage multiple flags in a single variable.


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define SENSOR1_READY_BIT   (1 << 0)
#define SENSOR2_READY_BIT   (1 << 1)

EventGroupHandle_t sensorEventGroup;

void Sensor1Task(void *pvParameters) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate sensor 1 work
        printf("Sensor1: Ready\n");
        xEventGroupSetBits(sensorEventGroup, SENSOR1_READY_BIT);
    }
}

void Sensor2Task(void *pvParameters) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1500)); // Simulate sensor 2 work
        printf("Sensor2: Ready\n");
        xEventGroupSetBits(sensorEventGroup, SENSOR2_READY_BIT);
    }
}

void ProcessorTask(void *pvParameters) {
    EventBits_t uxBits;
    while (1) {
        // Wait for both SENSOR1_READY_BIT and SENSOR2_READY_BIT to be set
        uxBits = xEventGroupWaitBits(
            sensorEventGroup,
            SENSOR1_READY_BIT | SENSOR2_READY_BIT,
            pdTRUE,  // Clear bits on exit
            pdTRUE,  // Wait for all bits
            portMAX_DELAY);

        if ((uxBits & (SENSOR1_READY_BIT | SENSOR2_READY_BIT)) == 
            (SENSOR1_READY_BIT | SENSOR2_READY_BIT)) {
            printf("Processor: Both sensors ready, processing data...\n");
            vTaskDelay(pdMS_TO_TICKS(500));  // Simulate processing time
        }
    }
}

void app_main(void) {
    sensorEventGroup = xEventGroupCreate();

    xTaskCreate(Sensor1Task, "Sensor1", 2048, NULL, 1, NULL);
    xTaskCreate(Sensor2Task, "Sensor2", 2048, NULL, 1, NULL);
    xTaskCreate(ProcessorTask, "Processor", 2048, NULL, 2, NULL);
}
