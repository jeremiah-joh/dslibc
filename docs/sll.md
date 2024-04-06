Singly Linked List
==================

Stack singly linked list.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(n)    | O(n)  |
| Remove    | O(n)    | O(n)  |

`struct sll_<name> sll_<name>_new()`
------------------------------------

Creates an empty linked list.

```c
INIT_SLL(int, int);

sll_int sll = sll_int_new();
```

`struct sll_<name> sll_<name>_from(const type *arr, const size_t len)`
----------------------------------------------------------------------

Creates linked list from array.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(sll.head->val == 1);
assert(sll.head->nxt->val == 2);
assert(sll.head->nxt->nxt->val == 3);
```

`struct sll_<name> sll_<name>_copy(const struct sll_<name> sll)`
----------------------------------------------------------------

Creates a deeply copied linked list.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int old = sll_int_from(arr, 3);
sll_int new = sll_int_copy(old);

assert(new.head->val == 1);
assert(new.head->nxt->val == 2);
assert(new.head->nxt->nxt->val == 3);
```

`struct sll_<name> sll_<name>_slice(const struct sll_<name> sll, const size_t head, const size_t tail)`
-------------------------------------------------------------------------------------------------------

Creates a deeply copied slice from given linked list.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);
sll_int sli = sll_int_slice(sll, 1, 3);

assert(sli.head->val == 2);
assert(sli.head->nxt->val == 3);
```

`int sll_<name>_push(struct sll_<name> *sll, const type val)`
------------------------------------------------------------------

Appends an element to the back of the linked list.  
Returns 0 on success, -1 on failure.

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

`int sll_<name>_pop(struct sll_<name> *sll, type *val)`
------------------------------------------------------------

Removes an element from back of the linked list and put it in `val`.  
Returns 0 on success, -1 on failure.

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_pop(&sll, &val);
assert(val == 3);
```

`int sll_<name>_append(struct sll_<name> *des, const struct sll_<name> src)`
----------------------------------------------------------------------------

Appends two linked lists together. Note that `src` linked list is copied.  
Returns 0 on success, -1 on failure.

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

`int sll_<name>_insert(struct sll_<name> *sll, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Inserts an element `val` at given index `idx`.  
Returns 0 on success, -1 on failure.

```c
INIT_SLL(int, int);

int arr[] = { 1, 3 };
sll_int sll = sll_int_from(arr, 2);

sll_int_insert(&sll, 2, 1);

assert(sll.head->nxt->val == 2);
```

`size_t sll_<name>_search(struct sll_<name> *sll, const type val)`
------------------------------------------------------------------

Returns index number where the `val` is on success, length of linked list on failure.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(sll_int_search(&sll, 2) == 1);
assert(sll_int_search(&sll, 4) == 3);
```

`size_t sll_<name>_remove(struct sll_<name> *sll, const type val)`
------------------------------------------------------------------

Finds given element `val` in linked list and remove it.  
Returns index number where the `val` is on success, length of linked list on failure.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(sll_int_search(&sll, 2) == 1);
assert(sll_int_search(&sll, 4) == 3);
```

`int sll_<name>_shrink(struct sll_<name> *sll, const size_t len)`
-----------------------------------------------------------------

Shrinks linked list to be given length `len`.  
Returns 0 on success, -1 on failure.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_shrink(&sll, 2);

assert(sll.len == 2);
assert(sll.head->nxt->val == 2);
```

`int sll_<name>_getnth(struct sll_<name> *sll, type *val, const size_t idx)`
----------------------------------------------------------------------------

Get an element `val` at index `idx` in linked list.  
Returns 0 on success, -1 on out of range situation.

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_getnth(&sll, &val, 1);

assert(val == 2);
```

`int sll_<name>_setnth(struct sll_<name> *sll, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Assigns an element `val` at index `idx` in linked list.
Returns 0 on success, -1 on out of range situation.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_setnth(&sll, 4, 1);

assert(val.head->nxt->val == 4);
```

`int sll_<name>_rmvnth(struct sll_<name> *sll, type *val, const size_t idx)`
----------------------------------------------------------------------------

Removes an element `val` at index `idx` in linked list.  
Returns 0 on success, -1 on out of range situation.

```c
INIT_SLL(int, int);

int val;
int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_rmvnth(&sll, &val, 1);

assert(val == 2);
assert(sll.len == 2);
```

`type *sll_<name>_getptr(struct sll_<name> *sll, const size_t idx)`
-------------------------------------------------------------------

Returns pointer of element in linked list, NULL pointer on out of range situation.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_int_getptr(&sll, 1) == 2);
```

`type *sll_<name>_head(struct sll_<name> *sll)`
-----------------------------------------------

Returns pointer of first element in linked list, NULL pointer when linked list is empty.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_<nam>_head(&sll) == 1);
```

`type *sll_<name>_tail(struct sll_<name> *sll)`
-----------------------------------------------

Returns pointer of last element in linked list, NULL pointer when linked list is empty.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

assert(*sll_<nam>_tail(&sll) == 3);
```

`void sll_<name>_free(struct sll_<name> *sll)`
----------------------------------------------

Deallocates linked list from memory.  

Using this function is recommanded because it prevents dangling pointer.

```c
INIT_SLL(int, int);

int arr[] = { 1, 2, 3 };
sll_int sll = sll_int_from(arr, 3);

sll_int_free(&sll);

assert(sll.head == NULL && sll.tail == NULL);
assert(sll.len == 0);
```

