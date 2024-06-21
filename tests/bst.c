#include "../src/bst.h"
#include <assert.h>

int
cmp(int x, int y)
{
	return x - y;
}

INIT_BST(int, int, int, cmp);

static void
square(int *x)
{
	*x *= *x;
}

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
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3);

	bst_int_foreach(&bst, square);

	assert(bst.root->val == 4);
	assert(bst.root->lch->val == 1);
	assert(bst.root->rch->val == 9);
}

void
retain()
{
	int key[] = { 1, 2, 3 };
	int val[] = { 1, 2, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3);

	bst_int_retain(&bst, even);

	assert(bst.len == 1);
	assert(bst.root->val == 2);
}

void
map()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst, map;

	bst = bst_int_from(key, val, 3);
	map = bst_int_map(bst, increase);

	assert(map.root->val == 3);
	assert(map.root->lch->val == 2);
	assert(map.root->rch->val == 4);
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
	retain();
	map();

	return 0;
}
