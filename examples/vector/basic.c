#include "../../lib/include/vector.h"
#include <stdio.h>

/*
 * Exapmple 01 - Basic
 *
 * Using Vector to store ints and sum them up
 * */

int vector_sum(Vector* vec)
{
    int sum = 0;
    for (size_t i = 0; i < vector_length(vec); i++) { // Could also used vec->length
        sum += *(int*)vector_at(vec, i);
    }

    return sum;
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

    int sum = vector_sum(&vec);
    printf("Sum is %d\n", sum);

    vector_destroy(&vec, NULL);

    return 0;
}
