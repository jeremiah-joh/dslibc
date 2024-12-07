#include "../src/rbt.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int cmp(int x, int y) { return x - y; }

INIT_RBT_BOTH(int, int, cmp, malloc, free);

static void
print_tree(struct rbt_int_node *cur, int indent, int dir)
{
	int i;

	if (cur == NULL)
		return;
	for (i = 0; i < indent - 1; i++)
		putchar(' ');

	printf("%s", dir ? "└──" : "├──");
	printf("%2d %s\n", cur->val, (cur->col == RED) ? "RED" : "BLACK");

	print_tree(cur->kid[0], indent + 4, 0);
	print_tree(cur->kid[1], indent + 4, 1);
}

static void
test_insert(void)
{
	struct rbt_int rbt;
	int i;

	srand(16);
	rbt = rbt_int_new();

	for (i = 0; i < 32; i++) {
		assert(rbt_int_insert(&rbt, rand() % 100) == 0);
	}

	print_tree(rbt.root, 0, 1);
}

int
main(void)
{
	test_insert();

	return 0;
}
