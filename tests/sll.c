#include "../src/sll.h"
#include <assert.h>
#include <stdlib.h>

INIT_SLL(int, int, malloc, realloc, free);

void
from()
{
	struct sll_int sll;
	int arr[3] = { 1, 2, 3 };

	sll = sll_int_from(arr, 3);

	assert(sll.head->val == 1);
	assert(sll.head->nxt->val == 2);
	assert(sll.head->nxt->nxt->val == 3);
}

void
push()
{
	struct sll_int sll = sll_int_new();

	sll_int_push(&sll, 1);
	sll_int_push(&sll, 2);
	sll_int_push(&sll, 3);

	assert(sll.head->val == 1);
	assert(sll.head->nxt->val == 2);
	assert(sll.head->nxt->nxt->val == 3);
}

void
pop()
{
	int v;
	struct sll_int sll = sll_int_new();

	sll_int_push(&sll, 1);
	sll_int_push(&sll, 2);
	sll_int_push(&sll, 3);

	sll_int_pop(&sll, &v);
	assert(v == 3);
	assert(sll.len == 2);
}

void
slice()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	struct sll_int sll, sli;

	sll = sll_int_from(arr, 5);
	sli = sll_int_slice(sll, 1, 4);
	
	assert(sli.len == 3);
	assert(sli.head->val == 2);
	assert(sli.head->nxt->val == 3);
	assert(sli.head->nxt->nxt->val == 4);
	assert(sli.len == 3);

	sli = sll_int_slice(sll, 0, 1);
	assert(sli.len == 1);
}

void
append()
{
	struct sll_int des, src;

	des = sll_int_new();
	sll_int_push(&des, 1);
	sll_int_push(&des, 2);
	sll_int_push(&des, 3);

	src = sll_int_new();
	sll_int_push(&src, 4);
	sll_int_push(&src, 5);
	sll_int_push(&src, 6);

	sll_int_append(&des, src);
	assert(des.len == 6);
	assert(des.tail->val == 6);
}

void
insert()
{
	struct sll_int sll = sll_int_new();

	sll_int_push(&sll, 1);
	sll_int_push(&sll, 3);

	sll_int_insert(&sll, 2, 1);
	assert(sll.head->nxt->val == 2);
	assert(sll.len == 3);
}

void
shrink()
{
	int arr[] = { 1, 2, 3 };
	struct sll_int sll = sll_int_from(arr, 3);

	sll_int_shrink(&sll, 2);

	assert(sll.len == 2);
	assert(sll.tail->val == 2);
}

void
nth()
{
	int v;
	struct sll_int sll = sll_int_new();

	sll_int_push(&sll, 1);
	sll_int_push(&sll, 2);
	sll_int_push(&sll, 3);

	sll_int_getnth(&sll, &v, 1);
	assert(v == 2);

	sll_int_setnth(&sll, 1, 1);
	assert(sll.head->nxt->val == 1);

	sll_int_rmvnth(&sll, &v, 1);
	assert(v == 1);
	assert(sll.head->nxt->val == 3);
}

void
ptr()
{
	struct sll_int sll = sll_int_new();

	sll_int_push(&sll, 1);
	sll_int_push(&sll, 2);
	sll_int_push(&sll, 3);

	assert(*sll_int_ptr(&sll, 1) == 2);
	assert(*sll_int_head(&sll) == 1);
	assert(*sll_int_tail(&sll) == 3);
}

void
foreach()
{
	int i, j, val[] = { 1, 2, 3, 4, 5 };
	struct sll_int sll;
	struct sll_int_iter iter;

	sll = sll_int_from(val, 5);
	iter = sll_int_iter(&sll);

	j = 1;
	FOR_EACH(int, i, iter) {
		assert(i == j++);
	}
}

int
main()
{
	from();
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
