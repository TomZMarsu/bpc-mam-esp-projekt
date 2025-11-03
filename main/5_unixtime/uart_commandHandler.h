#ifndef _UART_COMMAND_HANDLER_H
#define _UART_COMMAND_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "unixtime.h"
#include "../4_per_change/4_per_change.h"

#define COMMAND_QUEUE_SIZE 3
#define GPIO_TX      (43)
#define GPIO_RX     (44)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)


QueueHandle_t get_per_queueHandle();
QueueHandle_t get_unixtime_queueHandle();
QueueHandle_t get_random_queueHandle();
QueueHandle_t get_temperature_queueHandle();
void init_uart();
void init_command_queues();
void init_command_tasks();
void uart_commandHandler(void* params);

#endif