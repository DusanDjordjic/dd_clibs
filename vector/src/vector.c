#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ddv_err vector_init(Vector* vec, const size_t element_size)
{
    vec->element_size = element_size;
    vec->capacity = VECTOR_STEP;
    vec->length = 0;
    vec->err = DDV_OK;

    vec->elements = malloc(vec->capacity * element_size);
    if (vec->elements == NULL) {
        return DDV_ENOMEM;
    }

    return 0;
}

ddv_err vector_destroy(Vector* vec, freefn element_free)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return DDV_EUNINT;
    }

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
    vec->err = DDV_OK;

    return DDV_OK;
}

ddv_err vector_push(Vector* vec, const void* element)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return DDV_EUNINT;
    }

    if (element == NULL) {
        vec->err = DDV_EINVAL;
        return DDV_EINVAL;
    }

    if (vec->length == vec->capacity) {
        vec->capacity += VECTOR_STEP;
        void* new_elements = realloc(vec->elements, vec->capacity * vec->element_size);
        if (new_elements == NULL) {
            vec->err = DDV_ENOMEM;
            return DDV_ENOMEM;
        }
        vec->elements = new_elements;
    }

    memcpy(vector_end(vec), element, vec->element_size);
    vec->length += 1;

    vec->err = DDV_OK;
    return DDV_OK;
}

void* vector_pop(Vector* vec)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return NULL;
    }

    vec->length -= 1;
    vec->err = DDV_OK;
    return vector_end(vec);
}

ddv_err vector_replace(Vector* vec, const size_t index, const void* element, freefn element_free)
{
    void* el = vector_at(vec, index);
    if (el == NULL) {
        // Returns DDV_UNINIT | DDV_ERANGE
        return vec->err;
    }

    if (element == NULL) {
        vec->err = DDV_EINVAL;
        return DDV_EINVAL;
    }

    if (element_free != NULL) {
        element_free(el);
    }

    memcpy(el, element, vec->element_size);

    vec->err = DDV_OK;
    return DDV_OK;
}

void* vector_find(Vector* vec, findfn element_find)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return NULL;
    }

    if (element_find == NULL) {
        vec->err = DDV_EINVAL;
        return NULL;
    }

    void* element = NULL;

    for (size_t i = 0; i < vec->length; i++) {
        element = vector_at(vec, i);

        if (element_find(element) == 0) {
            return element;
        }
    }

    vec->err = DDV_OK;
    return NULL;
}

ddv_err vector_find_all(Vector* vec, findfn element_find, Vector** results)
{
    if (vec == NULL || vec->elements == NULL) {
        vec->err = DDV_EUNINT;
        return DDV_EUNINT;
    }

    if (element_find == NULL) {
        vec->err = DDV_EINVAL;
        return DDV_EINVAL;
    }

    *results = malloc(sizeof(Vector));
    vector_init(*results, sizeof(void*));
    void* element;

    for (size_t i = 0; i < vec->length; i++) {
        element = vector_at(vec, i);

        if (element_find(element) == 0) {
            vector_push(*results, &element);
        }
    }

    vec->err = DDV_OK;
    return DDV_OK;
}
