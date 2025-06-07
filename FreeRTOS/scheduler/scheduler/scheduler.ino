#include <Arduino.h>
#include <vector>
#include <functional>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/event_groups.h>

#define SCHEDULE_EVENT (1 << 0)

class Application {
public:
    Application() {
        mutex_ = xSemaphoreCreateMutex();
        event_group_ = xEventGroupCreate();
    }

    void Schedule(std::function<void()> task) {
        xSemaphoreTake(mutex_, portMAX_DELAY);
        main_tasks_.push_back(std::move(task));
        xSemaphoreGive(mutex_);
        xEventGroupSetBits(event_group_, SCHEDULE_EVENT);
    }

    void MainEventLoop() {
        while (true) {
            EventBits_t bits = xEventGroupWaitBits(event_group_, SCHEDULE_EVENT, pdTRUE, pdFALSE, portMAX_DELAY);
            if (bits & SCHEDULE_EVENT) {
                // Take mutex, move tasks out
                xSemaphoreTake(mutex_, portMAX_DELAY);
                std::vector<std::function<void()>> tasks = std::move(main_tasks_);
                main_tasks_.clear();  // just to be safe
                xSemaphoreGive(mutex_);

                // Run all scheduled tasks
                for (auto& task : tasks) {
                    task();
                }
            }
        }
    }

private:
    std::vector<std::function<void()>> main_tasks_;
    SemaphoreHandle_t mutex_;
    EventGroupHandle_t event_group_;
};

Application app;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Schedule 3 simple tasks
    app.Schedule([]() { Serial.println("Task 1 running"); });
    app.Schedule([]() { Serial.println("Task 2 running"); });
    app.Schedule([]() { Serial.println("Task 3 running"); });

    // Start the main event loop as a FreeRTOS task
    xTaskCreate(
        [](void*) {
            app.MainEventLoop();
        },
        "MainLoopTask", 4096, nullptr, 1, nullptr);
}

void loop() {
    // empty loop - all logic is in FreeRTOS tasks
}
