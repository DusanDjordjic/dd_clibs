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

void** vector_at(const Vector* vec, const unsigned int index)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

#ifdef DEBUG
    if (index >= vec->logical_length)
        return NULL;
#endif

    return (void**)((char*)vec->elements + vec->element_size * index);
}

unsigned int vector_size(const Vector* vec)
{
    // TODO Better Error code than just 0
    // bacuse 0 is valid length
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->logical_length;
}

unsigned int vector_capacity(const Vector* vec)
{
    // TODO Better Error code than just 0
    // bacuse 0 is valid length
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->actual_length;
}

void vector_print(const Vector* vec, printfn element_print)
{
    // TODO Error code
    VECTOR_CHECK_ELEMENTS_NULL();

    // TODO Error code
    if (element_print == NULL) {
        return;
    }

    void** it;
    for (unsigned int i = 0; i < vec->logical_length; i++) {
        it = (void**)(((char*)vec->elements) + i * vec->element_size);
        element_print(*it);
    }
}
