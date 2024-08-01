Hash table
==========

A linear-probing hash table.

It has following time complexities for each operations.
| Operation | Best case | Worst case |
|-----------|-----------|------------|
| insert    | O(1)      | O(n)       |
| remove    | O(1)      | O(n)       |
| search    | O(1)      | O(n)       |

Initialization
--------------

To use this data structure in your project, you need to copy the `ht.h` header
file into your project directory. Then, use following macros to initialize data
structure for your use case.
* `INIT_HT_TYPE(name, type);` - define struct and function prototypes.
* `INIT_HT_FUNC(name, type, hash, cmp, malloc, free);` - define functions.
* `INIT_HT(name, type, hash, cmp, malloc, free);` - define both at once.

Here are the descriptions of each parameters.
* `name` - the name of data structure, generates `struct ht_name`.
* `type` - type of data in the data structure.
* `hash` - hash function.
* `cmp` - comparison function. returns subtraction of two data.
* `malloc` - memory allocating function.
* `free` - memory deallocation function.

new
---

`struct ht_##name ht_##name##_new()`

Creates an empty hash table.

```c
#include "ht.h"
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

struct ht_int ht = ht_int_new();
```

from
----

`struct ht_##name ht_##name##_from(const type data[], const size_t len)`

Creates a hash table from an array of data.

```c
#include "ht.h"
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct ht_int ht = ht_int_from(data, 5);
```

copy
----

`struct ht_##name ht_##name##_copy(const struct ht_##name ht)`

Creates a deeply copied hash table from given table.

```c
#include "ht.h"
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct ht_int ht = ht_int_from(data, 5);
struct ht_int cpy = ht_int_copy(ht);
```

insert
------

`int ht_##name##_insert(struct ht_##name *ht, const type data)`

Inserts given data into hash table. It returns 0 on success, -1 when given
data is already in the table or memory allocation is failed.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

struct ht_int ht = ht_int_new();

assert(ht_int_insert(&ht, 1) == 0);
assert(ht_int_insert(&ht, 2) == 0);
assert(ht_int_insert(&ht, 3) == 0);
assert(ht.len == 3);
```

search
------

`int ht_##name##_search(struct ht_##name *ht, type *data)`

Searches given data from hash table and assign back to the pointer. It returns
0 on success, -1 when there is no given data in table.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct ht_int ht = ht_int_from(data, 5);

v = 1;
assert(ht_int_search(&ht, &v) == 0);
v = 2;
assert(ht_int_search(&ht, &v) == 0);
v = 3;
assert(ht_int_search(&ht, &v) == 0);
```

remove
------

`int ht_##name##_remove(struct ht_##name *ht, type *data)`

Removes given data from hash table and assign back to the pointer. It returns 0
on success, -1 when there is no given data in table.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3, 4, 5 };
struct ht_int ht = ht_int_from(data, 5);

v = 1;
assert(ht_int_remove(&ht, &v) == 0);
v = 2;
assert(ht_int_remove(&ht, &v) == 0);
v = 3;
assert(ht_int_remove(&ht, &v) == 0);
assert(ht.len == 0);
```

free
----

`void ht_##name##_free(struct ht_##name *ht)`

Frees hash table from memory, assigns NULL every nodes to prevent
use-after-free.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int data[] = { 1, 2, 3, 4, 5 };
struct ht_int ht = ht_int_from(data, 5);

ht_int_free(&ht);

assert(ht.arr == NULL);
assert(ht.cap == 0);
assert(ht.len == 0);
```

iter
----

`struct ht_##name##_iter ht_##name##_iter(struct ht_##name *ht)`

Creates an iterator for hash table.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int data[] = { 1, 2, 3 };
struct ht_int ht = ht_int_from(data, 3);
struct ht_int_iter iter = ht_int_iter(&ht);
```

getnxt
------

`int ht_##name##_getnxt(struct ht_##name##_iter *iter)`

Gets a next data.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int v;
int data[] = { 1, 2, 3 };
struct ht_int ht = ht_int_from(data, 3);
struct ht_int_iter iter = ht_int_iter(&ht);

assert(ht_int_getnxt(&iter, &v) == 0);
assert(v == 1);
assert(ht_int_getnxt(&iter, &v) == 0);
assert(v == 2);
assert(ht_int_getnxt(&iter, &v) == 0);
assert(v == 3);
assert(ht_int_getnxt(&iter, &v) != 0);
```

FOR_EACH
--------

`FOR_EACH(name, item, iter)`

Iterates every data in depth-first-search order.

```c
#include "ht.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int hash_int(int x) { return x; }
int cmp_int(int x, int y) { return x - y; }

INIT_HT(int, int, hash_int, cmp_int, malloc, free);

int i;
int data[] = { 1, 2, 3 };
struct ht_int ht = ht_int_from(data, 3);
struct ht_int_iter iter = ht_int_iter(&ht);

FOR_EACH(int, i, iter) {
	printf("%d\n", i);
}
```
