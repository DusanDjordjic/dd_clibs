#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef VECTOR_DEBUG
#define VECTOR_CHECK_ELEMENTS_NULL(x)                                                        \
    if (vec->elements == NULL) {                                                             \
        printf("%sError in %s on line %d\n%s", "\033[1;31m", __FILE__, __LINE__, "\033[0m"); \
        return x;                                                                            \
    }
#else
#define VECTOR_CHECK_ELEMENTS_NULL(x)
#endif

void vector_create(Vector* vec, unsigned int element_size)
{
    vec->element_size = element_size;
    vec->actual_length = VECTOR_STEP;
    vec->logical_length = 0;
    vec->elements_popped_before_push = 0;
    vec->elements = malloc(vec->actual_length * element_size);
}

void vector_destroy(Vector* vec, void (*element_destroy)(void*))
{
    VECTOR_CHECK_ELEMENTS_NULL();

    void** it;
    for (unsigned int i = 0; i < vec->logical_length; i++) {
        it = (void**)(((char*)vec->elements) + i * vec->element_size);
        element_destroy(*it);
    }

    free(vec->elements);
    vec->elements = NULL;
    vec->actual_length = 0;
    vec->logical_length = 0;
    vec->element_size = 0;
    vec->elements_popped_before_push = 0;
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

void** vector_end(Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    return (void**)(((char*)vec->elements) + vec->logical_length * vec->element_size);
}

void** vector_start(Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);
    return vec->elements;
}

unsigned int vector_size(Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->logical_length;
}

unsigned int vector_capacity(Vector* vec)
{
    VECTOR_CHECK_ELEMENTS_NULL(0);
    return vec->actual_length;
}

void vector_print(Vector* vec, void (*element_print)(void*))
{
    VECTOR_CHECK_ELEMENTS_NULL();
    void** it;
    for (unsigned int i = 0; i < vec->logical_length; i++) {
        it = (void**)(((char*)vec->elements) + i * vec->element_size);
        element_print(*it);
    }
}
