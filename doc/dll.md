Doubly Linked List
==================

A doubly linked list that implements double-ended queue.

INIT_DLL_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
INIT_DLL_TYPE(int, int)
```

INIT_DLL_FUNC(name, type, malloc, free)
------------------------------------------------

Initializes function definitions.

```c
#include <stdlib.h>

INIT_DLL_FUNC(int, int, malloc, free)
```

INIT_DLL_BOTH(name, type, malloc, free)
------------------------------------------------

Initializes both structures and functions.

```c
#include <stdlib.h>

INIT_DLL_FUNC(int, int, malloc, free)
```

new
---

`struct dll_##name dll_##name##_new(void);`

Constructs a new, empty linked list.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;

dll = dll_int_new();
```

from
----

`struct dll_##name dll_##name##_from(const type *arr, const size_t len);`

Allocate a linked list and fill it by `arr`\`s items.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
```

copy
----

`struct dll_##name dll_##name##_copy(const struct dll_##name *dll);`

Constructs a deeply copied linked list from given `dll`.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll1, dll2;
int arr[] = { 0, 1, 2, 3, 4 };

dll1 = dll_int_from(arr, 5);
dll2 = dll_int_copy(&dll2);
```

push_back
---------

`int dll_##name##_push(struct dll_##name *dll, const type val);`

Appends an element `val` to the back of the `dll`. It returns -1 as error if
memory allocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
dll_int_push_back(&dll, 5);
```

pop_back
--------

`int dll_##name##_pop(struct dll_##name *dll, type *val);`

Removes the last element from the `dll` and assigns into `val`. It returns -1
as error if memory deallocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 5);
dll_int_pop_back(&dll, &val);
```

push_front
----------

`int dll_##name##_push(struct dll_##name *dll, const type val);`

Appends an element `val` to the front of the `dll`. It returns -1 as error if
memory allocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
dll_int_push_front(&dll, 5);
```

pop_front
---------

`int dll_##name##_pop(struct dll_##name *dll, type *val);`

Removes the first element from the `dll` and assigns into `val`. It returns -1
as error if memory deallocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 5);
dll_int_pop_front(&dll, &val);
```

get
---

`int dll_##name##_get(struct dll_##name *dll, type *val, const size_t idx);`

Assigns the element at `idx` into `val` in `dll`. It returs -1 as error if the
`idx` is out of range.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 5);
dll_int_get(&dll, &val, 3);
```

set
---

`int dll_##name##_set(struct dll_##name *dll, const type val, const size_t len);`

Assigns the `val` at `idx` in `dll`. It returns -1 as error if the `idx` is out
of range.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
dll_int_get(&dll, 0, 3);
```

append
------

`int dll_##name##_append(struct dll_##name *dll, const type *arr, const size_t len);`

Appends an `arr` to the back of the `dll`. It returns -1 as error if memory
allocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
dll_int_append(&dll, arr, 5);
```

insert
------

`int dll_##name##_insert(struct dll_##name *dll, const type val, const size_t idx);`

Inserts the `val` to the `idx` in `dll`. It returns -1 as error if `idx` is out
of range or memory allocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 3, 4 };

dll = dll_int_from(arr, 4);
dll_int_insert(&dll, 2, 2);
```

remove
------

`int dll_##name##_remove(struct dll_##name *dll, type *val, const size_t idx);`

Removes the element at the `idx` and assigns it into `val`. It returns -1 as
error if `idx` is out of range or memory deallocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 4);
dll_int_remove(&dll, &val, 2);
```

shrink
------

`int dll_##name##_shrink(struct dll_##name *dll, const size_t len);`

Shrinks the length of `dll` to `len`. It returns -1 as erro if `len` is greater
than the length of `dll` or memory deallocation is failed.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 4);
dll_int_shrink(&dll, 3);
```

length
------

`size_t dll_##name##_length(struct dll_##name *dll);`

Returns the length of `dll`.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
size_t len;

dll = dll_int_from(arr, 4);
len = dll_int_length(&dll);
```

sizeof
------

`size_t dll_##name##_sizeof(struct dll_##name *dll);`

Retruns the amount of bytes that `dll` is occuping.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };
size_t size;

dll = dll_int_from(arr, 4);
size = dll_int_sizeof(&dll);
```

free
----

`void dll_##name##_free(struct dll_##name *dll);`

Deallocates the `dll` from memory and fills NULL and zeros into the internal
fields to prevent use-after-free.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 4);
dll_int_free(&dll);
```

iter
----

`struct dll_##name##_iter dll_##name##_iter(struct dll_##name *dll);`

Constructs an iterator of `dll`.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
struct dll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };

dll = dll_int_from(arr, 5);
iter = dll_int_iter(&dll);
```

next
----

`int dll_##name##_next(struct dll_##name##_iter *iter, type *val);`

Assigns the next element in `dll` into `val`. It returns -1 as error if the end
of range is reached.

```c
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
struct dll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 5);
iter = dll_int_iter(&dll);

dll_int_next(&iter, &val);
```

FOR_EACH_DLL(name, elem, iter)
------------------------------

Traverses each elements in `iter` of linked list.

```c
#include <stdio.h>
#include <stdlib.h>

INIT_DLL_BOTH(int, int, malloc, free)

struct dll_int dll;
struct dll_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

dll = dll_int_from(arr, 5);
iter = dll_int_iter(&dll);

FOR_EACH_DLL(int, val, iter) {
	printf("%d\n", val);
}
```
