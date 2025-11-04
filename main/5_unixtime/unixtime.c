#include "unixtime.h"
#include "../3_ntp/3_ntp.h"

static const char *TAG = "unixtime";

void fetch_print_epoch() {
    time_t now;
    struct tm timeinfo;

    fetch_time(&now, &timeinfo);
    
    ESP_LOGI(TAG, "ULOHA 5: Unix epoch time: %ld", (long)now);
}

void unixtime_printer(void* params) {
    QueueHandle_t cmd_queue = get_unixtime_queueHandle();

    while(1) {
        bool true_flag;
        if(xQueueReceive(cmd_queue, &true_flag, portMAX_DELAY)) {
            fetch_print_epoch();
        }
    }

    vTaskDelete(NULL);
}