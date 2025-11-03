#include "unixtime.h"

void unixtime_printer(void* params) {
    QueueHandle_t cmd_queue = get_unixtime_queueHandle();

    while(1) {
        bool true_flag;
        if(xQueueReceive(cmd_queue, &true_flag, portMAX_DELAY)) {
            ESP_LOGI("Uloha 5", "Prikaz UNIXTIME zavolan");
        }
    }

    vTaskDelete(NULL);
}