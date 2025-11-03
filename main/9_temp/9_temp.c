#include "9_temp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"

static const char *TAG = "example";

void measure_temp()
{
    QueueHandle_t cmd_queue = get_temperature_queueHandle();

    // Install and enable temperature sensor once at startup
    temperature_sensor_handle_t temp_sensor = NULL;
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor_config, &temp_sensor));
    ESP_ERROR_CHECK(temperature_sensor_enable(temp_sensor));

    while(1) {
        bool true_flag;
        
        if(xQueueReceive(cmd_queue, &true_flag, portMAX_DELAY)) {
            float tsens_value;
            ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_sensor, &tsens_value));
            float temp_f = 9.0/5.0 * tsens_value + 32;
            ESP_LOGI(TAG, "ULOHA 9: %.02f ℃\t%.02f F", tsens_value, temp_f);
        }
    }
}