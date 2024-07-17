#include "../src/bst.h"
#include <assert.h>

int
cmp(int x, int y)
{
	return x - y;
}

INIT_BST(int, int, int, cmp);

void
from()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3);

	assert(bst.len == 3);
	assert(bst.root->val == 2);
	assert(bst.root->rch->val == 3);
	assert(bst.root->lch->val == 1);
}

void
copy()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst, cpy;

	bst = bst_int_from(key, val, 3);
	cpy = bst_int_copy(bst);

	assert(bst.root->val == cpy.root->val);
	assert(bst.root->rch->val == cpy.root->rch->val);
	assert(bst.root->lch->val == cpy.root->lch->val);
}

void
insert()
{
	struct bst_int bst;

	bst = bst_int_new();

	bst_int_insert(&bst, 2, 2);
	bst_int_insert(&bst, 1, 1);
	bst_int_insert(&bst, 3, 3);

	assert(bst.len == 3);
	assert(bst.root->val == 2);
	assert(bst.root->rch->val == 3);
	assert(bst.root->lch->val == 1);
}

void
search()
{
	int v;
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3);
	
	bst_int_search(&bst, 1, &v);

	assert(v == 1);
}

void
remove()
{
	int v;
	int key[] = { 2, 1, 4, 3, 5 };
	int val[] = { 2, 1, 4, 3, 5 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 5);
	
	bst_int_remove(&bst, 4, &v);

	assert(v == 4);
	assert(bst.root->rch->val == 5);
	assert(bst.root->rch->lch->val == 3);
	assert(bst.len == 4);
}

void
ptr()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3);
	
	assert(*bst_int_ptr(&bst, 3) == 3);
	assert(*bst_int_root(&bst) == 2);
	assert(*bst_int_min(&bst) == 1);
	assert(*bst_int_max(&bst) == 3);
}

void
foreach()
{
	int *i, j, arr[3];
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;
	struct bst_int_iter iter;

	bst = bst_int_from(key, val, 3);
	iter = bst_int_iter(&bst);

	j = 0;
	FOR_EACH(int, i, iter) {
		arr[j++] = *i;
	}

	assert(arr[0] == 2);
	assert(arr[1] == 1);
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
	ptr();
	foreach();

	return 0;
}
