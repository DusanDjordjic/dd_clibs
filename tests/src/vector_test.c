#include <stdio.h>
#include <string.h>

#include "../../lib/include/vector.h"
#include <criterion/criterion.h>

void int_print(const void* item)
{
    printf("%d ", *(int*)item);
}

int int_cmp(const void* p1, const void* p2)
{
    int n1 = *(int*)p1;
    int n2 = *(int*)p2;
    return n2 - n1;
}

Test(vector, init)
{
    Vector vec;
    vector_init(&vec, 8);
    cr_expect(vector_capacity(&vec) == VECTOR_STEP, "Vector step is not %d.", VECTOR_STEP);
    cr_expect(vector_length(&vec) == 0, "Vector should be 0");
    vector_destroy(&vec, NULL);
}

Test(vector, destroy)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_length(&vec) == n, "Vector size should be %d", n);

    vector_destroy(&vec, NULL);

    cr_expect(vector_length(&vec) == 0, "Vector size should be 0");
    cr_expect(vector_capacity(&vec) == 0, "Vector capacity should be 0");
}

Test(vector, push)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 1, 2, 3 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(vector_length(&vec) == n, "Vector size should be %lu", n);
    vector_destroy(&vec, NULL);
}

Test(vector, pop)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 1, 2, 3 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(*(int*)vector_pop(&vec) == 3, "Expect 3rd element to be correct");
    cr_expect(*(int*)vector_pop(&vec) == 2, "Expect 2nd element to be correct");
    cr_expect(*(int*)vector_pop(&vec) == 1, "Expect 1st element to be correct");
    cr_expect(vector_length(&vec) == 0, "Vector should be 0");

    vector_destroy(&vec, NULL);
}

Test(vector, at)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(*(int*)vector_at(&vec, 0) == 1, "Expect 1st element to be correct");
    cr_expect(*(int*)vector_at(&vec, 1) == 2, "Expect 2nd element to be correct");
    cr_expect(*(int*)vector_at(&vec, 2) == 3, "Expect 3rd element to be correct");

    vector_destroy(&vec, NULL);
}

Test(vector, replace)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 1, 2, 3 };

    unsigned int n = sizeof(arr) / sizeof(int);

    for (unsigned int i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    cr_expect(*(int*)vector_replace(&vec, 1, arr + 2, NULL) == 3, "Expect 2rd element to be 3rd element");
    cr_expect(*(int*)vector_at(&vec, 2) == 3, "Expect 3rd element to be correct");
    cr_expect(*(int*)vector_at(&vec, 1) == 3, "Expect 2nd element to be correct");
    cr_assert_null(vector_replace(&vec, 1, NULL, NULL));

    vector_destroy(&vec, NULL);
}

Test(vector, sort)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 3, 8, 1, 9, 9, 3, 7, 4, 8, 7, 1, 6, 5, 4, 2, 9 };
    int arr_sorted[] = { 1, 1, 2, 3, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9, 9, 9 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    vector_sort(&vec, int_cmp);

    for (size_t i = 0; i < n; i++) {
        int n = *(int*)vector_at(&vec, i);
        cr_expect(n == arr_sorted[i], "Expected %d to be %d", n, arr_sorted[i]);
    }
}
