#include "../src/bst.h"
#include <assert.h>
#include <stdlib.h>

int
cmp(int x, int y)
{
	return x - y;
}

INIT_BST(int, int, cmp, malloc, free);

void
from()
{
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(val, 3);

	assert(bst.len == 3);
	assert(bst.root->data == 2);
	assert(bst.root->rch->data == 3);
	assert(bst.root->lch->data == 1);
}

void
copy()
{
	int val[] = { 2, 1, 3 };
	struct bst_int bst, cpy;

	bst = bst_int_from(val, 3);
	cpy = bst_int_copy(bst);

	assert(bst.root->data == cpy.root->data);
	assert(bst.root->rch->data == cpy.root->rch->data);
	assert(bst.root->lch->data == cpy.root->lch->data);
}

void
insert()
{
	struct bst_int bst;

	bst = bst_int_new();

	bst_int_insert(&bst, 2);
	bst_int_insert(&bst, 1);
	bst_int_insert(&bst, 3);

	assert(bst.len == 3);
	assert(bst.root->data == 2);
	assert(bst.root->rch->data == 3);
	assert(bst.root->lch->data == 1);
}

void
search()
{
	int v;
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(val, 3);
	
	v = 1;
	assert(bst_int_search(&bst, &v) == 0);
}

void
remove()
{
	int v;
	int val[] = { 2, 1, 4, 3, 5 };
	struct bst_int bst;

	bst = bst_int_from(val, 5);
	
	v = 4;
	assert(bst_int_remove(&bst, &v) == 0);
	assert(v == 4);
	assert(bst.root->rch->data == 5);
	assert(bst.root->rch->lch->data == 3);
	assert(bst.len == 4);
}

void
foreach()
{
	int i, j;
	int arr[] = { 0, 0, 0 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;
	struct bst_int_iter iter;

	bst = bst_int_from(val, 3);
	iter = bst_int_iter(&bst);

	j = 0;
	FOR_EACH(int, i, iter) {
		arr[j++] = i;
	}

	assert(arr[0] == 1);
	assert(arr[1] == 2);
	assert(arr[2] == 3);
}

int
main()
{
	from();
	copy();
	insert();
	search();
	remove();
	foreach();

	return 0;
}
