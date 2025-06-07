#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <functional>

// Define the type for our tasks (void functions with no params)
using TaskFunction = std::function<void()>;

// Queue handle
QueueHandle_t taskQueue;

// Maximum number of tasks in queue
const int MAX_TASKS = 10;

// Worker task function
void WorkerTask(void* param) {
  while (true) {
    TaskFunction task;

    // Wait indefinitely for a task to be available
    if (xQueueReceive(taskQueue, &task, portMAX_DELAY) == pdTRUE) {
      // Execute the task
      task();
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Create queue to hold task functions
  taskQueue = xQueueCreate(MAX_TASKS, sizeof(TaskFunction));

  if (taskQueue == NULL) {
    Serial.println("Failed to create task queue");
    while (true) {}
  }

  // Create 2 worker tasks pinned to different cores
  xTaskCreatePinnedToCore(WorkerTask, "Worker1", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(WorkerTask, "Worker2", 4096, NULL, 1, NULL, 1);

  // Schedule 3 example tasks:
  TaskFunction task1 = []() { Serial.println("Task 1 running"); };
  TaskFunction task2 = []() { Serial.println("Task 2 running"); };
  TaskFunction task3 = []() { Serial.println("Task 3 running"); };

  // Enqueue tasks
  xQueueSend(taskQueue, &task1, portMAX_DELAY);
  xQueueSend(taskQueue, &task2, portMAX_DELAY);
  xQueueSend(taskQueue, &task3, portMAX_DELAY);
}

void loop() {
  // Nothing here, workers handle tasks
}
