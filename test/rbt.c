#include "../src/rbt.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

static void
verify_red(struct rbt_int_node *cur)
{
	if (cur == NULL)
		return;
	if (COLOR(cur) == RED) {
		assert(COLOR(cur->par) == BLACK);
		assert(COLOR(cur->kid[0]) == BLACK);
		assert(COLOR(cur->kid[1]) == BLACK);
	}

	verify_red(cur->kid[0]);
	verify_red(cur->kid[1]);
}

static void
verify_num(struct rbt_int_node *cur, int black_n, int *black_path_n)
{
	if (COLOR(cur) == BLACK)
		black_n++;
	if (cur) {
		verify_num(cur->kid[0], black_n, black_path_n);
		verify_num(cur->kid[1], black_n, black_path_n);
	} else {
		if (*black_path_n < 0)
			*black_path_n = black_n;
		else	
			assert(black_n == *black_path_n);
	}
}

static void
verify(struct rbt_int *rbt)
{
	int black_path_n;

	black_path_n = -1;

	verify_red(rbt->root);
	verify_num(rbt->root, 0, &black_path_n);
}

static void
test_insert(void)
{
	struct rbt_int rbt;
	int i;

	srand(16);
	rbt = rbt_int_new();

	for (i = 0; i < 32; i++)
		assert(rbt_int_insert(&rbt, rand() % 100) == 0);

	verify(&rbt);
}

int
main(void)
{
	test_insert();

	return 0;
}
