# Dusan Djordjic's clibs

## Disclaimer

This project and all libraries it links to are in development and should not be used in production enviroments. I made them as fun side project and useful tools that I can use in my other fun side projects. 

If you find a bug or have some sugestions feel free to make a pull request.

<hr>

This is a collection of basic c libraries that I made and maintain. I use these libraries in my other projects like [dont_forget](https://github.com/DusanDjordjic/dont-forget). 

Every library is it's own folder. They are build individualy and used individualy. This project just groups them and provides a Makefile that runs nested Makefiles. Makefile builds a specific library (or all of them) and puts the lib files in the `./lib` folder and a header files in the `./lib/include` folder so thay can be easily accessed and used by other programs.

**IMPORTANT** Master branch holds the latest release. There are also relese branches so you can pick any version you want. On develop branch code is not fully tested and not production ready so use it with caution. 

## List of libraries

| Name         | Description                                                         | Status        |
| ------------ | ------------------------------------------------------------------- | ------------- |
| **vector-c** | Simple implementation of a generic dynamic array                    | Development   |
| **io-c**     | Set of function for reading and writing from and to input streams   | Development   |

## Todos 
- [ ] *all* : add dynamic library build support.
- [ ] *all* : add testing library and make tests.
- [X] *vector-c* : add *get* function that gets an item at some index.
- [X] *vector-c* : add *replace* function that replaces as item at some index.
- [ ] *vector-c* : add *shift* and *unshift* functions.
- [ ] *io-c* : add functions for writing.
- [ ] *io-c* : add *FILE\* stream* parameter so the user can specify the io stream.
- [ ] *btree-c* : make binary tree library.
- [ ] *tree-c* : make tree library.

### Notes 

- Vector-c should be able to function as normal generic dynamic array, stack and queue in the same time. Depending on your use case feel free use it as you see fit. 
- Io-c should provide functions for reading and writing to any stream. Writing should be generic.
