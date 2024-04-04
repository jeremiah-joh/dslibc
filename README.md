Data Structure Library for C
============================

A collection of useful data structures written in ANSI C.  

Following data structures are implemented.
* Vector
* Singly Linked List
* Doubly Linked List
* Binary Search Tree

Following data structures are planned.
* AVL Tree
* Red-Black Tree
* Hash Table Map
* Hash Table Set

Usage
-----

First, copy header file into your project directory. And include it.

There are three macros for each data structures.  
These are for linear data structures.
* `INIT_<struct>_TYPE(name, type)` - Initialize type and function prototypes.
* `INIT_<struct>_FUNC(name, type)` - Initialize functions.
* `INIT_<struct>(name, type)` - Initialize type and functions.

These are for map data structures.
* `INIT_<struct>_TYPE(name, key_t, val_t)` - Initialize type and function prototypes.
* `INIT_<struct>_FUNC(name, key_t, val_t)` - Initialize functions.
* `INIT_<struct>(name, key_t, val_t)` - Initialize type and functions.

Use macro like follow.

```c
#include "vec.h"

INIT_VEC(age, int);

int
main()
{
	struct vec_age age;

	age = vec_age_new();

	vec_age_push_back(&age, 21);
	vec_age_push_back(&age, 32);

	/* do something more */

	vec_age_free(&age);

	return 0;
}
```

See `docs/` directory for details of each data structures and their functions.
