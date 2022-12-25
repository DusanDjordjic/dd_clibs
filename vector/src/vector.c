#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vector_init(Vector* vec, const size_t element_size)
{
    vec->element_size = element_size;
    vec->capacity = VECTOR_STEP;
    vec->length = 0;
    vec->elements = malloc(vec->capacity * element_size);
    if (vec->elements == NULL) {
        return 1;
    }

    return 0;
}

int vector_destroy(Vector* vec, freefn element_free)
{
    VECTOR_CHECK_ELEMENTS_NULL(1);

    if (element_free != NULL) {
        for (size_t i = 0; i < vec->length; i++) {
            element_free(vector_at(vec, i));
        }
    }

    free(vec->elements);
    vec->elements = NULL;
    vec->capacity = 0;
    vec->length = 0;
    vec->element_size = 0;

    return 0;
}

int vector_push(Vector* vec, const void* element)
{
    VECTOR_CHECK_ELEMENTS_NULL(1);
    if (element == NULL) {
        return 2;
    }

    if (vec->length == vec->capacity) {
        vec->capacity += VECTOR_STEP;
        void* new_elements = realloc(vec->elements, vec->capacity * vec->element_size);
        if (new_elements == NULL) {
            return 3;
        }
        vec->elements = new_elements;
    }

    memcpy(vector_end(vec), element, vec->element_size);
    vec->length += 1;

    return 0;
}

void* vector_pop(Vector* vec)
{
    // TODO: Better error codes
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    vec->length -= 1;
    return vector_end(vec);
}

void* vector_replace(Vector* vec, const size_t index, const void* element, freefn element_free)
{
    // TODO: Better error codes
    VECTOR_CHECK_ELEMENTS_NULL(NULL);
    if (element == NULL) {
        return NULL;
    }

    // Index out of bounds
    if (vec->capacity <= index) {
        return NULL;
    }

    void* el = vector_at(vec, index);

    // There is no element at given index
    // So we'll just insert it

    if (vec->length >= index) {
        memcpy(el, element, vec->element_size);
        return el;
    }

    // If element_free func is provided use it to
    // free existing element at 'index'
    if (element_free != NULL) {
        element_free(el);
    }

    memcpy(el, element, vec->element_size);
    return el;
}
