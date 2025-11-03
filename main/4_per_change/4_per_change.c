#include "4_per_change.h"

bool cmp_buffer(char* prefix, uint8_t* buffer) {
    int prefix_len = strlen(prefix);

    for(int i = 0; i < prefix_len; i++) {
        if((char) buffer[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

int uint8_t_to_int(uint8_t buf_element) {
    return (int) buf_element - '0';
}

int data_period_to_ms(uint8_t* data_period) {
    return uint8_t_to_int(data_period[0])*10000 + uint8_t_to_int(data_period[1])*1000 + uint8_t_to_int(data_period[2])*100;
}

void period_changer(void* params) {
    QueueHandle_t cmd_queue = get_per_queueHandle();

    while(1) {
        int new_period;
        if(xQueueReceive(cmd_queue, &new_period, portMAX_DELAY)) {
            ESP_LOGI("Uloha 4", "Nastavovani nove periody pro blikani: %d", new_period);
            setBlinkPeriod(new_period);
        }
    }
}