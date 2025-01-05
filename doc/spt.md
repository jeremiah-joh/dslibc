Splay Tree
==========

**UNIMPLEMENTED**

A splay tree that implements ordered dictionary. It accesses to the recently
accessed element faster.

Each macro parameters mean:

| parameter | description                          |
|-----------|--------------------------------------|
| `name`    | the name of data structure.          |
| `type`    | the type that data structure stores. |
| `cmp`     | returns subtraction of two inputs.   |
| `malloc`  | memory allocation function.          |
| `free`    | memory deallocation function.        |

INIT_SPT_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "spt.h"

INIT_SPT_TYPE(int, int);
```

INIT_SPT_FUNC(name, type, cmp, malloc, free)
--------------------------------------------

Initializes function definitions.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_FUNC(int, int, cmp, malloc, free);
```

INIT_SPT_BOTH(name, type, cmp, malloc, free)
--------------------------------------------

Initializes both structures and functions.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);
```

new
---

`struct spt_##name spt_##name##_new(void);`

Constructs an empty hash table.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;

spt = spt_int_new();
```

from
----


Constructs a hash table and fill it by `arr`\`s items.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };

spt = spt_int_from(arr, 5);
```

copy
----

`struct spt_##name spt_##name##_copy(const struct spt_##name *spt);`

Constructs a deeply copied hash table from 'spt'.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt1, spt2;
int arr[] = { 0, 1, 2, 3, 4 };

spt1 = spt_int_from(arr, 5);
spt2 = spt_int_copy(&spt1);
```

max
---

`int spt_##name##_max(struct spt_##name *spt, type *val);`

Gets the greatest element in `spt` and assigns it into `val`. It returns 0 on
success, -1 if `spt` is empty.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

spt_int_max(&spt, &val);
```

min
---

`int spt_##name##_min(struct spt_##name *spt, type *val);`

Gets the least element in `spt` and assigns it into `val`. It returns 0 on
success, -1 if `spt` is empty.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

spt_int_min(&spt, &val);
```

get
---

`int spt_##name##_get(struct spt_##name *spt, type *val);`

Gets an element in `spt` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

val = 3;
spt_int_get(&spt, &val);
```

set
---

`int spt_##name##_set(struct spt_###name *spt, const type val);`

Assigns `val` in `spt`. It returns 0 on success, -1 if there is no such value.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

val = 3;
spt_int_set(&spt, val);
```

insert
------

`int spt_##name##_insert(struct spt_##name *spt, const type val);`

Inserts `val` into `spt`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

val = 5;
spt_int_set(&spt, val);
```

remove
------

`int spt_##name##_remove(struct spt_##name *spt, type *val);`

Removes `val` from `spt`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);

val = 3;
spt_int_set(&spt, val);
```

len
---


Returns the length of `spt`.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };

spt = spt_int_from(arr, 5);
len = spt_int_len(&spt);
```

free
----

`void spt_##name##_free(struct spt_##name *spt);`

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };

spt = spt_int_from(arr, 5);

spt_int_free(&spt);
```

iter
----

`struct spt_##name##_iter spt_##name##_iter(spt_##name *spt);`

Constructs an iterator.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int_iter iter;
struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };

spt = spt_int_from(arr, 5);
iter = spt_int_iter(&spt);
```

next
----

`int spt_##name##_next(struct spt_##name##_iter *iter, type *val);`

Assigns a next value in hash table into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "spt.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_SPT_BOTH(int, int, cmp, malloc, free);

struct spt_int_iter iter;
struct spt_int spt;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

spt = spt_int_from(arr, 5);
iter = spt_int_iter(&spt);

spt_int_next(&iter, &val);
```
