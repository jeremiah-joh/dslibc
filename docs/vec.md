Vector
======

Double-ended queue dynamic-length array.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(1)    | O(1)  |
| Remove    | O(n)    | O(n)  |

new
---

Creates an empty vector.

`struct vec_##name## vec_##name##_new();`

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();
```

from
----

Creates vector from array of keys and values.

`struct vec_##name## vec_##name##_from(const type *arr, const size_t len);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(vec.head->val == 1);
assert(vec.head->nxt->val == 2);
assert(vec.head->nxt->nxt->val == 3);
```

copy
----

Creates a deeply copied vector.

`struct vec_##name## vec_##name##_copy(const struct vec_##name## vec);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int old = vec_int_from(arr, 3);
vec_int new = vec_int_copy(old);

assert(new.head->val == old.head->val);
assert(new.head->nxt->val == old.head->nxt->val);
assert(new.head->nxt->nxt->val == old.head->nxt->nxt->val);
```

slice
-----

Creates a deeply copied slice from given vector.

`struct vec_##name## vec_##name##_slice(const struct vec_##name## vec, const size_t head, const size_t tail);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);
vec_int sli = vec_int_slice(vec, 1, 3);

assert(sli.head->val == 2);
assert(sli.head->nxt->val == 3);
```

push_back
---------

Appends an element to the back of the vector.
Returns 0 on success, -1 on failure.

`int vec_##name##_push_back(struct vec_##name## *vec, const type val);`

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();

vec_int_push_back(&vec, 1);
vec_int_push_back(&vec, 2);
vec_int_push_back(&vec, 3);

assert(vec.head->val == 1);
assert(vec.head->nxt->val == 2);
assert(vec.head->nxt->nxt->val == 3);
```

push_front
----------

Appends an element to the front of the vector.
Returns 0 on success, -1 on failure.

`int vec_##name##_push_front(struct vec_##name## *vec, const type val);`

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();

vec_int_push_front(&vec, 1);
vec_int_push_front(&vec, 2);
vec_int_push_front(&vec, 3);

assert(vec.head->val == 3);
assert(vec.head->nxt->val == 2);
assert(vec.head->nxt->nxt->val == 1);
```

pop_back
--------

Removes an element from back of the vector and put it in `val`.
Returns 0 on success, -1 on failure.

`int vec_##name##_pop_back(struct vec_##name## *vec, type *val);`

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_pop_back(&vec, &val);
assert(val == 3);
```

pop_front
---------

Removes an element from front of the vector and put it in `val`.
Returns 0 on success, -1 on failure.

`int vec_##name##_pop_front(struct vec_##name## *vec, type *val);`

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_pop_front(&vec, &val);
assert(val == 1);
```

append
------

Appends two vectors together. Note that `src` vector is copied.
Returns 0 on success, -1 on failure.

`int vec_##name##_append(struct vec_##name## *des, const struct vec_##name## src);`

```c
INIT_VEC(int, int);

int arr1[] = { 1, 2, 3 };
int arr2[] = { 4, 5, 6 };
vec_int vec1 = vec_int_from(arr1, 3);
vec_int vec2 = vec_int_from(arr2, 3);

vec_int_append(&vec1, vec2);

assert(vec1.head->val == 1);
assert(vec1.tail->val == 6);
```

insert
------

Inserts an element `val` at given index `idx`.
Returns 0 on success, -1 on failure.

`int vec_##name##_insert(struct vec_##name## *vec, const type val, const size_t idx);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 3 };
vec_int vec = vec_int_from(arr, 2);

vec_int_insert(&vec, 2, 1);

assert(vec.head->nxt->val == 2);
```

shrink
------

Shrinks vector to be given length `len`.
Returns 0 on success, -1 on failure.

`int vec_##name##_shrink(struct vec_##name## *vec, const size_t len);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_shrink(&vec, 2);

assert(vec.len == 2);
assert(vec.head->nxt->val == 2);
```

getnth
------

Get an element `val` at index `idx` in vector.
Returns 0 on success, -1 on out of range situation.

`int vec_##name##_getnth(struct vec_##name## *vec, type *val, const size_t idx);`

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_getnth(&vec, &val, 1);

assert(val == 2);
```

setnth
------

Assigns an element `val` at index `idx` in vector.
Returns 0 on success, -1 on out of range situation.

`int vec_##name##_setnth(struct vec_##name## *vec, const type val, const size_t idx);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_setnth(&vec, 4, 1);

assert(val.head->nxt->val == 4);
```

rmvnth
------

Removes an element `val` at index `idx` in vector.
Returns 0 on success, -1 on out of range situation.

`int vec_##name##_rmvnth(struct vec_##name## *vec, type *val, const size_t idx);`

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_rmvnth(&vec, &val, 1);

assert(val == 2);
assert(vec.len == 2);
```

ptr
---

Returns pointer of element in vector, NULL pointer on out of range situation.

`type *vec_##name##_ptr(struct vec_##name## *vec, const size_t idx);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_ptr(&vec, 1) == vec.head->nxt->val);
```

head
----

Returns pointer of first element in vector, NULL pointer when vector is empty.

`type *vec_##name##_head(struct vec_##name## *vec);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_head(&vec) == vec.head->val);
```

tail
----

Returns pointer of last element in vector, NULL pointer when vector is empty.

`type *vec_##name##_tail(struct vec_##name## *vec);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_tail(&vec) == vec.head->nxt->nxt->val);
```

free
----

Deallocates vector from memory.

`void vec_##name##_free(struct vec_##name## *vec);`

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_free(&vec);

assert(vec.arr == NULL);
assert(vec.len == 0);
```
