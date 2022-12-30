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

int int_find_1(const void* p1)
{
    const int n = *(int*)p1;
    return n - 1;
}

int int_find_2(const void* p1)
{
    const int n = *(int*)p1;
    return n - 2;
}

int int_find_3(const void* p1)
{
    const int n = *(int*)p1;
    return n - 3;
}

int int_find_11(const void* p1)
{
    const int n = *(int*)p1;
    return n - 11;
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
    cr_expect(vector_at(&vec, 100) == NULL, "Expect 101th element to be out of range");
    cr_expect(vector_err(&vec) == DDV_ERANGE, "Expect 101th element to be out of range");

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

    cr_expect(vector_replace(&vec, 1, arr + 2, NULL) == DDV_OK);
    cr_expect(*(int*)vector_at(&vec, 2) == 3, "Expect 3rd element to be correct");
    cr_expect(*(int*)vector_at(&vec, 1) == 3, "Expect 2nd element to be correct");
    cr_expect(vector_replace(&vec, 1, NULL, NULL) == DDV_EINVAL);

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

    vector_destroy(&vec, NULL);
}

Test(vector, find)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 3, 8, 1, 9, 9, 3, 7, 4, 8, 7, 1, 6, 5, 4, 2, 9 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    void* fa = vector_find(&vec, int_find_1);
    cr_expect(fa != NULL, "FA to not be NULL");

    void* fb = vector_at(&vec, 2);
    cr_expect(fb != NULL, "FB to not be NULL");

    int a = *(int*)fa;
    int b = *(int*)fb;

    cr_expect(a == b, "Expected %d == %d", a, b);

    void* fc = vector_find(&vec, int_find_11);
    cr_expect(fc == NULL, "FC be NULL");

    vector_destroy(&vec, NULL);
}

Test(vector, find_all)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 3, 8, 1, 9, 1, 3, 7, 4, 8, 7, 1, 6, 5, 4, 1, 9 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    Vector* results;
    Vector* results2;

    vector_find_all(&vec, int_find_1, &results);
    vector_find_all(&vec, int_find_3, &results2);

    cr_expect(vector_length(results) == 4, "To find 4 '1s'");
    cr_expect(vector_length(results2) == 2, "To find 2 '3s'");

    vector_destroy(&vec, NULL);
    vector_destroy(results, NULL);
    vector_destroy(results2, NULL);

    free(results);
    free(results2);
}

Test(vector, copy)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 3, 8, 1, 9, 1, 3, 7, 4, 8, 7, 1, 6, 5, 4, 1, 9, 10, 1, 3, 6, 8, 9 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    Vector clone;

    cr_expect(DDV_OK == vector_copy(&clone, &vec), "Expect vector_copy to work");

    cr_expect(vector_length(&clone) == vector_length(&vec), "Expect lengths to be equal");
    cr_expect(vector_capacity(&clone) == vector_capacity(&vec), "Expect capacities to be equal");
    cr_expect(vector_element_size(&clone) == vector_element_size(&vec), "Expect element sizes to be equal");
    cr_expect(vector_err(&clone) == vector_err(&vec), "Expect error codes to be equal");

    for (size_t i = 0; i < vector_length(&vec); i++) {
        int n1 = *(int*)vector_at(&vec, i);
        int n2 = *(int*)vector_at(&clone, i);
        cr_expect(n1 == n2, "Expect elemets to be copied correctly %d %d", n1, n2);
    }

    vector_destroy(&vec, NULL);
    vector_destroy(&clone, NULL);
}

Test(vector, clone)
{
    Vector vec;
    vector_init(&vec, sizeof(int));

    int arr[] = { 3, 8, 1, 9, 1, 3, 7, 4, 8, 7, 1, 6, 5, 4, 1, 9, 10, 1, 3, 6, 8, 9 };

    size_t n = sizeof(arr) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
        vector_push(&vec, arr + i);
    }

    Vector* clone;

    cr_expect(DDV_OK == vector_clone(&clone, &vec), "Expect vector_copy to work");

    cr_expect(vector_length(clone) == vector_length(&vec), "Expect lengths to be equal");
    cr_expect(vector_capacity(clone) == vector_capacity(&vec), "Expect capacities to be equal");
    cr_expect(vector_element_size(clone) == vector_element_size(&vec), "Expect element sizes to be equal");
    cr_expect(vector_err(clone) == vector_err(&vec), "Expect error codes to be equal");

    for (size_t i = 0; i < vector_length(&vec); i++) {
        int n1 = *(int*)vector_at(&vec, i);
        int n2 = *(int*)vector_at(clone, i);
        cr_expect(n1 == n2, "Expect elemets to be copied correctly %d %d", n1, n2);
    }

    vector_destroy(&vec, NULL);
    vector_destroy(clone, NULL);
    free(clone);
}
