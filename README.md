Data Structure Library for C
============================

A collection of useful data structures written in ANSI C.  

Following data structures are implemented.
* Vector
* Singly Linked List
* Doubly Linked List
* Binary Search Tree

Following data strucuters are planned.
* AVL Tree
* Red-Black Tree
* Hash Table Map
* Hash Table Set

Basic Usage
-----------

First, copy header file into your project directory.

There are three macros for each data structures.
* `INIT_<name>_TYPE` - Intitialize type of data structure. Use in header file.
* `INIT_<name>_FUNC` - Intitialize functions of data strucutre. Use in source file.
* `INIT_<name>` - Do both of them.

Use macro like follow.
```c
INIT_VEC_TYPE(age, int);
INIT_VEC_FUNC(age, int);
```

or

```c
INIT_VEC(age, int);
```

Then you can use `struct vec_age` and its functions.  
See `docs/` directory for details of each data structures and their functions.
