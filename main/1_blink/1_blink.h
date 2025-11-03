#ifndef BLINK_H
#define BLINK_H
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "blinkPeriod.h"

void configure_led(void);
void blink_led(void* params);

#endif // BLINK_H

