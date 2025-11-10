/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac_continuous.h"
#include "esp_log.h"
#include "10_wave_gen.h"

static const char *TAG = "sine_wave";

#define DAC_CONVERSION_FREQ_HZ    20000  // 20 kHz conversion frequency
#define SINE_WAVE_FREQ_HZ         50     // 50 Hz sine wave frequency
#define WAVE_ARRAY_LEN            400    // Number of samples per cycle
#define DAC_AMPLITUDE             255    // Maximum amplitude (8-bit DAC)

static uint8_t sin_wav[WAVE_ARRAY_LEN];  // Sine wave sample buffer

static void generate_sine_wave(void)
{
    for (int i = 0; i < WAVE_ARRAY_LEN; i++) {
        // Generate sine wave: sin(2π * i / N) scaled to 0-255
        sin_wav[i] = (uint8_t)((sin(i * 2 * M_PI / WAVE_ARRAY_LEN) + 1) * DAC_AMPLITUDE / 2);
    }
}

void start_sine_wave_task(void *params)
{
    ESP_LOGI(TAG, "Generating sine wave samples...");
    generate_sine_wave();
    
    ESP_LOGI(TAG, "Configuring DAC on GPIO17...");
    dac_continuous_handle_t dac_handle;
    dac_continuous_config_t cont_cfg = {
        .chan_mask = DAC_CHANNEL_MASK_CH0,  // GPIO17 on ESP32-S2
        .desc_num = 4,
        .buf_size = 2048,
        .freq_hz = DAC_CONVERSION_FREQ_HZ,
        .offset = 0,
        .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
        .chan_mode = DAC_CHANNEL_MODE_ALTER,
    };
    
    ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &dac_handle));
    ESP_ERROR_CHECK(dac_continuous_enable(dac_handle));

    // Continuously output sine wave via DMA
    while (1) {
        ESP_ERROR_CHECK(dac_continuous_write(dac_handle, sin_wav, WAVE_ARRAY_LEN, NULL, -1));
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

