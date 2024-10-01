Vector
======

A growable array that implements a stack.

INIT_VEC_TYPE(name, type)
-------------------------

Initializes structures and function prototypes.

```c
#include "vec.h"

INIT_VEC_TYPE(int, int)
```

INIT_VEC_FUNC(name, type, malloc, realloc, free)
------------------------------------------------

Initializes function definitions.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_FUNC(int, int, malloc, realloc, free)
```

INIT_VEC_BOTH(name, type, malloc, realloc, free)
------------------------------------------------

Initializes both structures and functions.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)
```

new
---

`struct vec_##name vec_##name##_new(void);`

Constructs a new, empty vector.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;

vec = vec_int_new();
```

from
----

`struct vec_##name vec_##name##_from(const type *arr, const size_t len);`

Allocate a vector and fill it by `arr`\`s items.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
```

copy
----

`struct vec_##name vec_##name##_copy(const struct vec_##name *vec);`

Constructs a deeply copied vector from given `vec`.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec1, vec2;
int arr[] = { 0, 1, 2, 3, 4 };

vec1 = vec_int_from(arr, 5);
vec2 = vec_int_copy(&vec2);
```

push
----

`int vec_##name##_push(struct vec_##name *vec, const type val);`

Appends an element `val` to the back of the `vec`. It returns -1 as error if
memory reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
vec_int_push(&vec, 5);
```

pop
---

`int vec_##name##_pop(struct vec_##name *vec, type *val);`

Removes the last element from the `vec` and assigns into `val`. It returns -1
as error if memory reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

vec = vec_int_from(arr, 5);
vec_int_pop(&vec, &val);
```

get
---

`int vec_##name##_get(struct vec_##name *vec, type *val, const size_t idx);`

Assigns the element at `idx` into `val` in `vec`. It returs -1 as error if the
`idx` is out of range.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

vec = vec_int_from(arr, 5);
vec_int_get(&vec, &val, 3);
```

set
---

`int vec_##name##_set(struct vec_##name *vec, const type val, const size_t len);`

Assigns the `val` at `idx` in `vec`. It returns -1 as error if the `idx` is out
of range.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
vec_int_get(&vec, 0, 3);
```

append
------

`int vec_##name##_append(struct vec_##name *vec, const type *arr, const size_t len);`

Appends an `arr` to the back of the `vec`. It returns -1 as error if memory
reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
vec_int_append(&vec, arr, 5);
```

insert
------

`int vec_##name##_insert(struct vec_##name *vec, const type val, const size_t idx);`

Inserts the `val` to the `idx` in `vec`. It returns -1 as error if `idx` is out
of range or memory reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 3, 4 };

vec = vec_int_from(arr, 4);
vec_int_insert(&vec, 2, 2);
```

remove
------

`int vec_##name##_remove(struct vec_##name *vec, type *val, const size_t idx);`

Removes the element at the `idx` and assigns it into `val`. It returns -1 as
error if `idx` is out of range or memory reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

vec = vec_int_from(arr, 5);
vec_int_remove(&vec, &val, 2);
```

shrink
------

`int vec_##name##_shrink(struct vec_##name *vec, const size_t len);`

Shrinks the length of `vec` to `len`. It returns -1 as erro if `len` is greater
than the length of `vec` or memory reallocation is failed.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
vec_int_shrink(&vec, 3);
```

len
---

`size_t vec_##name##_len(struct vec_##name *vec);`

Returns the length of `vec`.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };
size_t len;

vec = vec_int_from(arr, 5);
len = vec_int_len(&vec);
```

sizeof
------

`size_t vec_##name##_sizeof(struct vec_##name *vec);`

Retruns the amount of bytes that `vec` is occuping.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };
size_t size;

vec = vec_int_from(arr, 5);
size = vec_int_sizeof(&vec);
```

free
----

`void vec_##name##_free(struct vec_##name *vec);`

Deallocates the `vec` from memory and fills NULL and zeros into the internal
fields to prevent use-after-free.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
vec_int_free(&vec);
```

iter
----

`struct vec_##name##_iter vec_##name##_iter(struct vec_##name *vec);`

Constructs an iterator of `vec`.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
struct vec_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };

vec = vec_int_from(arr, 5);
iter = vec_int_iter(&vec);
```

next
----

`int vec_##name##_next(struct vec_##name##_iter *iter, type *val);`

Assigns the next element in `vec` into `val`. It returns -1 as error if the end
of range is reached.

```c
#include "vec.h"
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
struct vec_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

vec = vec_int_from(arr, 5);
iter = vec_int_iter(&vec);

vec_int_next(&iter, &val);
```

FOR_EACH_VEC(name, elem, iter)
------------------------------

Traverses each elements in `iter` of vector.

```c
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

INIT_VEC_BOTH(int, int, malloc, realloc, free)

struct vec_int vec;
struct vec_int_iter iter;
int arr[] = { 0, 1, 2, 3, 4 };
int val;

vec = vec_int_from(arr, 5);
iter = vec_int_iter(&vec);

FOR_EACH_VEC(int, val, iter) {
	printf("%d\n", val);
}
```
