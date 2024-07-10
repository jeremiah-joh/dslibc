#include "../src/vec.h"
#include <assert.h>

INIT_VEC(int, int);

static int
even(int x)
{
	return x % 2 == 0;
}

static int
increase(int x)
{
	return ++x;
}

void
from()
{
	struct vec_int vec;
	int arr[3] = { 1, 2, 3 };

	vec = vec_int_from(arr, 3);

	assert(vec.arr[0] == 1);
	assert(vec.arr[1] == 2);
	assert(vec.arr[2] == 3);
}

void
slice()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	struct vec_int vec, sli;

	vec = vec_int_from(arr, 5);
	sli = vec_int_slice(vec, 1, 4);
	
	assert(sli.len == 3);
	assert(sli.arr[0] == 2);
	assert(sli.arr[2] == 4);

	sli = vec_int_slice(vec, 0, 1);
	assert(sli.len == 1);
}

void
push()
{
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	vec_int_push_front(&vec, 1);
	vec_int_push_front(&vec, 2);
	vec_int_push_front(&vec, 3);

	assert(vec.arr[0] == 3);
	assert(vec.arr[1] == 2);
	assert(vec.arr[2] == 1);
	assert(vec.arr[3] == 1);
	assert(vec.arr[4] == 2);
	assert(vec.arr[5] == 3);
}

void
pop()
{
	int v;
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	vec_int_pop_back(&vec, &v);
	assert(v == 3);
	
	vec_int_pop_front(&vec, &v);
	assert(v == 1);
}

void
append()
{
	struct vec_int des, src;

	des = vec_int_new();
	vec_int_push_back(&des, 1);
	vec_int_push_back(&des, 2);
	vec_int_push_back(&des, 3);

	src = vec_int_new();
	vec_int_push_back(&src, 4);
	vec_int_push_back(&src, 5);
	vec_int_push_back(&src, 6);

	vec_int_append(&des, src.arr, src.len);
	assert(des.len == 6);
	assert(des.arr[0] == 1);
	assert(des.arr[1] == 2);
	assert(des.arr[2] == 3);
	assert(des.arr[3] == 4);
	assert(des.arr[4] == 5);
	assert(des.arr[5] == 6);
}

void
insert()
{
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);

	vec_int_insert(&vec, 3, 1);
	assert(vec.arr[1] == 3);
}

void
shrink()
{
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	vec_int_shrink(&vec, 2);
	assert(vec.len == 2);
}

void
nth()
{
	int v;
	struct vec_int vec = vec_int_new();
	
	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	vec_int_getnth(&vec, &v, 0);
	vec_int_setnth(&vec, v, 2);
	vec_int_rmvnth(&vec, &v, 1);

	assert(vec.arr[0] == 1);
	assert(vec.arr[1] == 1);
	assert(v == 2);
}

void
ptr()
{
	int v;
	struct vec_int vec = vec_int_new();
	
	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	v = *vec_int_ptr(&vec, 1);
	assert(v == 2);

	v = *vec_int_head(&vec);
	assert(v == 1);

	v = *vec_int_tail(&vec);
	assert(v == 3);
}

void
foreach()
{
	int arr[] = { 1, 2, 3 };
	struct vec_int vec;

	vec = vec_int_from(arr, 3);

	FOR_EACH_PTR(int, i, vec) {
		*i *= *i;
	}

	assert(vec.arr[0] == 1);
	assert(vec.arr[1] == 4);
	assert(vec.arr[2] == 9);
}

void
retain()
{
	int arr[] = { 1, 2, 3 };
	struct vec_int vec;

	vec = vec_int_from(arr, 3);

	vec_int_retain(&vec, even);

	assert(vec.len == 1);
	assert(vec.arr[0] == 2);
}

void
map()
{
	int arr[] = { 1, 2, 3 };
	struct vec_int vec, map;

	vec = vec_int_from(arr, 3);
	map = vec_int_map(vec, increase);

	assert(map.arr[0] == 2);
	assert(map.arr[1] == 3);
	assert(map.arr[2] == 4);
}

int
main()
{
	from();
	slice();
	push();
	pop();
	append();
	insert();
	shrink();
	nth();
	ptr();
	foreach();
	retain();
	map();

	return 0;
}
