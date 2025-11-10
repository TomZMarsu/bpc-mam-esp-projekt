/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#ifndef SINE_WAVE_GEN_H
#define SINE_WAVE_GEN_H

/**
 * @brief Start sine wave generation task on GPIO17
 *        Generates 50 Hz sine wave with maximum amplitude (255)
 *        Uses DMA for efficient continuous output
 *
 * @param params Unused (required for FreeRTOS task)
 */
void start_sine_wave_task(void *params);

#endif // SINE_WAVE_GEN_H