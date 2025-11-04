#ifndef UART_COMMAND_HANDLER_H
#define UART_COMMAND_HANDLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "uart_commandHandler.h"
#include "esp_log.h"
#include <sys/time.h>
#include "esp_attr.h"

void unixtime_printer(void* params);
void time_sync_notification_cb(struct timeval *tv);
void obtain_time(void);
void initialize_sntp(void);
void fetch_print_epoch();

#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_CUSTOM
void sntp_sync_time(struct timeval *tv);
#endif

#endif