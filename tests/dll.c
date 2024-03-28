#include "../src/dll.h"
#include <assert.h>

INIT_DLL(int, int);

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
search()
{
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	assert(dll_int_search(&dll, 2) == 1);
}

void
remove()
{
	int arr[] = { 1, 2, 3 };
	struct dll_int dll;

	dll = dll_int_from(arr, 3);

	assert(dll_int_remove(&dll, 2) == 1);
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

	assert(*dll_int_getptr(&dll, 1) == 2);
	assert(*dll_int_head(&dll) == 1);
	assert(*dll_int_tail(&dll) == 3);
}

void
t_free()
{
	struct dll_int dll;
	int arr[3] = { 1, 2, 3 };

	dll = dll_int_from(arr, 3);

	dll_int_free(&dll);

	assert(dll.head == NULL && dll.tail == NULL);
	assert(dll.len == 0);
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
	search();
	remove();
	nth();
	ptr();
	t_free();

	return 0;
}
