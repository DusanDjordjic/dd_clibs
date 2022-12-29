#include "../../lib/include/vector.h"
#include <stdio.h>
#include <string.h>

/*
 * Exapmple 03 - Storing poniters
 *
 * Using Vector to store strings.
 *
 * Using vector_foreach to loop through vector and print all strings
 * Using vector_find and vector_find_all to find strings that contain characher '1'
 * */

void string_free(void* element)
{
    // Note that because we store char* in the vector
    // when string free is called we get pointer to that element ei. char**
    char* s = *(char**)element;
    free(s);
}

void string_print(void* element)
{
    char* s = *(char**)element;
    printf("\"%s\"\n", s);
}

int string_find_1(const void* element)
{
    char* s = *(char**)element;
    for (; *s != '\0'; s++)
        if (*s == '1')
            return 0;

    return 1;
}

int main(void)
{
    Vector vec;
    vector_init(&vec, sizeof(char*));

    char* s;
    for (int i = 1; i < 11; i++) {
        // len(Test10) + 1(\0) = 7
        size_t len = sizeof(char) * 7;
        s = malloc(len);
        memset(s, 0, len);
        sprintf(s, "Test%d", i);

        vector_push(&vec, &s);
    }

    printf("Contents of a vector\n");
    vector_foreach(&vec, string_print);
    printf("====================\n");

    void* vs1 = vector_find(&vec, string_find_1);
    if (vs1 == NULL) {
        printf("There is no string that contains '1'\n");
    } else {
        char* s = *(char**)vs1;
        printf("FIND: String that contains '1' -> \"%s\"\n", s);
    }

    Vector* string_indexes;

    vector_find_all(&vec, string_find_1, &string_indexes);
    // string_indexes vector stores the indexes of the elements in vec
    // vector_at returns pointer to the element in vector (size_t*)
    // Then we use that index to find the correct string in 'vec'
    for (size_t i = 0; i < vector_length(string_indexes); i++) {
        size_t s_index_in_vec = *(size_t*)vector_at(string_indexes, i);
        char* s = *(char**)vector_at(&vec, s_index_in_vec);
        printf("FIND_ALL: Index %lu. String that contains '1' -> \"%s\"\n", s_index_in_vec, s);
    }

    vector_destroy(&vec, string_free);
    vector_destroy(string_indexes, NULL);
    // Note that we have to free the 'string_indexes' as well,
    // Because its dynamically allocted in vector_find_all
    free(string_indexes);

    return 0;
}
