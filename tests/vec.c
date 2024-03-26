#include "../src/vec.h"
#include <assert.h>

INIT_VEC(int, int);

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
	vec_int_push_back(&des, 4);
	vec_int_push_back(&des, 5);
	vec_int_push_back(&des, 6);

	vec_int_append(&des, &src);
	assert(des.len == 6);
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
search()
{
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	assert(vec_int_search(&vec, 2) == 1);
	assert(vec_int_search(&vec, 4) == 3);
}

void
remove()
{
	struct vec_int vec = vec_int_new();

	vec_int_push_back(&vec, 1);
	vec_int_push_back(&vec, 2);
	vec_int_push_back(&vec, 3);

	assert(vec_int_remove(&vec, 2) == 1);
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

	v = *vec_int_getptr(&vec, 1);
	assert(v == 2);

	v = *vec_int_head(&vec);
	assert(v == 1);

	v = *vec_int_tail(&vec);
	assert(v == 3);
}

int
main()
{
	push();
	pop();
	append();
	insert();
	search();
	remove();
	shrink();
	nth();
	ptr();

	return 0;
}
