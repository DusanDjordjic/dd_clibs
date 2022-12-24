# Simple prototype that uses memcpy to store elements

It works, I'm able to store non-pointer values by using memcpy.
It works for stack and heap allocated values. 
So the only problem is that I want to be able to send non-pointer values to `vector_push`, but then memcpy wouldn't work...
This will be added to the source code.

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_STEP 16

typedef struct vector_st {
	size_t element_size;
	size_t capacity;
	size_t length;
	void* elements;
} Vector;

typedef void (*printfn) (const void*);
typedef void (*freefn) (void*);

int vector_init(Vector* vec, size_t element_size);
int vector_push(Vector* vec, void* element);
void vector_print(Vector* vec, printfn element_print);
void* vector_end(Vector* vec);
void* vector_at(Vector* vec, size_t index);
void* vector_destory(Vector* vec, freefn element_free);

int vector_init(Vector* vec, size_t element_size)
{
	vec->element_size = element_size;
	vec->length = 0;
	vec->capacity = VECTOR_STEP;
	vec->elements = malloc(element_size * vec->capacity);
	if (vec->elements == NULL) {
		return 1;
	}

	return 0;
}

int vector_push(Vector* vec, void* element)
{
	if (vec->capacity == vec->length)
	{
		vec->capacity += VECTOR_STEP;
		void* new_elements = realloc(vec->elements, vec->capacity * vec->element_size);

		if (new_elements == NULL) {
			return 1;
		}

		vec->elements = new_elements;
	}
	
	void* end = vector_end(vec);
	
	memcpy(end, element, vec->element_size);
	vec->length += 1;

	return 0;

}

void vector_print(Vector* vec, printfn element_print) {
	for (size_t i = 0; i < vec->length; i++) {
		element_print(vector_at(vec, i));
	}
}

void* vector_at(Vector* vec, size_t index) {
	return (void*)((char*)vec->elements + index * vec->element_size);
}

void* vector_end(Vector* vec) {
	return (void*)((char*)vec->elements + vec->length * vec->element_size);
}

void* vector_destory(Vector* vec, freefn element_free) {

	if (element_free != NULL) {
		for (size_t i = 0; i < vec->length; i++) {
			element_free(vector_at(vec, i));
		}
	}

	free(vec->elements);
	vec->elements = NULL;
	vec->length = 0;
	vec->capacity = 0;
	vec->element_size = 0;
}
void int_print(const void* el)
{
	printf("EL = %d\n", *(int*)el);
}

void string_print(const void* el) {
	printf("EL = %s\n", *(const char**)el);
}

void string_free(void* el) {
	free(*(char**)el);
}

int main() {
	Vector vec;
	vector_init(&vec, sizeof(int));

	int arr[10] = { 0 };
	for (int i = 0; i < 10; i++) {
		arr[i] = i * 2;
	}
  
	// Ovde treba da posaljem samo int a ne int*,
  
	vector_push(&vec, arr + 0);
	vector_push(&vec, arr + 1);
	vector_push(&vec, arr + 2);
	vector_push(&vec, arr + 3);
	vector_push(&vec, arr + 4);
	vector_push(&vec, arr + 5);
	vector_push(&vec, arr + 6);
	vector_push(&vec, arr + 7);
	vector_push(&vec, arr + 8);

	vector_print(&vec, int_print);
	vector_destory(&vec, NULL);

  // STRINGS PRIMER
  
	Vector vec2;
	vector_init(&vec2, sizeof(char*));

	char* strings[10];
	for (int i = 0; i < 10; i++) {
		strings[i] = (char*)malloc(sizeof(char) * 9);
		if (strings[i] == NULL) {
			return 1;
		}
		memset(strings[i], 0, sizeof(char) * 9);
		strcpy_s(strings[i], sizeof(char) * 9, "Dusan123");	
	}

	vector_push(&vec2, (void*)(strings + 0));
	vector_push(&vec2, (void*)(strings + 1));
	vector_push(&vec2, (void*)(strings + 2));
	vector_push(&vec2, (void*)(strings + 3));
	vector_push(&vec2, (void*)(strings + 4));
	vector_push(&vec2, (void*)(strings + 5));
	vector_push(&vec2, (void*)(strings + 6));
	vector_push(&vec2, (void*)(strings + 7));
	vector_push(&vec2, (void*)(strings + 8));

	vector_print(&vec2, string_print);

	vector_destory(&vec2, string_free);

	return 0;
}
```
