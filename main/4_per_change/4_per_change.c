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

void period_changer(void* params)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, GPIO_TX, GPIO_RX, ECHO_TEST_RTS, ECHO_TEST_CTS);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    esp_log_level_set("*", ESP_LOG_INFO);
    const int command_length = strlen("PER:xxx");

    while(1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);

        if(cmp_buffer("PER:", data) && command_length==len) {
            uint8_t data_period[3] = {data[4], data[5], data[6]};
            int new_period = data_period_to_ms(data_period);

            ESP_LOGI("Uloha 4: ", "Setting blink period to %d ms", new_period);
            setBlinkPeriod(new_period);
        }
    }

    vTaskDelete(NULL);
}