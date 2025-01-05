Double Ended Vector
===================

**UNIMPLEMENTED**

A growable circular array that implements double-ended queue.

Each macro parameters mean:

| parameter | description                          |
|-----------|--------------------------------------|
| `name`    | the name of data structure.          |
| `type`    | the type that data structure stores. |
| `malloc`  | memory allocation function.          |
| `realloc` | memory reallocation function.        |
| `free`    | memory deallocation function.        |

INIT_DEV_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "dev.h"

INIT_DEV_TYPE(int, int);
```

INIT_DEV_FUNC(name, type, malloc, free)
---------------------------------------

Initializes function definitions.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_FUNC(int, int, malloc, free);
```

INIT_DEV_BOTH(name, type, malloc, free)
---------------------------------------

Initializes both structures and functions.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);
```

new
---

`struct dev_##name dev_##name##_new(void);`

Constructs a new, empty linked list.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;

dev = dev_int_new();
```

from
----

`struct dev_##name dev_##name##_from(const type *arr, const unsigned long len);`

Allocate a linked list and fill it by `arr`\`s items.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
```

copy
----

`struct dev_##name dev_##name##_copy(const struct dev_##name *dev);`

Constructs a deeply copied linked list from given `dev`.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev1, dev2;
int arr[] = { 0, 1, 2, 3, 4 };

dev1 = dev_int_from(arr, 5);
dev2 = dev_int_copy(&dev2);
```

push_back
---------

`int dev_##name##_push(struct dev_##name *dev, const type val);`

Appends an element `val` to the back of the `dev`. It returns -1 as error if
memory allocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
dev_int_push_back(&dev, 5);
```

pop_back
--------

`int dev_##name##_pop(struct dev_##name *dev, type *val);`

Removes the last element from the `dev` and assigns into `val`. It returns -1
as error if memory deallocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dev = dev_int_from(arr, 5);
dev_int_pop_back(&dev, &val);
```

push_front
----------

`int dev_##name##_push(struct dev_##name *dev, const type val);`

Appends an element `val` to the front of the `dev`. It returns -1 as error if
memory allocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
dev_int_push_front(&dev, 5);
```

pop_front
---------

`int dev_##name##_pop(struct dev_##name *dev, type *val);`

Removes the first element from the `dev` and assigns into `val`. It returns -1
as error if memory deallocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dev = dev_int_from(arr, 5);
dev_int_pop_front(&dev, &val);
```

get
---

`int dev_##name##_get(struct dev_##name *dev, type *val, const unsigned long idx);`

Assigns the element at `idx` into `val` in `dev`. It returs -1 as error if the
`idx` is out of range.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dev = dev_int_from(arr, 5);
dev_int_get(&dev, &val, 3);
```

set
---

`int dev_##name##_set(struct dev_##name *dev, const type val, const unsigned long len);`

Assigns the `val` at `idx` in `dev`. It returns -1 as error if the `idx` is out
of range.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
dev_int_get(&dev, 0, 3);
```

append
------

`int dev_##name##_append(struct dev_##name *dev, const type *arr, const unsigned long len);`

Appends an `arr` to the back of the `dev`. It returns -1 as error if memory
allocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
dev_int_append(&dev, arr, 5);
```

insert
------

`int dev_##name##_insert(struct dev_##name *dev, const type val, const unsigned long idx);`

Inserts the `val` to the `idx` in `dev`. It returns -1 as error if `idx` is out
of range or memory allocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 3, 4 };

dev = dev_int_from(arr, 4);
dev_int_insert(&dev, 2, 2);
```

remove
------

`int dev_##name##_remove(struct dev_##name *dev, type *val, const unsigned long idx);`

Removes the element at the `idx` and assigns it into `val`. It returns -1 as
error if `idx` is out of range or memory deallocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dev = dev_int_from(arr, 4);
dev_int_remove(&dev, &val, 2);
```

shrink
------

`int dev_##name##_shrink(struct dev_##name *dev, const unsigned long len);`

Shrinks the length of `dev` to `len`. It returns -1 as erro if `len` is greater
than the length of `dev` or memory deallocation is failed.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 4);
dev_int_shrink(&dev, 3);
```

len
---

`unsigned long dev_##name##_len(struct dev_##name *dev);`

Returns the length of `dev`.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };
unsigned long len;

dev = dev_int_from(arr, 4);
len = dev_int_len(&dev);
```

free
----

`void dev_##name##_free(struct dev_##name *dev);`

Deallocates the `dev` from memory and fills NULL and zeros into the internal
fields to prevent use-after-free.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 4);
dev_int_free(&dev);
```

iter
----

`struct dev_##name##_iter dev_##name##_iter(struct dev_##name *dev);`

Constructs an iterator of `dev`.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
struct dev_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };

dev = dev_int_from(arr, 5);
iter = dev_int_iter(&dev);
```

next
----

`int dev_##name##_next(struct dev_##name##_iter *iter, type *val);`

Assigns the next element in `dev` into `val`. It returns -1 as error if the end
of range is reached.

```c
#include "dev.h"
#include <stdlib.h>

INIT_DEV_BOTH(int, int, malloc, free);

struct dev_int dev;
struct dev_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dev = dev_int_from(arr, 5);
iter = dev_int_iter(&dev);

dev_int_next(&iter, &val);
```
