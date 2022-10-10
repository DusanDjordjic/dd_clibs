#include <stdio.h>
#include <string.h>

#include "../../lib/include/vector.h"

#include <criterion/criterion.h>

Test(vector, create)
{
    Vector vec;
    vector_create(&vec, 8);
    cr_expect(vector_capacity(&vec) == VECTOR_STEP, "Vector step is not %d.", VECTOR_STEP);
    cr_expect(vector_size(&vec) == 0, "Vector should be empty");
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
    cr_expect(vector_size(&vec) == 0, "Vector should be empty");
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
