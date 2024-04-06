Doubly Linked List
==================

Double-ended queue linked list.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(n)    | O(n)  |
| Remove    | O(n)    | O(n)  |

`struct dll_<name> dll_<name>_new()`
------------------------------------

Creates an empty linked list.

```c
INIT_DLL(int, int);

dll_int dll = dll_int_new();
```

`struct dll_<name> dll_<name>_from(const type *arr, const size_t len)`
----------------------------------------------------------------------

Creates linked list from array.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(dll.head->val == 1);
assert(dll.head->nxt->val == 2);
assert(dll.head->nxt->nxt->val == 3);
```

`struct dll_<name> dll_<name>_copy(const struct dll_<name> dll)`
----------------------------------------------------------------

Creates a deeply copied linked list.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int old = dll_int_from(arr, 3);
dll_int new = dll_int_copy(old);

assert(new.head->val == 1);
assert(new.head->nxt->val == 2);
assert(new.head->nxt->nxt->val == 3);
```

`struct dll_<name> dll_<name>_slice(const struct dll_<name> dll, const size_t head, const size_t tail)`
-------------------------------------------------------------------------------------------------------

Creates a deeply copied slice from given linked list.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);
dll_int sli = dll_int_slice(dll, 1, 3);

assert(sli.head->val == 2);
assert(sli.head->nxt->val == 3);
```

`int dll_<name>_push_back(struct dll_<name> *dll, const type val)`
------------------------------------------------------------------

Appends an element to the back of the linked list.  
Returns 0 on success, -1 on failure.

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

`int dll_<name>_push_front(struct dll_<name> *dll, const type val)`
-------------------------------------------------------------------

Appends an element to the front of the linked list.  
Returns 0 on success, -1 on failure.

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

`int dll_<name>_pop_back(struct dll_<name> *dll, type *val)`
------------------------------------------------------------

Removes an element from back of the linked list and put it in `val`.  
Returns 0 on success, -1 on failure.

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_pop_back(&dll, &val);
assert(val == 3);
```

`int dll_<name>_pop_front(struct dll_<name> *dll, type *val)`
------------------------------------------------------------

Removes an element from front of the linked list and put it in `val`.  
Returns 0 on success, -1 on failure.

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_pop_front(&dll, &val);
assert(val == 1);
```

`int dll_<name>_append(struct dll_<name> *des, const struct dll_<name> src)`
----------------------------------------------------------------------------

Appends two linked lists together. Note that `src` linked list is copied.  
Returns 0 on success, -1 on failure.

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

`int dll_<name>_insert(struct dll_<name> *dll, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Inserts an element `val` at given index `idx`.  
Returns 0 on success, -1 on failure.

```c
INIT_DLL(int, int);

int arr[] = { 1, 3 };
dll_int dll = dll_int_from(arr, 2);

dll_int_insert(&dll, 2, 1);

assert(dll.head->nxt->val == 2);
```

`size_t dll_<name>_search(struct dll_<name> *dll, const type val)`
------------------------------------------------------------------

Returns index number where the `val` is on success, length of linked list on failure.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(dll_int_search(&dll, 2) == 1);
assert(dll_int_search(&dll, 4) == 3);
```

`size_t dll_<name>_remove(struct dll_<name> *dll, const type val)`
------------------------------------------------------------------

Finds given element `val` in linked list and remove it.  
Returns index number where the `val` is on success, length of linked list on failure.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(dll_int_search(&dll, 2) == 1);
assert(dll_int_search(&dll, 4) == 3);
```

`int dll_<name>_shrink(struct dll_<name> *dll, const size_t len)`
-----------------------------------------------------------------

Shrinks linked list to be given length `len`.  
Returns 0 on success, -1 on failure.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_shrink(&dll, 2);

assert(dll.len == 2);
assert(dll.head->nxt->val == 2);
```

`int dll_<name>_getnth(struct dll_<name> *dll, type *val, const size_t idx)`
----------------------------------------------------------------------------

Get an element `val` at index `idx` in linked list.  
Returns 0 on success, -1 on out of range situation.

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_getnth(&dll, &val, 1);

assert(val == 2);
```

`int dll_<name>_setnth(struct dll_<name> *dll, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Assigns an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_setnth(&dll, 4, 1);

assert(val.head->nxt->val == 4);
```

`int dll_<name>_rmvnth(struct dll_<name> *dll, type *val, const size_t idx)`
----------------------------------------------------------------------------

Removes an element `val` at index `idx` in linked list.  
Returns 0 on success, -1 on out of range situation.

```c
INIT_DLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_rmvnth(&dll, &val, 1);

assert(val == 2);
assert(dll.len == 2);
```

`type *dll_<name>_getptr(struct dll_<name> *dll, const size_t idx)`
-------------------------------------------------------------------

Returns pointer of element in linked list, NULL pointer on out of range situation.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_getptr(&dll, 1) == dll.head->nxt->val);
```

`type *dll_<name>_head(struct dll_<name> *dll)`
-----------------------------------------------

Returns pointer of first element in linked list, NULL pointer when linked list is empty.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_head(&dll) == dll.head->val);
```

`type *dll_<name>_tail(struct dll_<name> *dll)`
-----------------------------------------------

Returns pointer of last element in linked list, NULL pointer when linked list is empty.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

assert(*dll_int_tail(&dll) == dll.head->nxt->nxt->val);
```

`void dll_<name>_free(struct dll_<name> *dll)`
----------------------------------------------

Deallocates linked list from memory.  

Using this function is recommanded because it prevents dangling pointer.

```c
INIT_DLL(int, int);

int arr[] = { 1, 2, 3 };
dll_int dll = dll_int_from(arr, 3);

dll_int_free(&dll);

assert(dll.arr == NULL);
assert(dll.len == 0);
```

