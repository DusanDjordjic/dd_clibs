#include "vector.h"
#include <stdlib.h>
typedef int (*comparefn)(void*, void*);
void vector_qsort(Vector* vec, int (*element_compare)(const void*, const void*))
{
    VECTOR_CHECK_ELEMENTS_NULL(NULL);

    vector_size(vec);
    element_compare(vec->elements, (char*)vec->elements + vec->element_size);
}
int partition(void* elements, int element_size, int low_index, int high_index, comparefn cmpfn)
{
    void* pivot = (char*)elements + high_index * element_size;

    int i = low_index - 1;
    for (int j = low_index; j <= high_index; j++) {
        if (cmpfn((char*)elements + j * element_size, pivot) > 0) {
            i++;
            void* tmp = (char*)elements + i * element_size;
        }
    }

    return i + 1;
}

void quick_sort(void* elements, int element_size, int low_index, int high_index, comparefn cmpfn)
{
    if (low_index < high_index) {
        int p = partition(elements, element_size, low_index, high_index, cmpfn);
        quick_sort(elements, element_size, low_index, p - 1, cmpfn);
        quick_sort(elements, element_size, p + 1, high_index, cmpfn);
    }
}
