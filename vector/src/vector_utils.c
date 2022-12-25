#include "vector.h"
#include <stdlib.h>

void* vector_end(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);
    return vector_at(vec, vec->length);
}

void* vector_start(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);
    return vec->elements;
}

void* vector_at(const Vector* vec, const size_t index)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

#ifdef DEBUG
    if (index >= vec->length)
        return NULL;
#endif

    return (void*)((char*)vec->elements + vec->element_size * index);
}

size_t vector_length(const Vector* vec)
{
    return vec->length;
}

size_t vector_capacity(const Vector* vec)
{
    return vec->capacity;
}

int vector_print(const Vector* vec, printfn element_print)
{
    VECTOR_CHECK_ELEMENTS_NULL(1);

    if (element_print == NULL) {
        return 2;
    }

    for (size_t i = 0; i < vec->length; i++) {
        element_print(vector_at(vec, i));
    }

    return 0;
}
