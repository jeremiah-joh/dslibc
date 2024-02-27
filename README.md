Data Structure Library for C
============================

A collection of useful data structures written in ANSI C.

Data structures
---------------

| File name | Data structure name | Insert | Remove | Search | State |
|:---------:|---------------------|--------|--------|--------|-------|
| vec.h | Vector (Double-Ended Queue) | O(n) | O(n) | O(1) | O |
| ll.h | (Doubly, Singly) Linked List | O(1) | O(n) | O(n) | X |
| avl.h | AVL tree | O(log n) | O(log n) | O(log n) | X |
| rb.h | Red-Black tree | O(log n) | O(log n) | O(log n) | X |
| splay.h | Splay tree | O(log n) ~ O(n) | O(log n) ~ O(n) | O(log n) ~ O(n) | X |
| ht.h | Hash table | O(1) ~ O(n) | O(1) ~ O(n) | O(1) ~ O(n) | X |

Usage
-------

First, download one of those files and put it into your project's directory.
Let's say it is `vec.h`.

```c
#include "vec.h"

struct your_struct {
    /* fields */
};

INIT_VEC(your_struct, struct your_struct);

int
main()
{
    vec_your_struct vec = vec_your_struct_new();

    /* your code */

    return 0;
}
```
