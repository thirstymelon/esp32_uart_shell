#pragma once

#include "config.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char (*buffer)[MAX_CMD_SIZE];
    char (*read_ptr)[MAX_CMD_SIZE];
    char (*write_ptr)[MAX_CMD_SIZE];
    size_t count;
    size_t max_commands;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb, char buffer[][MAX_CMD_SIZE],
             size_t max_commands);

bool rb_push(ring_buffer_t *rb, const char *command);
void rb_print(ring_buffer_t *rb);
