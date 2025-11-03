#ifndef BLINK_H
#define BLINK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void configure_led(void);
void blink_led(void* params);

#endif // BLINK_H

