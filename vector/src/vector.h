#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifndef VECTOR_STEP
#define VECTOR_STEP 8
#endif

typedef struct {
    unsigned int elements_popped_before_push;
    unsigned int element_size;
    unsigned int actual_length;
    unsigned int logical_length;
    void* elements;
} Vector;

void vector_create(Vector* vec, unsigned int element_size);
void vector_destroy(Vector* vec, void (*element_destroy)(void*));
void vector_push(Vector* vec, void* element);
void* vector_pop(Vector* vec);
void vector_print(Vector* vec, void (*element_print)(void*));
void** vector_start(Vector* vec);
void** vector_end(Vector* vec);
unsigned int vector_capacity(Vector* vec);
unsigned int vector_size(Vector* vec);
#endif
