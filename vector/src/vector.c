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

void vector_destroy(Vector* vec, void (*element_destroy)(void*))
{
    VECTOR_CHECK_ELEMENTS_NULL();

    if (element_destroy != NULL) {
        void** it;
        for (unsigned int i = 0; i < vec->logical_length; i++) {
            it = (void**)(((char*)vec->elements) + i * vec->element_size);
            element_destroy(*it);
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

void* vector_at(const Vector* vec, unsigned int index)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    if (index >= vec->logical_length)
        return NULL;

    return *(void**)((char*)vec->elements + vec->element_size * index);
}
