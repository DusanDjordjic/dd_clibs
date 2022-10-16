#include "vector.h"
#include <stdlib.h>

void** vector_end(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    return (void**)(((char*)vec->elements) + vec->logical_length * vec->element_size);
}

void** vector_start(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);
    return vec->elements;
}

void** vector_at(const Vector* vec, unsigned int index)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

#ifdef VECTOR_DEBUG
    if (index >= vec->logical_length)
        return NULL;
#endif

    return (void**)((char*)vec->elements + vec->element_size * index);
}

unsigned int vector_size(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->logical_length;
}

unsigned int vector_capacity(const Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->actual_length;
}

void vector_print(const Vector* vec, void (*element_print)(const void*))
{
    VECTOR_CHECK_ELEMENTS_NULL();
    void** it;
    for (unsigned int i = 0; i < vec->logical_length; i++) {
        it = (void**)(((char*)vec->elements) + i * vec->element_size);
        element_print(*it);
    }
}
