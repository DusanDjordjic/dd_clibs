#include "vector.h"
#include <stdlib.h>

void* vector_end(Vector* vec)
{
    return vector_at(vec, vec->length);
}

void* vector_start(Vector* vec)
{
    return vector_at(vec, 0);
}

void* vector_at(Vector* vec, const size_t index)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return 0;
    }

    if (index > vec->capacity) {
        vec->err = DDV_ERANGE;
        return NULL;
    }

    return (void*)((char*)vec->elements + vec->element_size * index);
}

size_t vector_length(Vector* vec)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return 0;
    }

    return vec->length;
}

size_t vector_capacity(Vector* vec)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return 0;
    }

    return vec->capacity;
}

ddv_err vector_err(Vector* vec)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return 0;
    }

    return vec->err;
}

ddv_err vector_foreach(Vector* vec, dofn element_do)
{
    if (vec == NULL || vec->elements == NULL) {
        return DDV_EUNINT;
    }

    if (element_do == NULL) {
        return DDV_EINVAL;
    }

    for (size_t i = 0; i < vec->length; i++) {
        element_do(vector_at(vec, i));
    }

    return DDV_OK;
}
