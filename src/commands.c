#include "commands.h"
#include "config.h"
#include "ring_buffer.h"
#include "uart_driver.h"

#include <stdio.h>

static ring_buffer_t *history_rb = NULL;

const user_command_t commands[] = {
    {"GREET", greet, "Greets the user\r\n"},
    {"VERSION", version, "Gets version\r\n"},
    {"HISTORY", history, "Prints command history\r\n"},
    {"HELP", help, "Prints all commands\r\n"}
};
const size_t TOTAL_COMMANDS = sizeof(commands) / sizeof(commands[0]);

void commands_set_history(void *rb) {
    history_rb = (ring_buffer_t *)rb;
}

void greet(char *args) {
    (void)args;
    uart_print("\r\nHello, User!\r\n");
}

void version(char *args) {
    (void)args;

    uart_print("\r\nVersion: ");
    uart_print(VERSION);
    uart_print("\r\n");
}

void history(char *args) {
    (void)args;
    rb_print(history_rb);
}

void help(char *args) {
    (void)args;

    uart_print("\r\nAvailable Commands:\r\n\r\n");
    char line[64];

    for (size_t i = 0; i < TOTAL_COMMANDS; i++) {
        snprintf(
            line,
            sizeof(line),
            "%-*s : %s",
            10,
            commands[i].command,
            commands[i].description
        );

        uart_print(line);
    }
}
