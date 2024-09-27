/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creatisllommons.org/publicdomain/zero/1.0/>.
 */

#include "../src/sll.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 5

INIT_SLL_BOTH(int, int, malloc, free)

static void
from()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	sll = sll_int_from(arr, LEN);

	assert(sll_int_len(&sll) == 5);
	assert(sll.beg->val == 0);
	assert(sll.beg->nxt->val == 1);
	assert(sll.beg->nxt->nxt->val == 2);
	assert(sll.beg->nxt->nxt->nxt->val == 3);
	assert(sll.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
push()
{
	struct sll_int sll;

	sll = sll_int_new();

	sll_int_push(&sll, 0);
	sll_int_push(&sll, 1);
	sll_int_push(&sll, 2);
	sll_int_push(&sll, 3);
	sll_int_push(&sll, 4);

	assert(sll_int_len(&sll) == 5);
	assert(sll.beg->val == 0);
	assert(sll.beg->nxt->val == 1);
	assert(sll.beg->nxt->nxt->val == 2);
	assert(sll.beg->nxt->nxt->nxt->val == 3);
	assert(sll.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
pop()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	sll = sll_int_from(arr, LEN);

	sll_int_pop(&sll, &val);
	assert(val == 0);
	sll_int_pop(&sll, &val);
	assert(val == 1);
	sll_int_pop(&sll, &val);
	assert(val == 2);
	sll_int_pop(&sll, &val);
	assert(val == 3);
	sll_int_pop(&sll, &val);
	assert(val == 4);

	assert(sll_int_len(&sll) == 0);

	assert(sll_int_pop(&sll, &val) != 0);
}

static void
get()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	sll = sll_int_from(arr, LEN);

	sll_int_get(&sll, &val, 0);
	assert(val == 0);
	sll_int_get(&sll, &val, 1);
	assert(val == 1);
	sll_int_get(&sll, &val, 2);
	assert(val == 2);
	sll_int_get(&sll, &val, 3);
	assert(val == 3);
	sll_int_get(&sll, &val, 4);
	assert(val == 4);

	assert(sll_int_get(&sll, &val, 5) != 0);
}

static void
set()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	sll = sll_int_from(arr, LEN);

	sll_int_set(&sll, 4, 0);
	sll_int_set(&sll, 3, 1);
	sll_int_set(&sll, 2, 2);
	sll_int_set(&sll, 1, 3);
	sll_int_set(&sll, 0, 4);

	assert(sll.beg->val == 4);
	assert(sll.beg->nxt->val == 3);
	assert(sll.beg->nxt->nxt->val == 2);
	assert(sll.beg->nxt->nxt->nxt->val == 1);
	assert(sll.beg->nxt->nxt->nxt->nxt->val == 0);

	assert(sll_int_set(&sll, 5, 5) != 0);
}

static void
append()
{
	struct sll_int sll1, sll2;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	sll1 = sll_int_new();
	sll2 = sll_int_from(arr, LEN);

	sll_int_append(&sll1, &sll2);

	assert(sll_int_len(&sll1) == 5);
	assert(sll2.beg->val == 0);
	assert(sll2.beg->nxt->val == 1);
	assert(sll2.beg->nxt->nxt->val == 2);
	assert(sll2.beg->nxt->nxt->nxt->val == 3);
	assert(sll2.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
insert()
{
	struct sll_int sll;
	int arr[2] = { 0, 4 };

	sll = sll_int_from(arr, 2);

	sll_int_insert(&sll, 1, 1);
	sll_int_insert(&sll, 2, 2);
	sll_int_insert(&sll, 3, 3);

	assert(sll_int_len(&sll) == 5);
	assert(sll.beg->val == 0);
	assert(sll.beg->nxt->val == 1);
	assert(sll.beg->nxt->nxt->val == 2);
	assert(sll.beg->nxt->nxt->nxt->val == 3);
	assert(sll.beg->nxt->nxt->nxt->nxt->val == 4);

	assert(sll_int_insert(&sll, 6, 6) != 0);
}

static void
remove()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	sll = sll_int_from(arr, LEN);

	sll_int_remove(&sll, &val, 2);
	assert(val == 2);

	assert(sll_int_len(&sll) == 4);
	assert(sll.beg->val == 0);
	assert(sll.beg->nxt->val == 1);
	assert(sll.beg->nxt->nxt->val == 3);
	assert(sll.beg->nxt->nxt->nxt->val == 4);
}

static void
shrink()
{
	struct sll_int sll;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	sll = sll_int_from(arr, LEN);

	sll_int_shrink(&sll, 3);

	assert(sll_int_len(&sll) == 3);
	assert(sll.beg->val == 0);
	assert(sll.beg->nxt->val == 1);
	assert(sll.beg->nxt->nxt->val == 2);
}

static void
iter()
{
	struct sll_int sll;
	struct sll_int_iter iter;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	sll = sll_int_from(arr, LEN);
	iter = sll_int_iter(&sll);

	assert(sll_int_next(&iter, &val) == 0);
	assert(val == 0);
	assert(sll_int_next(&iter, &val) == 0);
	assert(val == 1);
	assert(sll_int_next(&iter, &val) == 0);
	assert(val == 2);
	assert(sll_int_next(&iter, &val) == 0);
	assert(val == 3);
	assert(sll_int_next(&iter, &val) == 0);
	assert(val == 4);
	assert(sll_int_next(&iter, &val) != 0);
}

int
main()
{
	from();
	push();
	pop();
	get();
	set();
	append();
	insert();
	remove();
	shrink();
	iter();

	return 0;
}
