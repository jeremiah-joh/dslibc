Data Structure Library for C
============================

This library provides a collection of commonly used data structures implemented
in C, adhering to the ISO/IEC 9899:1990 standard.

**Supported Data Structures:**

| Data Structure      | Header File | API Reference            |
|---------------------|-------------|--------------------------|
| Vector              | `vec.h`     | [`vec.md`](doc/vec.md)   |
| Singly Linked List  | `sll.h`     | [`sll.md`](doc/sll.md)   |
| Doubly Linked List  | `dll.h`     | [`dll.md`](doc/dll.md)   |
| Binary Heap         | `heap.h`    | [`heap.md`](doc/heap.md) |
| Hash Table          | `ht.h`      | [`ht.md`](doc/ht.md)     |

**Planned Data Structures:**

| Data Structure      | Header File | API Reference            |
|---------------------|-------------|--------------------------|
| Double-Ended Vector | `dev.h`     | [`dev.md`](doc/dev.md)   |
| AVL Tree            | `avl.h`     | [`avl.md`](doc/avl.md)   |
| B tree              | `bt.h`      | [`bt.md`](doc/bt.md)     |
| Red-Black Tree      | `rbt.h`     | [`rbt.md`](doc/rbt.md)   |
| Splay Tree          | `spt.h`     | [`spt.md`](doc/spt.md)   |

Installation (Optional)
-----------------------

To install the library, follow these steps:

1.  **Clone the repository:**

```sh
git clone https://github.com/jeremiah-joh/dslibc.git
```

2.  **Navigate to the project directory:**

```sh
cd dslibc
```

3.  **Install the headers:** (Requires root privileges)

```sh
make install
```

This will install the header files under `/usr/local/include`.
You could change the path where header files are installed by editing `config.h`
file.

Usage
-----

You can use this library with or without installation.

**Without Installation:**

Include the desired header file directly in your project directory.
For example, to use the vector implementation:

```c
#include "vec.h"
```

**With Installation:**

Once installed, include the header file like any other system header:

```c
#include <vec.h>
```

**Example:**

This example code demonstrates creating a vector and pushing integers from 0 to
15 into it:

```c
#include <vec.h>
#include <stdlib.h>

/* initialize vector type and its functions */
INIT_VEC_BOTH(int, int, malloc, realloc, free);

int
main(void)
{
    struct vec_int vec;
    int i;
    
    vec = vec_int_new();  /* initialize the vector */
    
    for (i = 0; i < 16; i++)
        vec_int_push(&vec, i);  /* push elements to the vector */
    
    /* here you can use the vector data for your needs */
    
    vec_int_free(&vec);  /* free the memory allocated by the vector */
    
    return 0;
}
```

License
-------

dslibc by Woohyun Joh is marked with CC0 1.0
