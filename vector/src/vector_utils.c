#include "vector.h"

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
