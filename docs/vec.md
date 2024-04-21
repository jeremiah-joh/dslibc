Vector
======

Double-ended queue dynamic-length array.

| Operation | Average | Worst |
|-----------|:-------:|:-----:|
| Insert    | O(n)    | O(n)  |
| Search    | O(1)    | O(1)  |
| Remove    | O(n)    | O(n)  |

`struct vec_<name> vec_<name>_new()`
------------------------------------

Creates an empty vector.

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();
```

`struct vec_<name> vec_<name>_from(const type *arr, const size_t len)`
----------------------------------------------------------------------

Creates vector from array.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(vec.arr[0] == 1);
assert(vec.arr[1] == 2);
assert(vec.arr[2] == 3);
```

`struct vec_<name> vec_<name>_copy(const struct vec_<name> vec)`
----------------------------------------------------------------

Creates a deeply copied vector.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int old = vec_int_from(arr, 3);
vec_int new = vec_int_copy(old);

assert(new.arr[0] == old.arr[0]);
assert(new.arr[1] == old.arr[1]);
assert(new.arr[2] == old.arr[2]);
```

`struct vec_<name> vec_<name>_slice(const struct vec_<name> vec, const size_t head, const size_t tail)`
-------------------------------------------------------------------------------------------------------

Creates a deeply copied slice from given vector.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);
vec_int sli = vec_int_slice(vec, 1, 3);

assert(sli.arr[0] == 2);
assert(sli.arr[1] == 3);
```

`int vec_<name>_push_back(struct vec_<name> *vec, const type val)`
------------------------------------------------------------------

Appends an element to the back of the vector.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();

vec_int_push_back(&vec, 1);
vec_int_push_back(&vec, 2);
vec_int_push_back(&vec, 3);

assert(vec.arr[0] == 1);
assert(vec.arr[1] == 2);
assert(vec.arr[2] == 3);
```

`int vec_<name>_push_front(struct vec_<name> *vec, const type val)`
-------------------------------------------------------------------

Appends an element to the front of the vector.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

vec_int vec = vec_int_new();

vec_int_push_front(&vec, 1);
vec_int_push_front(&vec, 2);
vec_int_push_front(&vec, 3);

assert(vec.arr[0] == 3);
assert(vec.arr[1] == 2);
assert(vec.arr[2] == 1);
```

`int vec_<name>_pop_back(struct vec_<name> *vec, type *val)`
------------------------------------------------------------

Removes an element from back of the vector and put it in `val`.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_pop_back(&vec, &val);
assert(val == 3);
```

`int vec_<name>_pop_front(struct vec_<name> *vec, type *val)`
------------------------------------------------------------

Removes an element from front of the vector and put it in `val`.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_pop_front(&vec, &val);
assert(val == 1);
```

`int vec_<name>_append(struct vec_<name> *des, const type *arr, const size_t len)`
----------------------------------------------------------------------------------

Appends array at the tail of vector.
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

int arr1[] = { 1, 2, 3 };
int arr2[] = { 4, 5, 6 };
vec_int vec = vec_int_from(arr1, 3);

vec_int_append(&vec1, arr2, 3);

assert(vec1.arr[0] == 1);
assert(vec1.arr[5] == 6);
```

`int vec_<name>_insert(struct vec_<name> *vec, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Inserts an element `val` at given index `idx`.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

int arr[] = { 1, 3 };
vec_int vec = vec_int_from(arr, 2);

vec_int_insert(&vec, 2, 1);

assert(vec.arr[1] == 2);
```

`int vec_<name>_shrink(struct vec_<name> *vec, const size_t len)`
-----------------------------------------------------------------

Shrinks vector to be given length `len`.  
Returns 0 on success, -1 on failure.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_shrink(&vec, 2);

assert(vec.len == 2);
assert(vec.arr[1] == 2);
```

`int vec_<name>_getnth(struct vec_<name> *vec, type *val, const size_t idx)`
----------------------------------------------------------------------------

Get an element `val` at index `idx` in vector.  
Returns 0 on success, -1 on out of range situation.

Using this function is recommended over `val = vec.arr[idx]` because it checks range.

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_getnth(&vec, &val, 1);

assert(val == 2);
```

`int vec_<name>_setnth(struct vec_<name> *vec, const type val, const size_t idx)`
---------------------------------------------------------------------------------

Assigns an element `val` at index `idx` in vector.
Returns 0 on success, -1 on out of range situation.

Using this function is recommended over `vec.arr[idx] = val` because it checks range.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_setnth(&vec, 4, 1);

assert(val.arr[1] == 4);
```

`int vec_<name>_rmvnth(struct vec_<name> *vec, type *val, const size_t idx)`
----------------------------------------------------------------------------

Removes an element `val` at index `idx` in vector.  
Returns 0 on success, -1 on out of range situation.

```c
INIT_VEC(int, int);

int val;
int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_rmvnth(&vec, &val, 1);

assert(val == 2);
assert(vec.len == 2);
```

`type *vec_<name>_getptr(struct vec_<name> *vec, const size_t idx)`
-------------------------------------------------------------------

Returns pointer of element in vector, NULL pointer on out of range situation.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_getptr(&vec, 1) == vec.arr[1]);
```

`type *vec_<name>_head(struct vec_<name> *vec)`
-----------------------------------------------

Returns pointer of first element in vector, NULL pointer when vector is empty.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_head(&vec) == vec.arr[0]);
```

`type *vec_<name>_tail(struct vec_<name> *vec)`
-----------------------------------------------

Returns pointer of last element in vector, NULL pointer when vector is empty.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

assert(*vec_int_tail(&vec) == vec.arr[2]);
```

`void vec_<name>_free(struct vec_<name> *vec)`
----------------------------------------------

Deallocates vector from memory.  

Using this function is recommended over `free(vec.arr)` because it prevents dangling pointer.

```c
INIT_VEC(int, int);

int arr[] = { 1, 2, 3 };
vec_int vec = vec_int_from(arr, 3);

vec_int_free(&vec);

assert(vec.arr == NULL);
assert(vec.cap == 0);
assert(vec.len == 0);
```

