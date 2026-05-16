#include "uart_driver.h"
#include "config.h"

#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include <string.h>

void uart_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(UART_PORT, UART_BUF_SIZE, 0, 0, NULL, 0);
    uart_param_config(UART_PORT, &uart_config);

    uart_set_pin(
        UART_PORT,
        UART_TX_PIN,
        UART_RX_PIN,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    );
}

void uart_print(const char *str) {
    if (str == NULL) return;

    uart_write_bytes(UART_PORT, str, strlen(str));
}

bool uart_read_line(char *buffer, size_t max_len) {
    if (buffer == NULL || max_len == 0) return false;

    size_t pos = 0;
    uint8_t ch;
    bool overflow = false;

    while (1) {
        int len = uart_read_bytes(UART_PORT, &ch, 1, portMAX_DELAY);
        if (len <= 0) continue;

        if (ch == 27) {
            uint8_t seq[2];
            uart_read_bytes(UART_PORT, seq, 2, pdMS_TO_TICKS(10));
            continue;
        }

        if (ch == '\b' || ch == 127) {
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                uart_print("\b \b");
            }
            overflow = false;
            continue;
        }

        if (ch == '\n' || ch == '\r') {
            buffer[pos] = '\0';
            uart_print("\r\n");
            return !overflow;
        }

        if (ch < 32 || ch >= 127) continue;

        if (pos >= max_len - 1) {
            overflow = true;
            uart_write_bytes(UART_PORT, "\a", 1);
            continue;
        }

        buffer[pos++] = (char)ch;
        uart_write_bytes(UART_PORT, &ch, 1);
    }
}
