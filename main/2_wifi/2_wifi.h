#ifndef WIFI_H
#define WIFI_H

#include "esp_event.h"
#include "freertos/event_groups.h"

void eh_wifi_init(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void eh_set_device_ip(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void init_wifi(void);

#endif // WIFI_H
