AVL Tree
========

**UNIMPLEMENTED**

An AVL tree that implements ordered dictionary.

Each macro parameters mean:

| parameter | description                          |
|-----------|--------------------------------------|
| `name`    | the name of data structure.          |
| `type`    | the type that data structure stores. |
| `cmp`     | returns subtraction of two inputs.   |
| `malloc`  | memory allocation function.          |
| `free`    | memory deallocation function.        |

INIT_AVL_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "avl.h"

INIT_AVL_TYPE(int, int);
```

INIT_AVL_FUNC(name, type, cmp, malloc, free)
--------------------------------------------

Initializes function definitions.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_FUNC(int, int, cmp, malloc, free);
```

INIT_AVL_BOTH(name, type, cmp, malloc, free)
--------------------------------------------

Initializes both structures and functions.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);
```

new
---

`struct avl_##name avl_##name##_new(void);`

Constructs an empty hash table.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;

avl = avl_int_new();
```

from
----


Constructs a hash table and fill it by `arr`\`s items.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };

avl = avl_int_from(arr, 5);
```

copy
----

`struct avl_##name avl_##name##_copy(const struct avl_##name *avl);`

Constructs a deeply copied hash table from 'avl'.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl1, avl2;
int arr[] = { 0, 1, 2, 3, 4 };

avl1 = avl_int_from(arr, 5);
avl2 = avl_int_copy(&avl1);
```

max
---

`int avl_##name##_max(struct avl_##name *avl, type *val);`

Gets the greatest element in `avl` and assigns it into `val`. It returns 0 on
success, -1 if `avl` is empty.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

avl_int_max(&avl, &val);
```

min
---

`int avl_##name##_min(struct avl_##name *avl, type *val);`

Gets the least element in `avl` and assigns it into `val`. It returns 0 on
success, -1 if `avl` is empty.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

avl_int_min(&avl, &val);
```

get
---

`int avl_##name##_get(struct avl_##name *avl, type *val);`

Gets an element in `avl` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

val = 3;
avl_int_get(&avl, &val);
```

set
---

`int avl_##name##_set(struct avl_###name *avl, const type val);`

Assigns `val` in `avl`. It returns 0 on success, -1 if there is no such value.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

val = 3;
avl_int_set(&avl, val);
```

insert
------

`int avl_##name##_insert(struct avl_##name *avl, const type val);`

Inserts `val` into `avl`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

val = 5;
avl_int_set(&avl, val);
```

remove
------

`int avl_##name##_remove(struct avl_##name *avl, type *val);`

Removes `val` from `avl`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);

val = 3;
avl_int_set(&avl, val);
```

len
---


Returns the length of `avl`.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };

avl = avl_int_from(arr, 5);
len = avl_int_len(&avl);
```

free
----

`void avl_##name##_free(struct avl_##name *avl);`

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };

avl = avl_int_from(arr, 5);

avl_int_free(&avl);
```

iter
----

`struct avl_##name##_iter avl_##name##_iter(avl_##name *avl);`

Constructs an iterator.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int_iter iter;
struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };

avl = avl_int_from(arr, 5);
iter = avl_int_iter(&avl);
```

next
----

`int avl_##name##_next(struct avl_##name##_iter *iter, type *val);`

Assigns a next value in hash table into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "avl.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_AVL_BOTH(int, int, cmp, malloc, free);

struct avl_int_iter iter;
struct avl_int avl;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

avl = avl_int_from(arr, 5);
iter = avl_int_iter(&avl);

avl_int_next(&iter, &val);
```
