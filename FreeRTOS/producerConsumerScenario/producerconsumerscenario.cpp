/*
A Producer-Consumer scenario is a classic design pattern in concurrent programming where:

Producer(s): Generate data/items and put them into a shared resource (like a buffer or queue).

Consumer(s): Take data/items from that shared resource and process them.

Why is it important?
It decouples data production from consumption.

Producers and consumers can run at different speeds.

It requires careful synchronization to avoid issues like:

Race conditions (corrupting shared data)

Deadlocks

Data loss or overflow

*/
QueueHandle_t queue;

void ProducerTask(void *pvParameters) {
    int count = 0;
    while (1) {
        xQueueSend(queue, &count, portMAX_DELAY);
        count++;
        vTaskDelay(pdMS_TO_TICKS(100)); // simulate work
    }
}

void ConsumerTask(void *pvParameters) {
    int received;
    while (1) {
        if (xQueueReceive(queue, &received, portMAX_DELAY)) {
            printf("Consumed: %d\n", received);
        }
    }
}

void app_main() {
    queue = xQueueCreate(10, sizeof(int));
    xTaskCreate(ProducerTask, "Producer", 2048, NULL, 2, NULL);
    xTaskCreate(ConsumerTask, "Consumer", 2048, NULL, 2, NULL);
}
