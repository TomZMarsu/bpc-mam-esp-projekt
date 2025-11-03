#include "6_rng.h"
#include <stdio.h>
#include "esp_random.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "bootloader_random.h"

static const char *TAG = "RND_NUMBERS";

void generate_random_number(void) {
    QueueHandle_t cmd_queue = get_random_queueHandle();

    while(1) {
        bool true_flag;
        if(xQueueReceive(cmd_queue, &true_flag, portMAX_DELAY)) {
            bootloader_random_enable();

            uint32_t random_high = esp_random();
            uint32_t random_low = esp_random();
            uint64_t random_num = ((uint64_t)random_high << 32) | random_low;
            ESP_LOGI(TAG, "ULOHA 6: Random number: 0x%016llX", random_num);

            bootloader_random_disable();
        }
    }
}
