#include "../src/dll.h"
#include <assert.h>
#include <stdlib.h>

INIT_DLL(int, int, malloc, free);

void
from()
{
	struct dll_int dll;
	int arr[] = { 1, 2, 3 };

	dll = dll_int_from(arr, 3);

	assert(dll.head->val == 1);
	assert(dll.head->nxt->val == 2);
	assert(dll.head->nxt->nxt->val == 3);
}

void
copy()
{
	struct dll_int des, src;
	int arr[] = { 1, 2, 3 };

	src = dll_int_from(arr, 3);
	des = dll_int_copy(src);

	assert(des.head->val == 1);
	assert(des.head->nxt->val == 2);
	assert(des.head->nxt->nxt->val == 3);
}

void
push()
{
	struct dll_int dll = dll_int_new();

	dll_int_push_back(&dll, 1);
	dll_int_push_back(&dll, 2);
	dll_int_push_back(&dll, 3);

	dll_int_push_front(&dll, 1);
	dll_int_push_front(&dll, 2);
	dll_int_push_front(&dll, 3);

	assert(dll.len == 6);
	assert(dll.head->val == 3);
	assert(dll.tail->val == 3);
}

void
pop()
{
	int v;
	struct dll_int dll = dll_int_new();

	dll_int_push_back(&dll, 1);
	dll_int_push_back(&dll, 2);
	dll_int_push_back(&dll, 3);

	dll_int_pop_back(&dll, &v);
	assert(dll.len == 2);
	assert(v == 3);

	dll_int_pop_front(&dll, &v);
	assert(dll.len == 1);
	assert(v == 1);
}

void
slice()
{
	struct dll_int dll, sli;
	int arr[] = { 1, 2, 3, 4, 5 };

	dll = dll_int_from(arr, 5);
	sli = dll_int_slice(dll, 1, 4);

	assert(sli.head->val == 2);
	assert(sli.head->nxt->val == 3);
	assert(sli.head->nxt->nxt->val == 4);
}

void
append()
{
	struct dll_int des, src;
	int arr_des[] = { 1, 2, 3 };
	int arr_src[] = { 4, 5, 6 };

	des = dll_int_from(arr_des, 3);
	src = dll_int_from(arr_src, 3);

	dll_int_append(&des, src);

	assert(des.len == 6);
	assert(des.head->val == 1);
	assert(des.tail->val == 6);
}

void
insert()
{
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	dll_int_insert(&dll, 1, 2);

	assert(dll.len == 4);
	assert(dll.tail->prv->val = 1);
}

void
shrink()
{
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	dll_int_shrink(&dll, 2);

	assert(dll.tail->val == 2);
	assert(dll.len == 2);
}

void
nth()
{
	int v;
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	dll_int_getnth(&dll, &v, 1);
	assert(v == 2);

	dll_int_setnth(&dll, 1, 1);
	assert(dll.head->nxt->val == 1);

	dll_int_rmvnth(&dll, &v, 1);
	assert(v == 1);
	assert(dll.head->nxt->val == 3);
}

void
ptr()
{
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	assert(*dll_int_ptr(&dll, 1) == 2);
	assert(*dll_int_head(&dll) == 1);
	assert(*dll_int_tail(&dll) == 3);
}

void
foreach()
{
	int i, j, val[] = { 1, 2, 3, 4, 5 };
	struct dll_int dll;
	struct dll_int_iter iter;

	dll = dll_int_from(val, 5);
	iter = dll_int_iter(&dll);

	j = 1;
	FOR_EACH(int, i, iter) {
		assert(i == j++);
	}
}

int
main()
{
	from();
	copy();
	push();
	pop();
	slice();
	append();
	insert();
	shrink();
	nth();
	ptr();
	foreach();

	return 0;
}
