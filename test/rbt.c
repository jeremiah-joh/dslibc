#include "../src/rbt.h"
#include <stdlib.h>
#include <assert.h>

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

int
main(void)
{
	insert();

	return 0;
}
