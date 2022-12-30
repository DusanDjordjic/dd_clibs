#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h> /* for size_t */

#ifndef VECTOR_STEP
#define VECTOR_STEP 16
#endif

typedef int (*comparefn)(const void*, const void*);
typedef int (*findfn)(const void*);
typedef void (*freefn)(void*);
typedef void (*dofn)(void*);

typedef enum {
    DDV_OK = 0,
    DDV_ERROR = 1,
    DDV_ENOMEM = 2,
    DDV_ERANGE = 3,
    DDV_EINVAL = 4,
    DDV_EUNINT = 5,
} ddv_err;

typedef struct {
    size_t element_size;
    size_t capacity;
    size_t length;
    void* elements;
    /**
     * Using err field so I don't have to overwrite the errno
     * and possibly break strerrno
     */
    ddv_err err;
} Vector;

/**
 * Initializes the vector
 * allocates element_size * VECTOR_STEP of memory
 *
 * Error returns:
 * DDV_ENOMEM if malloc returns NULL
 * DDV_OK on success
 */
ddv_err vector_init(Vector* vec, const size_t element_size);

/**
 * Destroyes the vector
 * if provided calls freefn by passing to it pointer to every element of the vector.
 * Useful when pointers to dynamically allocated memory are stored in the vector.
 *
 * Frees the vector->elements and sets all other fields to 0
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are already NULL
 * DDV_OK on success
 */
ddv_err vector_destroy(Vector* vec, freefn element_free);

/**
 * Adds another element to the end of the vector.
 * Changes the capacity by +VECTOR_STEP if vector is full
 * and reallocates memory for elements.
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if 'element' is NULL
 * DDV_ENOMEM if it cannot reallocate more memory
 * DDV_OK on success
 */
ddv_err vector_push(Vector* vec, const void* element);

/**
 * Returns the pointer to the last element
 * and decrements the length of the vector.
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
void* vector_pop(Vector* vec);

/**
 * Replaces the element at a given index with 'element'.
 * if provided calls freefn by passing to it pointer to the element at 'index'
 * before replacing it.
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if 'element' is NULL
 * DDV_ERANGE if 'index' is greater than the vector length
 * DDV_OK on success
 */
ddv_err vector_replace(Vector* vec, const size_t index, const void* element, freefn element_free);

/**
 * Finds the element using provided findfn by passing each element of a vector to it.
 * When findfn returns 0 element is found.
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if 'findfn' is NULL
 * DDV_OK on success
 */
void* vector_find(Vector* vec, findfn element_find);

/**
 * Finds all elements using provided findfn by passing each element of a vector to it.
 * When findfn returns 0 element is found.
 * Each element's index is added to the *results vector.
 * '*results' will at the end contain indexes of elements in 'vec' found by using findfn
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if 'findfn' is NULL or 'results' is NULL
 * DDV_OK on success
 *
 * Note:
 * 'results' is dynamically allocated so the caller should free it after.
 */
ddv_err vector_find_all(Vector* vec, findfn element_find, Vector** results);

/**
 * Sorts the vector using comparefn
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if comparefn is NULL
 * DDV_OK on success
 */
ddv_err vector_sort(Vector* vec, comparefn cmpfn);

/**
 * Calls the dofn for each element in the vector
 * passing to it the pointer to the element
 *
 * Error returns:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_EINVAL if 'element_do' is NULL
 * DDV_OK on success
 */
ddv_err vector_foreach(Vector* vec, dofn element_do);

/**
 * Clopied the fields and elements from src to dest
 *
 * Error returns:
 * DDV_EUNINT if 'dest' or 'src' are NULL
 * DDV_ENOMEM if allocation failes
 * DDV_OK on success
 */
ddv_err vector_copy(Vector* dest, const Vector* src);

/**
 * Allocates new vector and copies the fields and elements from src.
 * Address of newly allocated vector is stored in *dest.
 *
 * Error returns:
 * DDV_EUNINT if 'dest' or 'src' are NULL
 * DDV_ENOMEM if allocation failes
 * DDV_OK on success
 */
ddv_err vector_clone(Vector** dest, const Vector* src);

/**
 * Returns the pointer to the element at a given index
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_ERANGE if index is bigger then the capacity
 */
void* vector_at(Vector* vec, const size_t index);

/**
 * Returns the pointer to firts element
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
void* vector_start(Vector* vec);

/**
 * Returns the pointer to one pass the last element
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 * DDV_ERANGE if length and capacity are the same, that is, vector is full
 */
void* vector_end(Vector* vec);

/**
 * Returns the capacity of a vector
 *
 * Error returns:
 * 0 on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
size_t vector_capacity(Vector* vec);

/**
 * Returns the length of a vector
 *
 * Error returns:
 * 0 on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
size_t vector_length(Vector* vec);

/**
 * Returns the element_size
 *
 * Error returns:
 * 0 on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
size_t vector_element_size(Vector* vec);

/**
 * Returns the current set error code
 *
 * Error returns:
 * NULL on error
 *
 * Sets error code:
 * DDV_EUNINT if vec or vec->elements are NULL
 */
ddv_err vector_err(Vector* vec);

#endif
