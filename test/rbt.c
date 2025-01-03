/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024, 2025 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creatiheapommons.org/publicdomain/zero/1.0/>.
 */

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

	rbt = rbt_int_new();

	srand(1024);
	for (i = 0; i < 1024; i++) {
		assert(rbt_int_insert(&rbt, rand() % 1024) == 0);
		verify(&rbt);
	}
}

static void
test_remove(void)
{
	struct rbt_int rbt;
	int i, v;

	rbt = rbt_int_new();

	srand(1024);
	for (i = 0; i < 1024; i++) {
		v = rand() % 1024;
		assert(rbt_int_insert(&rbt, v) == 0);
		verify(&rbt);
	}
	
	srand(1024);
	for (i = 0; i < 1024; i++) {
		v = rand() % 1024;
		printf("remove: %d\n", v);
		assert(rbt_int_remove(&rbt, &v) == 0);
		verify(&rbt);
	}

	assert(rbt.root == NULL);
	assert(rbt.len == 0);
}

static void
test_free(void)
{
	struct rbt_int rbt;
	int arr[] = { 2, 0, 1, 4, 3 };

	rbt = rbt_int_from(arr, 5);

	rbt_int_free(&rbt);

	assert(rbt.root == NULL);
	assert(rbt.len == 0);
}

static void
test_next(void)
{
	struct rbt_int rbt;
	struct rbt_int_iter iter;
	int arr[] = { 2, 0, 1, 4, 3 };
	int val;

	rbt = rbt_int_from(arr, 5);
	iter = rbt_int_iter(&rbt);

	assert(rbt_int_next(&iter, &val) == 0);
	assert(val == 0);
	assert(rbt_int_next(&iter, &val) == 0);
	assert(val == 1);
	assert(rbt_int_next(&iter, &val) == 0);
	assert(val == 2);
	assert(rbt_int_next(&iter, &val) == 0);
	assert(val == 3);
	assert(rbt_int_next(&iter, &val) == 0);
	assert(val == 4);
	assert(rbt_int_next(&iter, &val) != 0);
}

int
main(void)
{
	test_insert();
	test_remove();
	test_free();
	test_next();

	return 0;
}
