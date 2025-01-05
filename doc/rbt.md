Red-Black Tree
==============

**UNIMPLEMENTED**

A red-black tree that implements ordered dictionary.

Each macro parameters mean:

| parameter | description                          |
|-----------|--------------------------------------|
| `name`    | the name of data structure.          |
| `type`    | the type that data structure stores. |
| `cmp`     | returns subtraction of two inputs.   |
| `malloc`  | memory allocation function.          |
| `free`    | memory deallocation function.        |

INIT_RBT_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "rbt.h"

INIT_RBT_TYPE(int, int);
```

INIT_RBT_FUNC(name, type, cmp, malloc, free)
--------------------------------------------

Initializes function definitions.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_FUNC(int, int, cmp, malloc, free);
```

INIT_RBT_BOTH(name, type, cmp, malloc, free)
--------------------------------------------

Initializes both structures and functions.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);
```

new
---

`struct rbt_##name rbt_##name##_new(void);`

Constructs an empty hash table.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;

rbt = rbt_int_new();
```

from
----


Constructs a hash table and fill it by `arr`\`s items.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };

rbt = rbt_int_from(arr, 5);
```

copy
----

`struct rbt_##name rbt_##name##_copy(const struct rbt_##name *rbt);`

Constructs a deeply copied hash table from 'rbt'.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt1, rbt2;
int arr[] = { 0, 1, 2, 3, 4 };

rbt1 = rbt_int_from(arr, 5);
rbt2 = rbt_int_copy(&rbt1);
```

max
---

`int rbt_##name##_max(struct rbt_##name *rbt, type *val);`

Gets the greatest element in `rbt` and assigns it into `val`. It returns 0 on
success, -1 if `rbt` is empty.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

rbt_int_max(&rbt, &val);
```

min
---

`int rbt_##name##_min(struct rbt_##name *rbt, type *val);`

Gets the least element in `rbt` and assigns it into `val`. It returns 0 on
success, -1 if `rbt` is empty.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

rbt_int_min(&rbt, &val);
```

get
---

`int rbt_##name##_get(struct rbt_##name *rbt, type *val);`

Gets an element in `rbt` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

val = 3;
rbt_int_get(&rbt, &val);
```

set
---

`int rbt_##name##_set(struct rbt_###name *rbt, const type val);`

Assigns `val` in `rbt`. It returns 0 on success, -1 if there is no such value.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

val = 3;
rbt_int_set(&rbt, val);
```

insert
------

`int rbt_##name##_insert(struct rbt_##name *rbt, const type val);`

Inserts `val` into `rbt`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

val = 5;
rbt_int_set(&rbt, val);
```

remove
------

`int rbt_##name##_remove(struct rbt_##name *rbt, type *val);`

Removes `val` from `rbt`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);

val = 3;
rbt_int_set(&rbt, val);
```

len
---


Returns the length of `rbt`.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };

rbt = rbt_int_from(arr, 5);
len = rbt_int_len(&rbt);
```

free
----

`void rbt_##name##_free(struct rbt_##name *rbt);`

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };

rbt = rbt_int_from(arr, 5);

rbt_int_free(&rbt);
```

iter
----

`struct rbt_##name##_iter rbt_##name##_iter(rbt_##name *rbt);`

Constructs an iterator.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int_iter iter;
struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };

rbt = rbt_int_from(arr, 5);
iter = rbt_int_iter(&rbt);
```

next
----

`int rbt_##name##_next(struct rbt_##name##_iter *iter, type *val);`

Assigns a next value in hash table into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "rbt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

struct rbt_int_iter iter;
struct rbt_int rbt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

rbt = rbt_int_from(arr, 5);
iter = rbt_int_iter(&rbt);

rbt_int_next(&iter, &val);
```
