#include <stdio.h>
#include <string.h>

#include "../../lib/include/io.h"
#include "../../lib/include/vector.h"

int main()
{
    printf("TESTS \n");
    char* str = io_getstr();

    printf("LEN: %lu\n%s\n", strlen(str), str);

    return 0;
}
