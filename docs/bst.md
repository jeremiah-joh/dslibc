Binary Search Tree
==================

Binary search tree map.

| Operation | Average  | Worst |
|-----------|:--------:|:-----:|
| Insert    | O(log n) | O(n)  |
| Search    | O(log n) | O(n)  |
| Remove    | O(log n) | O(n)  |

new
---

Constructs a new, empty binary search tree.

`struct bst_##name bst_##name##_new();`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

struct bst_int bst;

bst = bst_int_new();
```

copy
----

Returns copy of binary search tree.

`struct bst_##name bst_##name##_copy(const struct bst_##name);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

struct bst_int bst, cpy;

bst = bst_int_new();
cpy = bst_int_copy(bst);
```

from
----

Returns binary search tree from array of keys and values.

`struct bst_##name bst_##name##_from(const key_t [], const val_t [], const size_t);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;

bst = bst_int_from(key, val, len);
```

insert
------

Inserts a key-value pair into binary search tree.
Returns 0 on success, -1 on failure.

`int bst_##name##_insert(struct bst_##name *, const key_t, const val_t);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

struct bst_int bst;

bst = bst_int_insert(&bst, 1, 1);
```

search
------

Get a value corresponding to the key.
Returns 0 on success, -1 on failure.

`int bst_##name##_search(struct bst_##name *, const key_t, val_t *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int val;

bst = bst_int_from(key, val, len);
bst_int_search(&bst, 2, &val);

assert(val == 2);
```

remove
------

Removes a value corresponding to the key.
Returns 0 on success, -1 on failure.

`int bst_##name##_remove(struct bst_##name *, const key_t, val_t *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int val;

bst = bst_int_from(key, val, len);
bst_int_remove(&bst, 2, &val);

assert(val == 2);
```

ptr
---

Returns pointer of value corresponding to the key.
Returns NULL on failure.

`val_t *bst_##name##_ptr(struct bst_##name *, const key_t);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int *val;

bst = bst_int_from(key, val, len);
val = bst_int_ptr(&bst, 2);

assert(*val == 2);
```

root
----

Returns pointers of value at root.
Returns NULL when tree is empty.

`val_t *bst_##name##_root(struct bst_##name *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int *val;

bst = bst_int_from(key, val, len);
val = bst_int_root(&bst);

assert(*val == 1);
```

max
---

Returns pointers of value at the most right node.
Returns NULL when tree is empty.

`val_t *bst_##name##_max(struct bst_##name *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int *val;

bst = bst_int_from(key, val, len);
val = bst_int_max(&bst);

assert(*val == 3);
```

min
---

Returns pointers of value at the most left node.
Returns NULL when tree is empty.

`val_t *bst_##name##_min(struct bst_##name *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;
int *val;

bst = bst_int_from(key, val, len);
val = bst_int_min(&bst);

assert(*val == 3);
```

free
----

Deallocates binary search tree from memory.

`void bst_##name##_free(struct bst_##name *);`

```c
int
cmp(int x, int y)
{
    return y - x;
}

INIT_BST(int, int, int, cmp);

int key[] = { 1, 2, 3 };
int val[] = { 1, 2, 3 };
int len = 3;

struct bst_int bst;

bst = bst_int_from(key, val, len);
bst_int_free(&bst);

assert(bst.root == NULL);
assert(bst.len == 0);
```
