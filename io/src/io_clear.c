#include <stdio.h>

#include "io.h"

void io_clear_buffer()
{
    while (fgetc(stdin) != '\n') { };
}
