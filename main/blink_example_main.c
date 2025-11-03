/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

// include vsech uloh
#include "1_blink/1_blink.h"
#include "2_wifi/2_wifi.h"
#include "3_ntp/3_ntp.h"

static const char *TAG = "example";

void app_main(void)
{
    // ULOHA 1: START
    xTaskCreate(blink_led, "u1_blink_led", 2048, NULL, 1, NULL);
    // ULOHA 1: KONEC 

    // ULOHA 2: START
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    init_wifi();
    // ULOHA 2: KONEC

    // ULOHA 3: START
    fetch_print_time();
    // ULOHA 3: KONEC
}
