#include "../src/bst.h"
#include <assert.h>

INIT_BST(int, int, int);

int
cmp(int x, int y)
{
	return x - y;
}

void
from()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3, cmp);

	assert(bst.len == 3);
	assert(bst.root->val == 2);
	assert(bst.root->rch->val == 3);
	assert(bst.root->lch->val == 1);
}

void
insert()
{
	struct bst_int bst;

	bst = bst_int_new(cmp);

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

	bst = bst_int_from(key, val, 3, cmp);
	
	bst_int_search(&bst, 1, &v);

	assert(v == 1);
}

void
remove()
{
	int v;
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3, cmp);
	
	bst_int_remove(&bst, 1, &v);

	assert(v == 1);
	assert(bst.len == 2);
}

void
ptr()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3, cmp);
	
	assert(*bst_int_getptr(&bst, 3) == 3);
	assert(*bst_int_root(&bst) == 2);
	assert(*bst_int_min(&bst) == 1);
	assert(*bst_int_max(&bst) == 3);
}

void
t_free()
{
	int key[] = { 2, 1, 3 };
	int val[] = { 2, 1, 3 };
	struct bst_int bst;

	bst = bst_int_from(key, val, 3, cmp);

	bst_int_free(&bst);

	assert(bst.root == NULL);
	assert(bst.len == 0);
}

int
main()
{
	from();
	insert();
	search();
	remove();
	ptr();
	t_free();

	return 0;
}
