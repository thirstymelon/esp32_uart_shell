#pragma once

#include <stdbool.h>
#include <stddef.h>

void uart_init(void);
void uart_print(const char *str);
bool uart_read_line(char *buffer, size_t max_len);
