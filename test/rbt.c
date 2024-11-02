#include "../src/rbt.h"
#include <stdlib.h>
#include <assert.h>

#define LEN 5

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

static void
insert(void)
{
	struct rbt_int rbt;

	rbt = rbt_int_new();

	assert(rbt_int_insert(&rbt, 0) == 0);
	assert(rbt_int_insert(&rbt, 1) == 0);
	assert(rbt_int_insert(&rbt, 2) == 0);
	assert(rbt_int_insert(&rbt, 3) == 0);
	assert(rbt_int_insert(&rbt, 4) == 0);

	assert(rbt.root->val == 1);
	assert(rbt.root->kid[0]->val == 0);
	assert(rbt.root->kid[1]->val == 3);
	assert(rbt.root->kid[1]->kid[0]->val == 2);
	assert(rbt.root->kid[1]->kid[1]->val == 4);
}

static void
free_t(void)
{
	struct rbt_int rbt;
	int arr[] = { 0, 1, 2, 3, 4 };

	rbt = rbt_int_from(arr, LEN);

	rbt_int_free(&rbt);

	assert(rbt.root == NULL);
	assert(rbt.len == 0);
}

int
main(void)
{
	insert();
	free_t();

	return 0;
}
