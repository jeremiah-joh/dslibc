Singly Linked List
==================

Stack singly linked list.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(n)    | O(n)  |
| Remove    | O(n)    | O(n)  |

new
---

Creates an empty linked list.

`struct sll_##name## sll_##name##_new();`

```c
INIT_SLL(int, int);

sll_int sll = sll_int_new();
```

map
---

```c
INIT_SLL(int, int);

int
increase(int x)
{
    return ++x;
}

int arr[] = { 1, 2, 3 };
struct sll_int sll, map;

sll = sll_int_from(arr, 3);
map = sll_int_map(sll, increase);

assert(map.head->val == 2);
assert(map.head->nxt->val == 3);
assert(map.head->nxt->nxt->val == 4);
```

from
----

Creates linked list from array of keys and values.

`struct sll_##name## sll_##name##_from(const type *arr, const size_t len);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(sll.head->val == 1);
assert(sll.head->nxt->val == 2);
assert(sll.head->nxt->nxt->val == 3);
```

copy
----

Creates a deeply copied linked list.

`struct sll_##name## sll_##name##_copy(const struct sll_##name## sll);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int old = sll_int_from(arr, 3);
sll_int new = sll_int_copy(old);

assert(new.head->val == old.head->val);
assert(new.head->nxt->val == old.head->nxt->val);
assert(new.head->nxt->nxt->val == old.head->nxt->nxt->val);
```

slice
-----

Creates a deeply copied slice from given linked list.

`struct sll_##name## sll_##name##_slice(const struct sll_##name## sll, const size_t head, const size_t tail);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);
sll_int sli = sll_int_slice(sll, 1, 3);

assert(sli.head->val == 2);
assert(sli.head->nxt->val == 3);
```

push
----

Appends an element to the back of the linked list.
Returns 0 on success, -1 on failure.

`int sll_##name##_push(struct sll_##name## *sll, const type val);`

```c
INIT_SLL(int, int);

sll_int sll = sll_int_new();

sll_int_push(&sll, 1);
sll_int_push(&sll, 2);
sll_int_push(&sll, 3);

assert(sll.head->val == 1);
assert(sll.head->nxt->val == 2);
assert(sll.head->nxt->nxt->val == 3);
```

pop
---

Removes an element from back of the linked list and put it in `val`.
Returns 0 on success, -1 on failure.

`int sll_##name##_pop(struct sll_##name## *sll, type *val);`

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_pop(&sll, &val);
assert(val == 3);
```

append
------

Appends two linked lists together. Note that `src` linked list is copied.
Returns 0 on success, -1 on failure.

`int sll_##name##_append(struct sll_##name## *des, const struct sll_##name## src);`

```c
INIT_SLL(int, int);

int arr1[] = { 1, 2, 3 };
int arr2[] = { 4, 5, 6 };
sll_int sll1 = sll_int_from(arr1, 3);
sll_int sll2 = sll_int_from(arr2, 3);

sll_int_append(&sll1, sll2);

assert(sll1.head->val == 1);
assert(sll1.tail->val == 6);
```

insert
------

Inserts an element `val` at given index `idx`.
Returns 0 on success, -1 on failure.

`int sll_##name##_insert(struct sll_##name## *sll, const type val, const size_t idx);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 3 };
sll_int sll = sll_int_from(arr, 2);

sll_int_insert(&sll, 2, 1);

assert(sll.head->nxt->val == 2);
```

shrink
------

Shrinks linked list to be given length `len`.
Returns 0 on success, -1 on failure.

`int sll_##name##_shrink(struct sll_##name## *sll, const size_t len);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_shrink(&sll, 2);

assert(sll.len == 2);
assert(sll.head->nxt->val == 2);
```

getnth
------

Get an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int sll_##name##_getnth(struct sll_##name## *sll, type *val, const size_t idx);`

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_getnth(&sll, &val, 1);

assert(val == 2);
```

setnth
------

Assigns an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int sll_##name##_setnth(struct sll_##name## *sll, const type val, const size_t idx);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_setnth(&sll, 4, 1);

assert(val.head->nxt->val == 4);
```

rmvnth
------

Removes an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int sll_##name##_rmvnth(struct sll_##name## *sll, type *val, const size_t idx);`

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_rmvnth(&sll, &val, 1);

assert(val == 2);
assert(sll.len == 2);
```

retain
------

Retains only elements which given function returns non-zero value.
Returns 0 on success, -1 on failure.

`int sll_##name##_retain(struct sll_##name *sll, int (*fn)(type));`

```c
INIT_SLL(int, int);

int
even(int x)
{
    return x % 2 == 0;
}

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_retain(&sll, even);

assert(sll.len == 1);
assert(sll.head->val == 2);
```

ptr
---

Returns pointer of element in linked list, NULL pointer on out of range situation.

`type *sll_##name##_ptr(struct sll_##name## *sll, const size_t idx);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_int_ptr(&sll, 1) == sll.head->nxt->val);
```

head
----

Returns pointer of first element in linked list, NULL pointer when linked list is empty.

`type *sll_##name##_head(struct sll_##name## *sll);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_int_head(&sll) == sll.head->val);
```

tail
----

Returns pointer of last element in linked list, NULL pointer when linked list is empty.

`type *sll_##name##_tail(struct sll_##name## *sll);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_int_tail(&sll) == sll.head->nxt->nxt->val);
```

foreach
-------

Calls a given function on each element in slltor.

`void sll_##name##_foreach(struct sll_##name *sll, void (*fn)(type *));`

```c
INIT_SLL(int, int);

void
square(int *x)
{
    *x *= *x;
}

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_foreach(&sll, square);

assert(sll.head->val == 1);
assert(sll.head->nxt->val == 4);
assert(sll.head->nxt->nxt->val == 9);
```

free
----

Deallocates linked list from memory.

`void sll_##name##_free(struct sll_##name## *sll);`

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_free(&sll);

assert(sll.arr == NULL);
assert(sll.len == 0);
```
