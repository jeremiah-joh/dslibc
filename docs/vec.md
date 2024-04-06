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

assert(new.arr[0] == 1);
assert(new.arr[1] == 2);
assert(new.arr[2] == 3);
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

`int vec_<name>_append(struct vec_<name> *des, const struct vec_<name> src)`
----------------------------------------------------------------------------

Append two vectors together. 
