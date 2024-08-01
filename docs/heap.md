Binary Heap
===========

A binary heap to implement priority queue. It implements both maximum and
minimum heap.

Initialization
--------------

To use this data structure in your project, you need to copy the `heap.h`
header file into your project directory. Then, use following macros to
initialize data structure for your use case.
* `INIT_HEAP_TYPE(name, type);` - define struct and function prototypes.
* `INIT_MAX_HEAP_FUNC(name, type, cmp, malloc, realloc, free);` - define
functions of maximum heap.
* `INIT_MIN_HEAP_FUNC(name, type, cmp, malloc, realloc, free);` - define
functions of minimum heap.
* `INIT_MAX_HEAP(name, type, cmp, malloc, realloc, free);` - define both at
once.
* `INIT_MIN_HEAP(name, type, cmp, malloc, realloc, free);` - define both at
once.

Here are the descriptions of each parameters.
* `name` - the name of data structure, generates `struct heap_name`.
* `type` - type of data in the data structure.
* `cmp` - comparison function. returns subtraction of two data.
* `malloc` - memory allocating function.
* `realloc` - memory re-allocating function.
* `free` - memory deallocation function.
