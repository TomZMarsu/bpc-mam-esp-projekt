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

// uloha 8 - logovani
#include "esp_log.h"

// include vsech uloh
#include "1_blink/1_blink.h"
#include "2_wifi/2_wifi.h"
#include "3_ntp/3_ntp.h"
#include "6_rng/6_rng.h"
#include "7_mac/7_mac.h"
#include "9_temp/9_temp.h"
#include "10_wave_gen/10_wave_gen.h"

#include "4_per_change/4_per_change.h"
#include "4_per_change/blinkPeriod.h"

static const char *TAG = "example";

void app_main(void)
{
    // ULOHA 8: LOGOVANI - Keep only our application logs
    // Note: Global esp_log_level_set("*", ESP_LOG_NONE) not needed - sdkconfig sets default to NONE
    
    // Enable logging ONLY for our own application tags
    esp_log_level_set("example", ESP_LOG_INFO);
    esp_log_level_set("blink", ESP_LOG_INFO);
    esp_log_level_set("APP_WIFI", ESP_LOG_INFO);  // Changed from "wifi" to avoid ESP-IDF wifi component conflict
    esp_log_level_set("ntp", ESP_LOG_INFO);
    esp_log_level_set("RND_NUMBERS", ESP_LOG_INFO);
    esp_log_level_set("unixtime", ESP_LOG_INFO);
    esp_log_level_set("sine_wave", ESP_LOG_INFO);
    esp_log_level_set("BASE_MAC", ESP_LOG_INFO);
    esp_log_level_set("temperature_sensor", ESP_LOG_INFO);
    esp_log_level_set("Uloha 4", ESP_LOG_INFO);
    esp_log_level_set("Uloha 5", ESP_LOG_INFO);

    // ULOHA 1: START
    initBlinkPeriod(1000);
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
    xTaskCreate(fetch_print_time, "u3_ntp", 2048, NULL, 1, NULL);
    // ULOHA 3: KONEC

    // ULOHA 5: START
    xTaskCreate(uart_commandHandler, "u5_uart_commandHandler", 2048, NULL, 1, NULL);
    // ULOHA 5: KONEC

    // ULOHA 7: START
    print_mac();
    // ULOHA 7: KONEC

    // ULOHA 10: START - Sine wave generation on GPIO17
    xTaskCreate(start_sine_wave_task, "u10_wave_gen", 4096, NULL, 5, NULL);
    // ULOHA 10: KONEC
}
