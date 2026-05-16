#include "ring_buffer.h"
#include "uart_driver.h"

#include <string.h>

void rb_init(
    ring_buffer_t *rb,
    char buffer[][MAX_CMD_SIZE],
    size_t max_commands
) {
    if (rb == NULL || buffer == NULL) return;

    rb->buffer = buffer;
    rb->read_ptr = buffer;
    rb->write_ptr = buffer;
    rb->count = 0;
    rb->max_commands = max_commands;
}

bool rb_push(ring_buffer_t *rb, const char *command) {
    if (rb == NULL || command == NULL) return false;

    strncpy(*rb->write_ptr, command, MAX_CMD_SIZE - 1);

    (*rb->write_ptr)[MAX_CMD_SIZE - 1] = '\0';
    rb->write_ptr++;

    if (rb->write_ptr >= rb->buffer + rb->max_commands) rb->write_ptr = rb->buffer;

    if (rb->count < rb->max_commands) rb->count++;
    else {
        rb->read_ptr++;
        if (rb->read_ptr >= rb->buffer + rb->max_commands) rb->read_ptr = rb->buffer;
    }
    return true;
}

void rb_print(ring_buffer_t *rb) {
    if (rb == NULL || rb->count == 0) {
        uart_print("\r\nNo command history available.\r\n");
        return;
    }

    uart_print("\r\nCommand History:\r\n");

    char (*ptr)[MAX_CMD_SIZE] = rb->read_ptr;
    char num_buf[8];

    for (size_t i = 0; i < rb->count; i++) {
        snprintf(num_buf, sizeof(num_buf), "%d: ", (int)(i + 1));

        uart_print(num_buf);
        uart_print(*ptr);
        uart_print("\r\n");

        ptr++;

        if (ptr >= rb->buffer + rb->max_commands) ptr = rb->buffer;
    }
}
