#ifndef _4_PER_CHANGE_H
#define _4_PER_CHANGE_H

#include <stdio.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_system.h"
#include "blinkPeriod.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_TX      (43)
#define GPIO_RX     (44)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)

bool cmp_buffer(char* prefix, uint8_t* buffer);
int uint8_t_to_int(uint8_t buf_element);
int data_period_to_ms(uint8_t* data_period);
void period_changer(void* params);
#endif