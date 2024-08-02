Binary Heap
===========

A binary heap to implement priority queue. It implements both maximum and
minimum heap.

Initialization
--------------

To use this data structure in your project, you need to copy the `heap.h`
header file into your project directory. Then, use following macros to
initialize data structure for your use case.
* `INIT_HEAP_TYPE(name, type);` - define struct and function prototypes.
* `INIT_MAX_HEAP_FUNC(name, type, cmp, malloc, realloc, free);` - define
functions of maximum heap.
* `INIT_MIN_HEAP_FUNC(name, type, cmp, malloc, realloc, free);` - define
functions of minimum heap.
* `INIT_MAX_HEAP(name, type, cmp, malloc, realloc, free);` - define both at
once.
* `INIT_MIN_HEAP(name, type, cmp, malloc, realloc, free);` - define both at
once.

Here are the descriptions of each parameters.
* `name` - the name of data structure, generates `struct heap_name`.
* `type` - type of data in the data structure.
* `cmp` - comparison function. returns subtraction of two data.
* `malloc` - memory allocating function.
* `realloc` - memory re-allocating function.
* `free` - memory deallocation function.

new
---

`struct heap_##name heap_##name##_new()`

Creates an empty heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

struct heap_int heap = heap_int_new();
```

from
----

`struct heap_##name heap_##name##_from(const type data[], const size_t len)`

Creates a heap from an array of data.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);
```

copy
----

`struct heap_##name heap_##name##_copy(const struct heap_##name)`

Creates a deeply copied heap from given heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);
struct heap_int copy = heap_int_copy(heap);
```

push
----

`int heap_##name##_push(struct heap_##name *heap, type data)`

Pushes new data into heap. It returns 0 on success, -1 on memory allocation
failed or there is already same data.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);

assert(heap_int_push(&heap, 6) == 0);
```

pop
---

`int heap_##name##_pop(struct heap_##name *heap, type *data)`

Pops value of root from heap. It return 0 on success, -1 on memory allocation
failed or heap is empty.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);

assert(heap_int_pop(&heap, &v) == 0);
assert(heap.len == 4);
assert(v == 5);
```

root
----

`int heap_##name##_root(struct heap_##name *heap, type *data)`

Gets value of root in heap. It returns 0 on success, -1 if heap is empty.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);

assert(heap_int_root(&heap, &v) == 0);
assert(v == 5);
```

free
----

`void heap_##name##_free(struct heap_##name *heap)`

Frees heap from memory and assigns NULL every nodes to prevent
use-after-free.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);

heap_int_free(&heap);
assert(heap.arr == NULL);
assert(heap.cap == 0);
assert(heap.len == 0);
```

iter
----

`struct heap_##name##_iter heap_##name##_iter(struct heap_##name *heap)`

Creates an iterator for heap.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct heap_int heap = heap_int_from(data, 5);
sturct heap_int_iter iter = heap_int_iter(&heap);
```

getnxt
------

`int heap_##name##_getnxt(struct heap_##name##_iter *iter, type *data)`

Gets a next data.

```c
#include "heap.h"
#include <stdlib.h>

int cmp_int(int x, int y) { return x - y; }

INIT_MAX_HEAP(int, int, cmp_int, malloc, realloc, free);

int v;
int data[] = { 1, 2, 3 };
struct heap_int heap = heap_int_from(data, 3);
sturct heap_int_iter iter = heap_int_iter(&heap);

assert(heap_int_getnxt(&iter, &v) == 0);
assert(v == 1);
assert(heap_int_getnxt(&iter, &v) == 0);
assert(v == 3);
assert(heap_int_getnxt(&iter, &v) == 0);
assert(v == 2);
assert(heap_int_getnxt(&iter, &v) != 0);
```

FOR_EACH
--------

`FOR_EACH(name, item, iter)`

Iterates every data in depth-first-search order.

```c
#include "heap.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int cmp_int(int x, int y) { return x - y; };

INIT_HEAP(int, int, cmp_int, malloc, free);

int i;
int data[] = { 1, 2, 3 };
struct heap_int heap = heap_int_from(data, 3);
struct heap_int_iter iter = heap_int_iter(&heap);

FOR_EACH(int, i, iter) {
	printf("%d\n", i);
}
```
