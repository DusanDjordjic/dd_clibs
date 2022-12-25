#include "vector.h"
#include <stdlib.h>
#include <string.h>

static int partition(void* elements, const size_t element_size, const int low_index, const int high_index, comparefn cmpfn)
{
    void* pivot = (char*)elements + high_index * element_size;

    void* tmp = malloc(element_size);

    int i = low_index;
    for (int j = low_index; j < high_index; j++) {
        if (cmpfn((char*)elements + j * element_size, pivot) > 0) {
            // swap I and J
            void* jp = ((char*)elements + j * element_size);
            void* ip = ((char*)elements + i * element_size);
            memcpy(tmp, jp, element_size);
            memcpy(jp, ip, element_size);
            memcpy(ip, tmp, element_size);

            i++;
        }
    }

    // swap I and High
    void* highp = ((char*)elements + high_index * element_size);
    void* ip = ((char*)elements + i * element_size);
    memcpy(tmp, highp, element_size);
    memcpy(highp, ip, element_size);
    memcpy(ip, tmp, element_size);

    free(tmp);

    return i;
}

static void quick_sort(void* elements, int element_size, int low_index, int high_index, comparefn cmpfn)
{
    if (low_index < high_index) {
        int p = partition(elements, element_size, low_index, high_index, cmpfn);
        quick_sort(elements, element_size, low_index, p - 1, cmpfn);
        quick_sort(elements, element_size, p + 1, high_index, cmpfn);
    }
}

int vector_sort(Vector* vec, comparefn cmpfn)
{
    VECTOR_CHECK_ELEMENTS_NULL(1);

    int high_index = vector_length(vec) - 1;
    int low_index = 0;
    quick_sort(vec->elements, vec->element_size, low_index, high_index, cmpfn);

    return 0;
}
