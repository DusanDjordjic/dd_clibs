#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void vector_create(Vector* vec, unsigned int element_size)
{
    vec->element_size = element_size;
    vec->actual_length = VECTOR_STEP;
    vec->logical_length = 0;
    vec->elements = malloc(vec->actual_length * element_size);
}

void vector_destroy(Vector* vec, freefn element_free)
{
    VECTOR_CHECK_ELEMENTS_NULL();

    if (element_free != NULL) {
        void** it;
        for (unsigned int i = 0; i < vec->logical_length; i++) {
            it = (void**)(((char*)vec->elements) + i * vec->element_size);
            element_free(*it);
        }
    }

    free(vec->elements);
    vec->elements = NULL;
    vec->actual_length = 0;
    vec->logical_length = 0;
    vec->element_size = 0;
}

void vector_push(Vector* vec, void* element)
{
    VECTOR_CHECK_ELEMENTS_NULL();

    if (vec->logical_length == vec->actual_length) {
        vec->actual_length += VECTOR_STEP;
        vec->elements = realloc(vec->elements, vec->actual_length * vec->element_size);
        assert(vec->elements != NULL);
    }

    *vector_end(vec) = element;
    vec->logical_length++;
}

void* vector_pop(Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    vec->logical_length--;
    return *vector_end(vec);
}

void** vector_replace(const Vector* vec, const unsigned int index, void* element, freefn element_free)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    void** el = vector_at(vec, index);

#ifdef DEBUG
    if (el == NULL) {
        return NULL;
    }
#endif
    // There is no element at given index
    // So we'll just insert it
    if (*el == NULL) {
        *el = element;
        return el;
    }

    if (element_free != NULL) {
        element_free(*el);
        return NULL;
    }

    *el = element;

    return el;
}
