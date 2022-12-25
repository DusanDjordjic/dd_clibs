#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#ifndef VECTOR_STEP
#define VECTOR_STEP 16
#endif

#ifdef DEBUG
#define VECTOR_CHECK_ELEMENTS_NULL(x)                                                        \
    if (vec->elements == NULL) {                                                             \
        printf("%sError in %s on line %d\n%s", "\033[1;31m", __FILE__, __LINE__, "\033[0m"); \
        return x;                                                                            \
    }
#else
#define VECTOR_CHECK_ELEMENTS_NULL(x)
#endif

typedef int (*comparefn)(const void*, const void*);
typedef void (*freefn)(void*);
typedef void (*printfn)(const void*);

typedef struct {
    size_t element_size;
    size_t capacity;
    size_t length;
    void* elements;
} Vector;

// Basic
int vector_init(Vector* vec, size_t element_size);
int vector_destroy(Vector* vec, freefn);
int vector_push(Vector* vec, const void* element);
void* vector_pop(Vector* vec);

// Advanced
void* vector_replace(Vector* vec, const size_t index, const void* element, freefn);
int vector_sort(Vector* vec, comparefn cmpfn);

// Utils
int vector_print(const Vector* vec, printfn);
void* vector_at(const Vector* vec, const size_t index);
void* vector_start(const Vector* vec);
void* vector_end(const Vector* vec);
size_t vector_capacity(const Vector* vec);
size_t vector_length(const Vector* vec);

#endif
