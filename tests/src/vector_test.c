#include <stdio.h>
#include <string.h>

#include "../../lib/include/vector.h"

#include <criterion/criterion.h>

Test(vector, create)
{
    Vector vec;
    vector_create(&vec, 8);
    cr_expect(vector_capacity(&vec) == VECTOR_STEP, "Vector step is not %d.", VECTOR_STEP);
    cr_expect(vector_size(&vec) == 0, "Vector should be 0");
}

Test(vector, push)
{
    Vector vec;
    vector_create(&vec, sizeof(int*));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_size(&vec) == n, "Vector size should be %d", n);
}

Test(vector, pop)
{
    Vector vec;
    vector_create(&vec, sizeof(int*));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_size(&vec) == n, "Vector size should be %d", n);
    cr_expect(vector_pop(&vec) == arr + 2, "Expect 3rd element to be correct");
    cr_expect(vector_pop(&vec) == arr + 1, "Expect 2nd element to be correct");
    cr_expect(vector_pop(&vec) == arr + 0, "Expect 1st element to be correct");
    cr_expect(vector_size(&vec) == 0, "Vector should be 0");
}

Test(vector, at)
{
    Vector vec;
    vector_create(&vec, sizeof(int*));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_size(&vec) == n, "Vector size should be %d", n);
    cr_expect(vector_at(&vec, 1) == arr + 1, "Expect 2rd element to be correct");
    cr_expect(vector_at(&vec, n) == NULL, "Expect %dth element to be NULL", n);
}

Test(vector, destroy)
{
    Vector vec;
    vector_create(&vec, sizeof(int*));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_size(&vec) == n, "Vector size should be %d", n);

    vector_destroy(&vec, NULL);

    cr_expect(vector_size(&vec) == 0, "Vector size should be 0");
    cr_expect(vector_capacity(&vec) == 0, "Vector capacity should be 0");
}

int int_cmp(const void* n1, const void* n2)
{
    return n1 - n2;
}

Test(vector, sort)
{
    Vector vec;
    vector_create(&vec, sizeof(int*));

    int arr[] = { 3, 8, 7, 1, 0, 5, 4, 2, 9 };
    int arr_sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    vector_qsort(&vec, int_cmp);

    for (int i = 0; i < n; i++) {
        int el = *(int*)vector_at(&vec, i);
        cr_expect(el == arr_sorted[i], "Expected %d but got %d. Vector is not sorted", arr_sorted[i], el);
    }
}
