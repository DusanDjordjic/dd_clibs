#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "io.h"

char* io_getnstr(unsigned int n)
{
    // Add + 1 because fgets reads one less char and adds '\0'
    char* buffer = malloc(sizeof(char) * (n + 1));
    if (buffer == NULL)
        return NULL;

    fgets(buffer, n + 1, stdin);

    unsigned long int len = strlen(buffer);
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    // No need to clear a stdio buffer if there are no more chars
    else if (len == n)
        io_clear_buffer();

    return buffer;
}

char* io_getstr()
{
    unsigned char step = 32;
    unsigned int size = 1; // Add 1 for '\0'
    char* str = malloc(sizeof(char));
    if (str == NULL)
        return NULL;
    char buffer[step];
    ssize_t i;
    do {
        i = read(STDIN_FILENO, buffer, step);

        if (i < 0) {
            // Error
            if (str != NULL)
                free(str);
            return NULL;
        } else if (i == 0) {
            // Done
            break;
        }
        // size = 1, i = 5, size = 6
        // input: abcde
        // str: ......
        // offset 6 - 5 - 1 = 0
        // memset: 0, 0, 6 (i + 1)
        // str: 000000
        // str: abcde\0

        // size = 6, i = 3, size = 9,
        // input: fg\n
        // str: abcde\0...
        // memset: 5, 0, 4
        // str:abcdefg\n\0

        size += i;
        str = realloc(str, sizeof(*str) * size);
        if (str == NULL)
            return NULL;

        memset(str + size - i - 1, '\0', i + 1);
        strncat(str, buffer, i);
    } while (i == step);

    str[strlen(str) - 1] = '\0'; // strlen - 1 is always a new line
    return str;
}
