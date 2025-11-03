#ifndef NTP_H
#define NTP_H

#include <sys/time.h>
#include "esp_attr.h"

/* Variable holding number of times ESP32 restarted since first boot.
 * It is placed into RTC memory using RTC_DATA_ATTR and
 * maintains its value when ESP32 wakes from deep sleep.
 */
extern RTC_DATA_ATTR int boot_count;

void time_sync_notification_cb(struct timeval *tv);
void obtain_time(void);
void initialize_sntp(void);
void fetch_print_time();

#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_CUSTOM
void sntp_sync_time(struct timeval *tv);
#endif

#endif // NTP_H
