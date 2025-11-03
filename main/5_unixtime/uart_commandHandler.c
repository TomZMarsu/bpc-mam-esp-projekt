#include "uart_commandHandler.h"

static QueueHandle_t per_queueHandle;
static QueueHandle_t unixtime_queueHandle;
static QueueHandle_t random_queueHandle;
static QueueHandle_t temperature_queueHandle;

QueueHandle_t get_per_queueHandle() {
    return per_queueHandle;
}

QueueHandle_t get_unixtime_queueHandle() {
    return unixtime_queueHandle;
}

QueueHandle_t get_random_queueHandle() {
    return random_queueHandle;
}

QueueHandle_t get_temperature_queueHandle() {
    return temperature_queueHandle;
}

void init_uart() {
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

    esp_log_level_set("*", ESP_LOG_INFO);
}

void init_command_queues() {
    // xQueueCreate(QUEUE_SIZE, size of queue element)
    per_queueHandle = xQueueCreate(COMMAND_QUEUE_SIZE, sizeof(int));
    unixtime_queueHandle = xQueueCreate(COMMAND_QUEUE_SIZE, sizeof(bool));
    random_queueHandle = xQueueCreate(COMMAND_QUEUE_SIZE, sizeof(bool));
    temperature_queueHandle = xQueueCreate(COMMAND_QUEUE_SIZE, sizeof(bool));
}

void init_command_tasks() {
    xTaskCreate(period_changer, "u4_period_changer", 2048, NULL, 1, NULL);
    xTaskCreate(unixtime_printer, "u5_unixtime_printer", 2048, NULL, 1, NULL);
    xTaskCreate(generate_random_number, "u6_rng", 2048, NULL, 1, NULL);
}

bool isThatCommand(char* commandName, uint8_t* buf, int buf_len) {
    return cmp_buffer(commandName, buf) && strlen(commandName)==buf_len;
}

void uart_commandHandler(void* params) {
    init_uart();
    init_command_queues();
    init_command_tasks();

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    const int period_command_length = strlen("PER:xxx");
    const bool true_flag = true;

    while(1) {
        int len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 20 / portTICK_PERIOD_MS);

        if(cmp_buffer("PER:", data) && period_command_length==len) {
            uint8_t data_period[3] = {data[4], data[5], data[6]};
            int new_period = data_period_to_ms(data_period);
            ESP_LOGI("Uloha 5", "Prikaz UNIXTIME zavolan");
            xQueueSend(per_queueHandle, &new_period, portMAX_DELAY);
        } else if (isThatCommand("UNIXTIME?", data, len)) {
            xQueueSend(unixtime_queueHandle, &true_flag, portMAX_DELAY);
        } else if (isThatCommand("RANDOM?", data, len)) {
            xQueueSend(random_queueHandle, &true_flag, portMAX_DELAY);
        } else if (isThatCommand("TEMPERATURE?", data, len)) {
            xQueueSend(temperature_queueHandle, &true_flag, portMAX_DELAY);
        }
        
    }

    vTaskDelete(NULL);
}