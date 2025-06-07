#include "esp_task_wdt.h"

typedef struct {
    char device[32];
    char data[32];
    int a;
} I2CRequest_t;

#define I2C_QUEUE_LEN 10
QueueHandle_t i2cQueue;

void setup() {
  esp_task_wdt_init(50, true);
  esp_task_wdt_add(NULL);

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(__FILE__ __DATE__);

  i2cQueue = xQueueCreate(I2C_QUEUE_LEN, sizeof(I2CRequest_t));
  if (i2cQueue == NULL) {
    Serial.println("Queue creation failed!");
    while (1); // Halt
  }
  xTaskCreate(I2CTask, "I2CTask", 4096, NULL, 3, NULL);
  xTaskCreate(TaskA, "TaskA", 2048, NULL, 2, NULL);
  xTaskCreate(TaskB, "TaskB", 2048, NULL, 2, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void i2c_write(const char *device, const char *data, int a) {
    printf("I2C -> Device: %s, Data: %s, a: %d\n", device, data, a);
    vTaskDelay(pdMS_TO_TICKS(20)); // Simulate delay
}

void I2CTask(void *pvParameters) {
    esp_task_wdt_add(NULL); 
    I2CRequest_t req;
    while (1) {
        if (xQueueReceive(i2cQueue, &req, portMAX_DELAY)) {
            // Process one I2C request at a time
            i2c_write(req.device, req.data, req.a);
        }
    }
}

void TaskA(void *pvParameters) {
    esp_task_wdt_add(NULL); 
    while (1) {
        I2CRequest_t req;
        strcpy(req.device, "SensorA");
        strcpy(req.data, "ReadTemp");
        req.a = 1;
        Serial.printf("TaskA sending at %lu ms\n", millis());
        xQueueSend(i2cQueue, &req, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void TaskB(void *pvParameters) {
    esp_task_wdt_add(NULL); 
    while (1) {
        I2CRequest_t req;
        strcpy(req.device, "SensorB");
        strcpy(req.data, "WriteConfig");
        req.a = 2;

        xQueueSend(i2cQueue, &req, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}