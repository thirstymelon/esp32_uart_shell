#pragma once

#include <stddef.h>

typedef struct {
    const char *command;
    void (*handler)(char *args);
    const char *description;
} user_command_t;

extern const user_command_t commands[];
extern const size_t TOTAL_COMMANDS;

void greet(char *args);
void version(char *args);
void history(char *args);
void help(char *args);

void commands_set_history(void *history_rb);
