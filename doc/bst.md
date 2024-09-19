Binary Search Tree
==================

A binary search tree that implements dictionary.

INIT_BST_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "bst.h"

INIT_BST_TYPE(int, int)
```

INIT_BST_FUNC(name, type, cmp, malloc, free)
--------------------------------------------

Initializes function definitions.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_FUNC(int, int, cmp, malloc, free)
```

INIT_BST_BOTH(name, type, cmp, malloc, free)
--------------------------------------------

Initializes both structures and functions.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)
```

new
---

`struct bst_##name bst_##name##_new(void);`

Constructs an empty binary search tree.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;

bst = bst_int_new();
```

from
----

`struct bst_##name bst_##name##_from(const type *arr, const size_t len);`

Constructs a binary search tree and fill it by `arr`\`s items.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };

bst = bst_int_from(arr, 5);
```

copy
----

`struct bst_##name bst_##name##_copy(const struct bst_##name *bst);`

Constructs a deeply copied binary search tree from 'bst'.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst1, bst2;
int arr[] = { 3, 4, 1, 0, 2 };

bst1 = bst_int_from(arr, 5);
bst2 = bst_int_copy(&bst1);
```

root
----

`int bst_##name##_root(struct bst_##name *bst, type *val);`

Assigns the value in root node into 'val'. It return 0 on success, -1 if the
binary search tree is empty.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

bst_int_root(&bst, &val);
```

max
---

`int bst_##name##_max(struct bst_##name *bst, type *val);`

Assigns the maximum value in tree node into 'val'. It return 0 on success, -1 if
the binary search tree is empty.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

bst_int_max(&bst, &val);
```

min
---

`int bst_##name##_min(struct bst_##name *bst, type *val);`

Assigns the minimum value in tree node into 'val'. It return 0 on success, -1 if
the binary search tree is empty.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

bst_int_min(&bst, &val);
```

get
---

`int bst_##name##_get(struct bst_##name *bst, type *val);`

Gets an element in `bst` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

val = 3;
bst_int_get(&bst, &val);
```

set
---

`int bst_##name##_set(struct bst_###name *bst, const type val);`

Assigns `val` in `bst`. It returns 0 on success, -1 if there is no such value.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

val = 3;
bst_int_set(&bst, val);
```

insert
------

`int bst_##name##_insert(struct bst_##name *bst, const type val);`

Inserts `val` into `bst`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

val = 5;
bst_int_set(&bst, val);
```

remove
------

`int bst_##name##_remove(struct bst_##name *bst, type *val);`

Removes `val` from `bst`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);

val = 3;
bst_int_set(&bst, val);
```

length
------

`size_t bst_##name##_length(struct bst_##name *bst);`

Returns the length of `bst`.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
size_t len;

bst = bst_int_from(arr, 5);
len = bst_int_length(&bst);
```

sizeof
------

`size_t bst_##name##_sizeof(struct bst_##name *bst);`

Retruns the amount of bytes that `bst` is occuping.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
size_t size;

bst = bst_int_from(arr, 5);
size = bst_int_sizeof(&bst);
```
free
----

`void bst_##name##_free(struct bst_##name *bst);`

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };

bst = bst_int_from(arr, 5);

bst_int_free(&bst);
```

iter
----

`struct bst_##name##_iter bst_##name##_iter(bst_##name *bst);`

Constructs an iterator.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int_iter iter;
struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };

bst = bst_int_from(arr, 5);
iter = bst_int_iter(&bst);
```

next
----

`int bst_##name##_next(struct bst_##name##_iter *iter, type *val);`

Assigns a next value in binary search tree into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "bst.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int_iter iter;
struct bst_int bst;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);
iter = bst_int_iter(&bst);

bst_int_next(&iter, &val);
```

FOR_EACH_BST(name, elem, iter)
-----------------------------

Traverses each elements in `iter` of binary search tree.

```c
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

struct bst_int bst;
struct bst_int_iter iter;
int arr[] = { 3, 4, 1, 0, 2 };
int val;

bst = bst_int_from(arr, 5);
iter = bst_int_iter(&bst);

FOR_EACH_BST(int, val, iter) {
	printf("%d\n", val);
}
```
