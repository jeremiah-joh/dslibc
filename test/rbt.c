#include "../src/rbt.h"
#include <stdlib.h>
#include <assert.h>

#define LEN(a) (sizeof(a) / sizeof(*a))

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
	assert(rbt_int_insert(&rbt, 5) == 0);
	assert(rbt_int_insert(&rbt, 6) == 0);
	assert(rbt_int_insert(&rbt, 7) == 0);
	assert(rbt_int_insert(&rbt, 8) == 0);
	assert(rbt_int_insert(&rbt, 9) == 0);

	assert(rbt_int_len(&rbt) == 10);
	assert(rbt.root->val == 3);
	assert(rbt.root->kid[0]->val == 1);
	assert(rbt.root->kid[0]->kid[0]->val == 0);
	assert(rbt.root->kid[0]->kid[1]->val == 2);
	assert(rbt.root->kid[1]->val == 5);
	assert(rbt.root->kid[1]->kid[0]->val == 4);
	assert(rbt.root->kid[1]->kid[1]->val == 7);
	assert(rbt.root->kid[1]->kid[1]->kid[0]->val == 6);
	assert(rbt.root->kid[1]->kid[1]->kid[1]->val == 8);
	assert(rbt.root->kid[1]->kid[1]->kid[1]->kid[1]->val == 9);
}

static void
remove(void)
{
	struct rbt_int rbt;
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int val;

	rbt = rbt_int_from(arr, LEN(arr));

	val = 4;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 4);
	val = 0;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 0);
	val = 1;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 1);
	val = 8;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 8);
	val = 9;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 9);
	val = 3;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 3);
	val = 2;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 2);
	val = 7;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 7);
	val = 6;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 6);
	val = 5;
	assert(rbt_int_remove(&rbt, &val) == 0);
	assert(val == 5);

	assert(rbt_int_remove(&rbt, &val) != 0);
	assert(rbt_int_len(&rbt) == 0);
}

static void
free_t(void)
{
	struct rbt_int rbt;
	int arr[] = { 0, 1, 2, 3, 4 };

	rbt = rbt_int_from(arr, LEN(arr));

	rbt_int_free(&rbt);

	assert(rbt.root == NULL);
	assert(rbt.len == 0);
}

int
main(void)
{
	insert();
	remove();
	free_t();

	return 0;
}
