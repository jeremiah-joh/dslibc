Heap
====

A heap that implements priority queue.

INIT_HEAP_TYPE(name, type)
--------------------------

Initializes structures and function prototypes.

```c
#include "heap.h"

INIT_HEAP_TYPE(int, int);
```

INIT_MAX_HEAP_FUNC(name, type, cmp, malloc, realloc, free)
----------------------------------------------------------

Initializes function definition for maximum heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_FUNC(int, int, cmp, malloc, realloc, free);
```

INIT_MIN_HEAP_FUNC(name, type, cmp, malloc, realloc, free)
----------------------------------------------------------

Initializes function definition for minimum heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MIN_HEAP_FUNC(int, int, cmp, malloc, realloc, free);
```

INIT_MAX_HEAP_BOTH(name, type, cmp, malloc, realloc, free)
----------------------------------------------------------

Initializes both structures and functions for maximum heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MIN_HEAP_BOTH(int, int, cmp, malloc, realloc, free);
```

INIT_MIN_HEAP_BOTH(name, type, cmp, malloc, realloc, free)
----------------------------------------------------------

Initializes both structures and functions for minimum heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MIN_HEAP_BOTH(int, int, cmp, malloc, realloc, free);
```

new
---

`struct heap_##name heap_##name##_new(void);`

Constructs an empty heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MIN_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;

heap = heap_int_new();
```

from
----

`struct heap_##name heap_##name##_from(const type *arr, const size_t len);`

Constructs a heap and fill it by `arr`\`s items.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };

heap = heap_int_from(arr, 5);
```

copy
----

`struct heap_##name heap_##name##_copy(const struct heap_##name *heap);`

Constructs a deeply copied heap from given `heap`.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap1, heap2;
int arr[] = { 0, 1, 2, 3, 4 };

heap1 = heap_int_from(arr, 5);
heap2 = heap_int_copy(&heap2);
```

push
----

`int heap_##name##_push(struct heap_##name *heap, const type val);`

Inserts `val` in `heap` and sort it. It returns 0 on success, -1 if memory
reallocation is failed.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };

heap = heap_int_from(arr, 5);

heap_int_push(&heap, 5);
```

pop
---

`int heap_##name##_pop(struct heap_##name *heap, type *val);`

Removes the greates or least value from `heap` and assigns it into `val`. It
returns 0 on success, -1 if the memory reallocation is failed.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

heap = heap_int_from(arr, 5);

heap_int_pop(&heap, &val);
```

get
---

`int heap_##name##_get(struct heap_##name *heap, type *val);`

Searches the given `val` from `heap` and assigns it back. It returns 0 on
success, -1 if there is no such value in heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

heap = heap_int_from(arr, 5);

val = 3;
heap_int_get(&heap, &val);
```

set
---

`int heap_##name##_get(struct heap_##name *heap, const type val);`

Searches the given `val` from `heap` and assigns the `val` into found. It
returns 0 on success, -1 if there is no such value in heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };

heap = heap_int_from(arr, 5);

heap_int_set(&heap, 3);
```

len
---

`size_t heap_##name##_len(struct heap_##name *heap);`

Returns the length of `heap`.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };
size_t len;

heap = heap_int_from(arr, 4);
len = heap_int_len(&heap);
```

free
----

`void heap_##name##_free(struct heap_##name *heap);`

Deallocates the `heap` from memory and fills NULL and zeros into the internal
fields to prevent use-after-free.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, malloc, realloc, free);

struct heap_int heap;
int arr[] = { 0, 1, 2, 3, 4 };

heap = heap_int_from(arr, 4);
heap_int_free(&heap);
```

iter
----

`struct heap_##name##_iter heap_##name##_iter(struct heap_##name *heap);`

Constructs an iterator of `heap`.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, malloc, realloc, free);

struct heap_int heap;
struct heap_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };

heap = heap_int_from(arr, 5);
iter = heap_int_iter(&heap);
```

next
----

`int heap_##name##_next(struct heap_##name##_iter *iter, type *val);`

Assigns the next element in `heap` into `val`. It returns -1 as error if the end
of range is reached.

```c
#include "heap.h"
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, malloc, realloc, free);

struct heap_int heap;
struct heap_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

heap = heap_int_from(arr, 5);
iter = heap_int_iter(&heap);

heap_int_next(&iter, &val);
```

FOR_EACH_MAX_HEAP(name, elem, iter)
------------------------------

Traverses each elements in `iter` of heap.

```c
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, malloc, realloc, free);

struct heap_int heap;
struct heap_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

heap = heap_int_from(arr, 5);
iter = heap_int_iter(&heap);

FOR_EACH_HEAP(int, val, iter) {
	printf("%d\n", val);
}
```
