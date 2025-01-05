B-Tree
======

**UNIMPLEMENTED**

A b-tree that implements ordered dictionary. It is cache efficient.

Each macro parameters mean:

| parameter | description                          |
|-----------|--------------------------------------|
| `name`    | the name of data structure.          |
| `type`    | the type that data structure stores. |
| `ord`     | maximum number of child pointers.    |
| `cmp`     | returns subtraction of two inputs.   |
| `malloc`  | memory allocation function.          |
| `free`    | memory deallocation function.        |

INIT_BT_TYPE(name, type, ord)
-----------------------------

Initializes structures and function prototypes.

```c
#include "bt.h"

INIT_BT_TYPE(int, int);
```

INIT_BT_FUNC(name, type, ord, cmp, malloc, free)
------------------------------------------------

Initializes function definitions.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_FUNC(int, int, 5, cmp, malloc, free);
```

INIT_BT_BOTH(name, type, ord, cmp, malloc, free)
------------------------------------------------

Initializes both structures and functions.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);
```

new
---

`struct bt_##name bt_##name##_new(void);`

Constructs an empty hash table.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;

bt = bt_int_new();
```

from
----


Constructs a hash table and fill it by `arr`\`s items.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };

bt = bt_int_from(arr, 5);
```

copy
----

`struct bt_##name bt_##name##_copy(const struct bt_##name *bt);`

Constructs a deeply copied hash table from 'bt'.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt1, bt2;
int arr[] = { 0, 1, 2, 3, 4 };

bt1 = bt_int_from(arr, 5);
bt2 = bt_int_copy(&bt1);
```

max
---

`int bt_##name##_max(struct bt_##name *bt, type *val);`

Gets the greatest element in `bt` and assigns it into `val`. It returns 0 on
success, -1 if `bt` is empty.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

bt_int_max(&bt, &val);
```

min
---

`int bt_##name##_min(struct bt_##name *bt, type *val);`

Gets the least element in `bt` and assigns it into `val`. It returns 0 on
success, -1 if `bt` is empty.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

bt_int_min(&bt, &val);
```

get
---

`int bt_##name##_get(struct bt_##name *bt, type *val);`

Gets an element in `bt` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

val = 3;
bt_int_get(&bt, &val);
```

set
---

`int bt_##name##_set(struct bt_###name *bt, const type val);`

Assigns `val` in `bt`. It returns 0 on success, -1 if there is no such value.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

val = 3;
bt_int_set(&bt, val);
```

insert
------

`int bt_##name##_insert(struct bt_##name *bt, const type val);`

Inserts `val` into `bt`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

val = 5;
bt_int_set(&bt, val);
```

remove
------

`int bt_##name##_remove(struct bt_##name *bt, type *val);`

Removes `val` from `bt`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);

val = 3;
bt_int_set(&bt, val);
```

len
---


Returns the length of `bt`.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };

bt = bt_int_from(arr, 5);
len = bt_int_len(&bt);
```

free
----

`void bt_##name##_free(struct bt_##name *bt);`

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };

bt = bt_int_from(arr, 5);

bt_int_free(&bt);
```

iter
----

`struct bt_##name##_iter bt_##name##_iter(bt_##name *bt);`

Constructs an iterator.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int_iter iter;
struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };

bt = bt_int_from(arr, 5);
iter = bt_int_iter(&bt);
```

next
----

`int bt_##name##_next(struct bt_##name##_iter *iter, type *val);`

Assigns a next value in hash table into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "bt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_BT_BOTH(int, int, 5, cmp, malloc, free);

struct bt_int_iter iter;
struct bt_int bt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

bt = bt_int_from(arr, 5);
iter = bt_int_iter(&bt);

bt_int_next(&iter, &val);
```
