Binary search tree
==================

A plain binary search tree.

It has following time complexities for each operations.
| Operation | Best case | Worst case |
|-----------|-----------|------------|
| insert    | O(log n)  | O(n)       |
| remove    | O(log n)  | O(n)       |
| search    | O(log n)  | O(n)       |

Initialization
--------------

To use this data structure in your project, you need to copy the `bst.h` header
file into your project directory. Then, use following macros to initialize data
structure for your use case.
* `INIT_BST_TYPE(name, type);` - define struct and function prototypes.
* `INIT_BST_FUNC(name, type, cmp, malloc, free);` - define functions.
* `INIT_BST(name, type, cmp, malloc, free);` - define both at once.

Here are the descriptions of each parameters.
* `name` - the name of data structure, generates `struct bst_name`.
* `type` - type of data in the data structure.
* `cmp` - comparison function. returns subtraction of two data.
* `malloc` - memory allocating function.
* `free` - memory deallocation function.

new
---

`struct bst_##name bst_##name##_new()`

Creates an empty binary search tree.

```c
#include "bst.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

struct bst_int bst = bst_int_new();
```

from
----

`struct bst_##name bst_##name##_from(const type data[], const size_t len)`

Creates a binary search tree from an array of data.

```c
#include "bst.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);
```

copy
----

`struct bst_##name bst_##name##_copy(const struct bst_##name bst)`

Creates a deeply copied binary search tree from given tree.

```c
#include "bst.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);
struct bst_int cpy = bst_int_copy(bst);
```

insert
------

`int bst_##name##_insert(struct bst_##name *bst, const type data)`

Inserts given data into binary search tree. It returns 0 on success, -1 when
given data is already in the tree or memory allocation is failed.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

struct bst_int bst = bst_int_new();

assert(bst_int_insert(&bst, 1) == 0);
assert(bst_int_insert(&bst, 2) == 0);
assert(bst_int_insert(&bst, 3) == 0);
assert(bst.len == 3);
```

search
------

`int bst_##name##_search(struct bst_##name *bst, type *data)`

Searches given data from binary search tree and assign back to the pointer.
It returns 0 on success, -1 when there is no given data in tree.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

v = 1;
assert(bst_int_search(&bst, &v) == 0);
v = 2;
assert(bst_int_search(&bst, &v) == 0);
v = 3;
assert(bst_int_search(&bst, &v) == 0);
```

remove
------

`int bst_##name##_remove(struct bst_##name *bst, type *data)`

Removes given data from binary search tree and assign back to the pointer.
It returns 0 on success, -1 when there is no given data in tree.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

v = 1;
assert(bst_int_remove(&bst, &v) == 0);
v = 2;
assert(bst_int_remove(&bst, &v) == 0);
v = 3;
assert(bst_int_remove(&bst, &v) == 0);
assert(bst.len == 0);
```

root
----

`int bst_##name##_root(struct bst_##name *bst, type *data)`

Gets the root data of binary search tree. It returns 0 on success, -1 when tree
is empty.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

assert(bst_int_root(&bst, &v) == 0);
assert(v == 1);
```

max
---

`int bst_##name##_max(struct bst_##name *bst, type *data)`

Gets the greates data in binary search tree. It returns 0 on success, -1 when
tree is empty.
```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

assert(bst_int_max(&bst, &v) == 0);
assert(v == 5);
```

min
---

`int bst_##name##_min(struct bst_##name *bst, type *data)`

Gets the least data in binary search tree. It returns 0 on success, -1 when
tree is empty.
```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

assert(bst_int_min(&bst, &v) == 0);
assert(v == 0);
```

free
----

`void bst_##name##_free(struct bst_##name *bst)`

Frees binary search tree from memory, assigns NULL every nodes to prevent
use-after-free.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct bst_int bst = bst_int_from(data, 5);

bst_int_free(&bst);

assert(bst.root == NULL);
assert(bst.len == 0);
```

iter
----

`struct bst_##name##_iter bst_##name##_iter(struct bst_##name *bst)`

Creates an iterator for binary search tree.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int data[] = { 1, 2, 3 };
struct bst_int bst = bst_int_from(data, 3);
struct bst_int_iter iter = bst_int_iter(&bst);
```

getnxt
------

`int bst_##name##_getnxt(struct bst_##name##_iter *iter)`

Gets a next data.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3 };
struct bst_int bst = bst_int_from(data, 3);
struct bst_int_iter iter = bst_int_iter(&bst);

assert(bst_int_getnxt(&iter, &v) == 0);
assert(v == 1);
assert(bst_int_getnxt(&iter, &v) == 0);
assert(v == 2);
assert(bst_int_getnxt(&iter, &v) == 0);
assert(v == 3);
assert(bst_int_getnxt(&iter, &v) != 0);
```

FOR_EACH
--------

`FOR_EACH(name, item, iter)`

Iterates every data in depth-first-search order.

```c
#include "bst.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int cmp_int(int x, int y) { return x - y; };

INIT_BST(int, int, cmp_int, malloc, free);

int i;
int data[] = { 1, 2, 3 };
struct bst_int bst = bst_int_from(data, 3);
struct bst_int_iter iter = bst_int_iter(&bst);

FOR_EACH(int, i, iter) {
	printf("%d\n", i);
}
```
