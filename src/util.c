#include <ctype.h>

#include "util.h"

int max(int a, int b) {
    if (a > b) {
        return a;
    }else if (b > a) {
        return b;
    }
    return a;
}

int is_string_empty(char *string) {
    while (*string != '\0') {
        if (!isspace(*string)) {
            return 0;
        }
        string++;
    }
    return 1;
}
