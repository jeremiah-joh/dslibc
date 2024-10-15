/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include "../src/vec.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 5

INIT_VEC_BOTH(int, int, malloc, realloc, free);

static void
from()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	vec = vec_int_from(arr, LEN);

	assert(vec_int_len(&vec) == 5);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 2);
	assert(vec.arr[3] == 3);
	assert(vec.arr[4] == 4);
}

static void
push()
{
	struct vec_int vec;

	vec = vec_int_new();

	vec_int_push(&vec, 0);
	vec_int_push(&vec, 1);
	vec_int_push(&vec, 2);
	vec_int_push(&vec, 3);
	vec_int_push(&vec, 4);

	assert(vec_int_len(&vec) == 5);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 2);
	assert(vec.arr[3] == 3);
	assert(vec.arr[4] == 4);
}

static void
pop()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	vec = vec_int_from(arr, LEN);

	vec_int_pop(&vec, &val);
	assert(val == 4);
	vec_int_pop(&vec, &val);
	assert(val == 3);
	vec_int_pop(&vec, &val);
	assert(val == 2);
	vec_int_pop(&vec, &val);
	assert(val == 1);
	vec_int_pop(&vec, &val);
	assert(val == 0);

	assert(vec_int_len(&vec) == 0);

	assert(vec_int_pop(&vec, &val) != 0);
}

static void
get()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	vec = vec_int_from(arr, LEN);

	vec_int_get(&vec, &val, 0);
	assert(val == 0);
	vec_int_get(&vec, &val, 1);
	assert(val == 1);
	vec_int_get(&vec, &val, 2);
	assert(val == 2);
	vec_int_get(&vec, &val, 3);
	assert(val == 3);
	vec_int_get(&vec, &val, 4);
	assert(val == 4);

	assert(vec_int_get(&vec, &val, 5) != 0);
}

static void
set()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	vec = vec_int_from(arr, LEN);

	vec_int_set(&vec, 4, 0);
	vec_int_set(&vec, 3, 1);
	vec_int_set(&vec, 2, 2);
	vec_int_set(&vec, 1, 3);
	vec_int_set(&vec, 0, 4);

	assert(vec.arr[0] == 4);
	assert(vec.arr[1] == 3);
	assert(vec.arr[2] == 2);
	assert(vec.arr[3] == 1);
	assert(vec.arr[4] == 0);

	assert(vec_int_set(&vec, 5, 5) != 0);
}

static void
append()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	vec = vec_int_new();

	vec_int_append(&vec, arr, LEN);

	assert(vec_int_len(&vec) == 5);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 2);
	assert(vec.arr[3] == 3);
	assert(vec.arr[4] == 4);
}

static void
insert()
{
	struct vec_int vec;
	int arr[2] = { 0, 4 };

	vec = vec_int_from(arr, 2);

	vec_int_insert(&vec, 1, 1);
	vec_int_insert(&vec, 2, 2);
	vec_int_insert(&vec, 3, 3);

	assert(vec_int_len(&vec) == 5);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 2);
	assert(vec.arr[3] == 3);
	assert(vec.arr[4] == 4);

	assert(vec_int_insert(&vec, 6, 6) != 0);
}

static void
remove()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	vec = vec_int_from(arr, LEN);

	vec_int_remove(&vec, &val, 2);
	assert(val == 2);

	assert(vec_int_len(&vec) == 4);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 3);
	assert(vec.arr[3] == 4);
}

static void
shrink()
{
	struct vec_int vec;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	vec = vec_int_from(arr, LEN);

	vec_int_shrink(&vec, 3);

	assert(vec_int_len(&vec) == 3);
	assert(vec.arr[0] == 0);
	assert(vec.arr[1] == 1);
	assert(vec.arr[2] == 2);
}

static void
iter()
{
	struct vec_int vec;
	struct vec_int_iter iter;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	vec = vec_int_from(arr, LEN);
	iter = vec_int_iter(&vec);

	assert(vec_int_next(&iter, &val) == 0);
	assert(val == 0);
	assert(vec_int_next(&iter, &val) == 0);
	assert(val == 1);
	assert(vec_int_next(&iter, &val) == 0);
	assert(val == 2);
	assert(vec_int_next(&iter, &val) == 0);
	assert(val == 3);
	assert(vec_int_next(&iter, &val) == 0);
	assert(val == 4);
	assert(vec_int_next(&iter, &val) != 0);
}

int
main()
{
	from();
	push();
	pop();
	get();
	set();
	append();
	insert();
	remove();
	shrink();
	iter();

	return 0;
}
