Doubly Linked List
==================

Double-ended queue linked list.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(n)    | O(n)  |
| Remove    | O(n)    | O(n)  |

new
---

Creates an empty linked list.

`struct dll_##name## dll_##name##_new();`

```c
INIT_DLL(int, int);

dll_int dll = dll_int_new();
```

from
----

Creates linked list from array of keys and values.

`struct dll_##name## dll_##name##_from(const type *arr, const size_t len);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(dll.head->val == 1);
assert(dll.head->nxt->val == 2);
assert(dll.head->nxt->nxt->val == 3);
```

copy
----

Creates a deeply copied linked list.

`struct dll_##name## dll_##name##_copy(const struct dll_##name## dll);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int old = dll_int_from(arr, 3);
dll_int new = dll_int_copy(old);

assert(new.head->val == old.head->val);
assert(new.head->nxt->val == old.head->nxt->val);
assert(new.head->nxt->nxt->val == old.head->nxt->nxt->val);
```

slice
-----

Creates a deeply copied slice from given linked list.

`struct dll_##name## dll_##name##_slice(const struct dll_##name## dll, const size_t head, const size_t tail);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);
dll_int sli = dll_int_slice(dll, 1, 3);

assert(sli.head->val == 2);
assert(sli.head->nxt->val == 3);
```

push_back
---------

Appends an element to the back of the linked list.
Returns 0 on success, -1 on failure.

`int dll_##name##_push_back(struct dll_##name## *dll, const type val);`

```c
INIT_DLL(int, int);

dll_int dll = dll_int_new();

dll_int_push_back(&dll, 1);
dll_int_push_back(&dll, 2);
dll_int_push_back(&dll, 3);

assert(dll.head->val == 1);
assert(dll.head->nxt->val == 2);
assert(dll.head->nxt->nxt->val == 3);
```

push_front
----------

Appends an element to the front of the linked list.
Returns 0 on success, -1 on failure.

`int dll_##name##_push_front(struct dll_##name## *dll, const type val);`

```c
INIT_DLL(int, int);

dll_int dll = dll_int_new();

dll_int_push_front(&dll, 1);
dll_int_push_front(&dll, 2);
dll_int_push_front(&dll, 3);

assert(dll.head->val == 3);
assert(dll.head->nxt->val == 2);
assert(dll.head->nxt->nxt->val == 1);
```

pop_back
--------

Removes an element from back of the linked list and put it in `val`.
Returns 0 on success, -1 on failure.

`int dll_##name##_pop_back(struct dll_##name## *dll, type *val);`

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_pop_back(&dll, &val);
assert(val == 3);
```

pop_front
---------

Removes an element from front of the linked list and put it in `val`.
Returns 0 on success, -1 on failure.

`int dll_##name##_pop_front(struct dll_##name## *dll, type *val);`

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_pop_front(&dll, &val);
assert(val == 1);
```

append
------

Appends two linked lists together. Note that `src` linked list is copied.
Returns 0 on success, -1 on failure.

`int dll_##name##_append(struct dll_##name## *des, const struct dll_##name## src);`

```c
INIT_DLL(int, int);

int arr1[] = { 1, 2, 3 };
int arr2[] = { 4, 5, 6 };
dll_int dll1 = dll_int_from(arr1, 3);
dll_int dll2 = dll_int_from(arr2, 3);

dll_int_append(&dll1, dll2);

assert(dll1.head->val == 1);
assert(dll1.tail->val == 6);
```

insert
------

Inserts an element `val` at given index `idx`.
Returns 0 on success, -1 on failure.

`int dll_##name##_insert(struct dll_##name## *dll, const type val, const size_t idx);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 3 };
dll_int dll = dll_int_from(arr, 2);

dll_int_insert(&dll, 2, 1);

assert(dll.head->nxt->val == 2);
```

shrink
------

Shrinks linked list to be given length `len`.
Returns 0 on success, -1 on failure.

`int dll_##name##_shrink(struct dll_##name## *dll, const size_t len);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_shrink(&dll, 2);

assert(dll.len == 2);
assert(dll.head->nxt->val == 2);
```

getnth
------

Get an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int dll_##name##_getnth(struct dll_##name## *dll, type *val, const size_t idx);`

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_getnth(&dll, &val, 1);

assert(val == 2);
```

setnth
------

Assigns an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int dll_##name##_setnth(struct dll_##name## *dll, const type val, const size_t idx);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_setnth(&dll, 4, 1);

assert(val.head->nxt->val == 4);
```

rmvnth
------

Removes an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

`int dll_##name##_rmvnth(struct dll_##name## *dll, type *val, const size_t idx);`

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_rmvnth(&dll, &val, 1);

assert(val == 2);
assert(dll.len == 2);
```

retain
------

Retains only elements which given function returns non-zero value.
Returns 0 on success, -1 on failure.

`int dll_##name##_retain(struct dll_##name *dll, int (*fn)(type));`

```c
INIT_DLL(int, int);

int
even(int x)
{
    return x % 2 == 0;
}

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_retain(&dll, even);

assert(dll.len == 1);
assert(dll.head->val == 2);
```

ptr
---

Returns pointer of element in linked list, NULL pointer on out of range situation.

`type *dll_##name##_ptr(struct dll_##name## *dll, const size_t idx);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_ptr(&dll, 1) == dll.head->nxt->val);
```

head
----

Returns pointer of first element in linked list, NULL pointer when linked list is empty.

`type *dll_##name##_head(struct dll_##name## *dll);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_head(&dll) == dll.head->val);
```

tail
----

Returns pointer of last element in linked list, NULL pointer when linked list is empty.

`type *dll_##name##_tail(struct dll_##name## *dll);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_tail(&dll) == dll.head->nxt->nxt->val);
```

foreach
-------

Calls a given function on each element in dlltor.

`void dll_##name##_foreach(struct dll_##name *dll, void (*fn)(type *));`

```c
INIT_DLL(int, int);

void
square(int *x)
{
    *x *= *x;
}

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_foreach(&dll, square);

assert(dll.head->val == 1);
assert(dll.head->nxt->val == 4);
assert(dll.head->nxt->nxt->val == 9);
```

free
----

Deallocates linked list from memory.

`void dll_##name##_free(struct dll_##name## *dll);`

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_free(&dll);

assert(dll.arr == NULL);
assert(dll.len == 0);
```
