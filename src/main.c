#include "commands.h"
#include "config.h"
#include "ring_buffer.h"
#include "uart_driver.h"
#include "utils.h"

#include <string.h>

static ring_buffer_t rb;
static char history_buffer[MAX_HISTORY][MAX_CMD_SIZE];

static void process_command(char *input) {
    if (input == NULL) return;

    char temp_input[MAX_CMD_SIZE];

    strncpy(temp_input, input, MAX_CMD_SIZE - 1);
    temp_input[MAX_CMD_SIZE - 1] = '\0';

    char *saveptr;
    char *temp_cmd = strtok_r(temp_input, " ", &saveptr);

    if (temp_cmd != NULL) {
        to_upper(temp_cmd);

        if (strcmp(temp_cmd, "HISTORY") != 0) {
            if (!rb_push(&rb, input)) {
                uart_print("Failed to write history\r\n");
            }
        }
    }

    char *command = strtok_r(input, " ", &saveptr);
    if (command == NULL) return;
    to_upper(command);

    char *args = strtok_r(NULL, "", &saveptr);

    for (size_t i = 0; i < TOTAL_COMMANDS; i++) {
        if (strcmp(command, commands[i].command) == 0) {
            commands[i].handler(args);
            return;
        }
    }

    uart_print("Invalid command\r\n");
}

void app_main(void) {
    uart_init();
    rb_init(&rb, history_buffer, MAX_HISTORY);

    commands_set_history(&rb);
    uart_print("\r\nSimple UART Shell\r\n");

    while (1) {
        uart_print("\r\n> ");
        char user_input[MAX_CMD_SIZE];

        if (!uart_read_line(user_input, MAX_CMD_SIZE)) {
            uart_print("Command too long\r\n");
            continue;
        }

        if (strlen(user_input) == 0) continue;
        process_command(user_input);
    }
}
