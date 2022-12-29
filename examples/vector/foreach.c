#include "../../lib/include/vector.h"
#include <stdio.h>

/*
 * Exapmple 02 - Foreach
 *
 * Using Vector to store ints.
 *
 * Using vector_foreach to loop through vector and sum all of the elements
 * */

int g_sum = 0;

void vector_sum(void* element)
{
    g_sum += *(int*)element;
}

int main(void)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    for (int i = 1; i < 11; i++) {
        // Send the address of i
        // vector_push uses memcpy to copy from &i to the vector
        vector_push(&vec, &i);
    }

    vector_foreach(&vec, vector_sum);

    printf("Global Sum is %d\n", g_sum);

    vector_destroy(&vec, NULL);

    return 0;
}
