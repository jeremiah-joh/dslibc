Binary search tree
==================

Unbalanced, plain binary search tree.

Initialization
--------------

You can initialize a binary search tree with following macros.

* `INIT_BST_TYPE(name, key_t, val_t);` - generates struct and function declaration.
* `INIT_BST_FUNC(name, key_t, val_t, cmp);` - generates function definition.
* `INIT_BST(name, key_t, val_t, cmp);` - generates both at once.

Each parpameters have following meanings.

* `name` - name of data structure. it is represented as `struct bst_name`.
* `key_t` - type of key.
* `val_t` - type of value.
* `cmp` - function that compares two keys and returns signed integer. it should returns negative integer if the first key is less than second, positive if the first key is greater than second, and zero if both keys have same value.

new
---

`struct bst_##name bst_##name##_new()`

Constructs an empty tree.

```c
#include "bst.h"

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

struct bst_int bst = bst_int_new();
```

copy
----

`struct bst_##name bst_##name##_copy(const struct bst_##name)`

Constructs a deeply copied tree from given tree.

```c
#include "bst.h"

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

struct bst_int bst = bst_int_new();
struct bst_int cpy = bst_int_copy(bst);
```

from
----

`struct bst_##name bst_##name##_from(const key_t [], const val_t [], const size_t)`

Constructs a tree from given keys and values.

```c
#include "bst.h"

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3); /* provide length of array */
```

iter
----

`struct bst_##name##_iter bst_##name##_iter(struct bst_##name *)`

Constructs an iterator of given pointer of tree.

```c
#include "bst.h"

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);
struct bst_int_iter iter = bst_int_iter(&bst);
```

insert
------

`int bst_##name##_insert(struct bst_##name *, const key_t, const val_t)`

Inserts a new key and value into tree. Returns 0 on success, -1 on failure.

```c
#include "bst.h"

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

struct bst_int bst = bst_int_new();

bst_##name##_insert(&bst, 1, 4);
bst_##name##_insert(&bst, 2, 5);
bst_##name##_insert(&bst, 3, 6);
```

search
------

`int bst_##name##_search(struct bst_##name *, const key_t, val_t *)`

Gets a value corresponded with given key as call-by-reference. Returns 0 on sucess, -1 on failure.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };
int buf;

struct bst_int bst = bst_int_from(key, val, 3);

bst_int_search(&bst, 2, &buf);
assert(buf == 5);
```

remove
------

`int bst_##name##_remove(struct bst_##name *, const key_t, val_t *)`

Removes a value corresponded with given key and return it as call-by-reference. Returns 0 on sucess, -1 on failure.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };
int buf;

struct bst_int bst = bst_int_from(key, val, 3);

bst_int_remove(&bst, 2, &buf);
assert(buf == 5);
assert(bst.len == 2);
```

ptr
---

`val_t *bst_##name##_ptr(struct bst_##name *, const key_t)`

Returns pointer of value corresponded with given key. Returns NULL on failure.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);

assert(*bst_int_ptr(&bst, 2) == 5);
assert(bst_int_ptr(&bst, 10) == NULL);
```

root
----

`val_t *bst_##name##_root(struct bst_##name *)`

Returns pointer of value in root node. Returns NULL if the tree is empty.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);

assert(bst_int_root(&bst) == 4);
```

max
---

`val_t *bst_##name##_max(struct bst_##name *)`

Returns pointer of the greatest value in tree. Returns NULL if the tree is empty.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);

assert(bst_int_max(&bst) == 6);
```

min
---

`val_t *bst_##name##_min(struct bst_##name *)`

Returns pointer of the least value in tree. Returns NULL if the tree is empty.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);

assert(bst_int_min(&bst) == 4);
```

next
----

`val_t *bst_##name##_next(struct bst_##name##_iter *)`

Returns pointer of next value in iterator. Returns NULL if the iteration is ended.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);
struct bst_int_iter iter = bst_int_iter(&bst);

assert(*bst_int_next(&iter) == 6);
assert(*bst_int_next(&iter) == 5);
assert(*bst_int_next(&iter) == 4);
assert(bst_int_next(&iter) == NULL);
```

free
----

`void bst_##name##_free(struct bst_##name *)`

Deallocates entire nodes and tree itself from memory. This function is use-after-free proof.

```c
#include "bst.h"
#include <assert.h>

int cmp_int(int x, int y) { return x - y };

INIT_BST(int, int, int, cmp_int);

int key[] = { 1, 2, 3 };
int val[] = { 4, 5, 6 };

struct bst_int bst = bst_int_from(key, val, 3);

bst_int_free(&bst);

assert(bst->root == NULL);
assert(bst->len = 0;)
```
