Singly Linked List
==================

A singly linked list that implements queue.

INIT_SLL_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
INIT_SLL_TYPE(int, int)
```

INIT_SLL_FUNC(name, type, malloc, free)
------------------------------------------------

Initializes function definitions.

```c
#include <stdlib.h>

INIT_SLL_FUNC(int, int, malloc, free)
```

INIT_SLL_BOTH(name, type, malloc, free)
------------------------------------------------

Initializes both structures and functions.

```c
#include <stdlib.h>

INIT_SLL_FUNC(int, int, malloc, free)
```

new
---

`struct sll_##name sll_##name##_new(void);`

Constructs a new, empty linked list.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;

sll = sll_int_new();
```

from
----

`struct sll_##name sll_##name##_from(const type *arr, const size_t len);`

Allocate a linked list and fill it by `arr`\`s items.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 5);
```

copy
----

`struct sll_##name sll_##name##_copy(const struct sll_##name *sll);`

Constructs a deeply copied linked list from given `sll`.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll1, sll2;
int arr[] = { 0, 1, 2, 3, 4 };

sll1 = sll_int_from(arr, 5);
sll2 = sll_int_copy(&sll2);
```

push
----

`int sll_##name##_push(struct sll_##name *sll, const type val);`

Appends an element `val` to the back of the `sll`. It returns -1 as error if
memory reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 5);
sll_int_push(&sll, 5);
```

pop
---

`int sll_##name##_pop(struct sll_##name *sll, type *val);`

Removes the first element from the `sll` and assigns into `val`. It returns -1
as error if memory reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

sll = sll_int_from(arr, 5);
sll_int_pop(&sll, &val);
```

get
---

`int sll_##name##_get(struct sll_##name *sll, type *val, const size_t idx);`

Assigns the element at `idx` into `val` in `sll`. It returs -1 as error if the
`idx` is out of range.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

sll = sll_int_from(arr, 5);
sll_int_get(&sll, &val, 3);
```

set
---

`int sll_##name##_set(struct sll_##name *sll, const type val, const size_t len);`

Assigns the `val` at `idx` in `sll`. It returns -1 as error if the `idx` is out
of range.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 5);
sll_int_get(&sll, 0, 3);
```

append
------

`int sll_##name##_append(struct sll_##name *sll, const type *arr, const size_t len);`

Appends an `arr` to the back of the `sll`. It returns -1 as error if memory
reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 5);
sll_int_append(&sll, arr, 5);
```

insert
------

`int sll_##name##_insert(struct sll_##name *sll, const type val, const size_t idx);`

Inserts the `val` to the `idx` in `sll`. It returns -1 as error if `idx` is out
of range or memory reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 3, 4 };

sll = sll_int_from(arr, 4);
sll_int_insert(&sll, 2, 2);
```

remove
------

`int sll_##name##_remove(struct sll_##name *sll, type *val, const size_t idx);`

Removes the element at the `idx` and assigns it into `val`. It returns -1 as
error if `idx` is out of range or memory reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

sll = sll_int_from(arr, 4);
sll_int_remove(&sll, &val, 2);
```

shrink
------

`int sll_##name##_shrink(struct sll_##name *sll, const size_t len);`

Shrinks the length of `sll` to `len`. It returns -1 as erro if `len` is greater
than the length of `sll` or memory reallocation is failed.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 4);
sll_int_shrink(&sll, 3);
```

length
------

`size_t sll_##name##_length(struct sll_##name *sll);`

Returns the length of `sll`.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };
size_t len;

sll = sll_int_from(arr, 4);
len = sll_int_length(&sll);
```

sizeof
------

`size_t sll_##name##_sizeof(struct sll_##name *sll);`

Retruns the amount of bytes that `sll` is occuping.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };
size_t size;

sll = sll_int_from(arr, 4);
size = sll_int_sizeof(&sll);
```

free
----

`void sll_##name##_free(struct sll_##name *sll);`

Deallocates the `sll` from memory and fills NULL and zeros into the internal
fields to prevent use-after-free.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 4);
sll_int_free(&sll);
```

iter
----

`struct sll_##name##_iter sll_##name##_iter(struct sll_##name *sll);`

Constructs an iterator of `sll`.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
struct sll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };

sll = sll_int_from(arr, 5);
iter = sll_int_iter(&sll);
```

next
----

`int sll_##name##_next(struct sll_##name##_iter *iter, type *val);`

Assigns the next element in `sll` into `val`. It returns -1 as error if the end
of range is reached.

```c
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
struct sll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

sll = sll_int_from(arr, 5);
iter = sll_int_iter(&sll);

sll_int_next(&iter, &val);
```

FOR_EACH_SLL(name, elem, iter)
------------------------------

Traverses each elements in `iter` of linked list.

```c
#include <stdio.h>
#include <stdlib.h>

INIT_SLL_BOTH(int, int, malloc, free)

struct sll_int sll;
struct sll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

sll = sll_int_from(arr, 5);
iter = sll_int_iter(&sll);

FOR_EACH_SLL(int, val, iter) {
	printf("%d\n", val);
}
```
