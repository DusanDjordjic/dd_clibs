# Dusan Djordjic's Vector

Generic vector (dynamic array) implementation with functions like `vector_foreach`, `vector_find`, `vector_find_all`...
These function provide a nice API for users to easily query the vector or do some operations on in.

## List of functions 

For more detailed description on what each function does and what error it sets see *src/vector.h* file.

- *vector_init* : Initializes the vector and alloces first *blob* of memory.
- *vector_destroy* : Frees the vector and optionally takes a function pointer that is used to free individual elements in vector.
- *vector_push* : Uses memcpy to copy the contents of a passed *void\** argument to the end of a vector.
- *vector_pop* : Returns a pointer to the last element of a vector and decrements the length.
- *vector_replace* : Replaces the element at a given index, optionally takes a function pointer the is used to free replaced element.
- *vector_find* : Finds the first element that *freefn* returns 0 for and returns a pointer to it.
- *vector_find_all* : Allocates a new vector that will hold the indexes of found elements in the firts vector. Uses *freefn* to 'find' the elements. Vector\*\* argument will be set to hold the pointer to the allocated vector. Also the function calls `vector_init` with the new allocated vector so you shouldn't
- *vector_sort* : Sorts the vector by some condition that is determined by *comparefn* passed to it.
- *vector_copy* : Clopis all the fields and elements form src to dest.
- *vector_clone* : Allocates a new vector and copies all the fields and elements from src to it. Address of newly allocated vector is stored in \*dest.
- *vector_at* : Returns a pointer to the element at given index.
- *vector_start* : Returns a pointer to the firts element (start of the array).
- *vector_end* : Returns a pointer to the one pass the last element.
- *vector_capacity* : Returns the total size of allocated memory.
- *vector_length* : Returns the number of elements that are stored in vector.
- *vector_err* : Returns the error\_code set in vector. Useful to see if something and went wrong with previous *vector_* function. See *vector.h* for the list of error codes.

## Examples 

Examples are found in the *repo\_root/examples/vector/*. Feel free to make a pull request with more examples.

## Future

In the future expect some more utility functions to be created. If you have some suggestions feel free to contact me or create an issue.
Also if you find some implementation bug or have a suggestion please make an issue or a pull request. Thanks.
