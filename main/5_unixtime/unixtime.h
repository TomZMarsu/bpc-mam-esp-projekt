#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "uart_commandHandler.h"
#include "esp_log.h"

void unixtime_printer(void* params);

#endif