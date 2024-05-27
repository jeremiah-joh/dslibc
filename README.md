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
* B-Tree
* Hash Table

Usage
-----

Here is a simple example code that uses `vec.h`.

```c
#include "vec.h"

INIT_VEC(int, int);

int
main()
{
	struct vec_int vec;

	vec = vec_int_new();

	vec_int_push_back(&vec, 21);
	vec_int_push_back(&vec, 32);

	/* do something more */

	vec_int_free(&vec);

	return 0;
}
```

See [`docs/`](docs/) directory for details of each data structures.

