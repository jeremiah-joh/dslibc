Hash Table
==========

A hash table that implements dictionary.

INIT_HT_TYPE(name, type)
------------------------

Initializes structures and function prototypes.

```c
#include "ht.h"

INIT_HT_TYPE(int, int);
```

INIT_HT_FUNC(name, type, hash, cmp, malloc, free)
-------------------------------------------------

Initializes function definitions.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_FUNC(int, int, hash, cmp, malloc, free);
```

INIT_HT_BOTH(name, type, hash, cmp, malloc, free)
-------------------------------------------------

Initializes both structures and functions.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);
```

new
---

`struct ht_##name ht_##name##_new(void);`

Constructs an empty hash table.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;

ht = ht_int_new();
```

from
----

`struct ht_##name ht_##name##_from(const type *arr, const size_t len);`

Constructs a hash table and fill it by `arr`\`s items.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };

ht = ht_int_from(arr, 5);
```

copy
----

`struct ht_##name ht_##name##_copy(const struct ht_##name *ht);`

Constructs a deeply copied hash table from 'ht'.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht1, ht2;
int arr[] = { 0, 1, 2, 3, 4 };

ht1 = ht_int_from(arr, 5);
ht2 = ht_int_copy(&ht1);
```

get
---

`int ht_##name##_get(struct ht_##name *ht, type *val);`

Gets an element in `ht` and assigns it into `val`. It returns 0 on success, -1
if there is no such value.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);

val = 3;
ht_int_get(&ht, &val);
```

set
---

`int ht_##name##_set(struct ht_###name *ht, const type val);`

Assigns `val` in `ht`. It returns 0 on success, -1 if there is no such value.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);

val = 3;
ht_int_set(&ht, val);
```

insert
------

`int ht_##name##_insert(struct ht_##name *ht, const type val);`

Inserts `val` into `ht`. It returns 0 on success, -1 if there is already a same
value, or memory reallocation is failed.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);

val = 5;
ht_int_set(&ht, val);
```

remove
------

`int ht_##name##_remove(struct ht_##name *ht, type *val);`

Removes `val` from `ht`. It returns 0 on success, -1 if there is no such value,
or memory reallocation is failed.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);

val = 3;
ht_int_set(&ht, val);
```

len
---

`size_t ht_##name##_len(struct ht_##name *ht);`

Returns the length of `ht`.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
size_t len;

ht = ht_int_from(arr, 5);
len = ht_int_len(&ht);
```

free
----

`void ht_##name##_free(struct ht_##name *ht);`

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };

ht = ht_int_from(arr, 5);

ht_int_free(&ht);
```

iter
----

`struct ht_##name##_iter ht_##name##_iter(ht_##name *ht);`

Constructs an iterator.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int_iter iter;
struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };

ht = ht_int_from(arr, 5);
iter = ht_int_iter(&ht);
```

next
----

`int ht_##name##_next(struct ht_##name##_iter *iter, type *val);`

Assigns a next value in hash table into `val`. It returns 0 on success, -1 if
there is no value left.

```c
#include "ht.h"
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

struct ht_int_iter iter;
struct ht_int ht;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);
iter = ht_int_iter(&ht);

ht_int_next(&iter, &val);
```

FOR_EACH_HT(name, elem, iter)
-----------------------------

Traverses each elements in `iter` of hash table.

```c
#include "ht.h"
#include <stdio.h>
#include <stdlib.h>

int hash(int x) { /* some hash function */ }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, malloc, free);

struct ht_int ht;
struct ht_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

ht = ht_int_from(arr, 5);
iter = ht_int_iter(&ht);

FOR_EACH_HT(int, val, iter) {
	printf("%d\n", val);
}
```
