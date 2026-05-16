#pragma once

#include "driver/gpio.h"
#include "driver/uart.h"

#define VERSION "1.0.0"

#define UART_PORT UART_NUM_0
#define UART_BAUDRATE 115200

#define UART_TX_PIN GPIO_NUM_1
#define UART_RX_PIN GPIO_NUM_3

#define UART_BUF_SIZE 512

#define MAX_CMD_SIZE 128
#define MAX_HISTORY 20
