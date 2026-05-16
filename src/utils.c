#include "utils.h"

#include <ctype.h>

void to_upper(char *str) {
    if (str == NULL)
        return;

    while (*str != '\0') {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}
