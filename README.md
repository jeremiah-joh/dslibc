Data Structure Library for C
============================

A collection of useful data structures written in ANSI C.

| data structure     | header  |
|--------------------|---------|
| Vector             | vec.h   |
| Singly Linked List | sll.h   |
| Doubly Linked List | dll.h   |
| Heap               | heap.h  |
| Hash Table         | ht.h    |

Installation
------------

Following commands will install these header files under `/usr/local/include`.

	$ git clone https://github.com/jeremiah-joh/dslibc.git
	$ cd dslibc
	# make install

Usage
-----

You could use this library with or without installation. If you don't want to
install, then just put one of these header files into your project directory.

Then, include the header file and use it. There is an [API document](doc).

Here is the example code that put integers from 0 to 16 into vector.

```c
#include <vec.h>
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free);

int
main(void)
{
	struct vec_int vec;
	int i;

	vec = vec_int_new();

	for (i = 0; i < 16; i++)
		vec_int_push(&vec, i);

	return 0;
}
```

License
-------

dslibc by Woohyun Joh is marked with CC0 1.0
