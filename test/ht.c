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

#include "../src/ht.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 5

int hash(int x) { return x * 2; }
int cmp(int x, int y) { return x - y; }

INIT_HT_BOTH(int, int, hash, cmp, malloc, free);

static void
from()
{
	struct ht_int ht;
	int arr[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(arr, LEN);

	assert(ht.cap == 8);
	assert(ht_int_len(&ht) == 5);
	assert(ht.arr[0].val == 0);
	assert(ht.arr[1].val == 4);
	assert(ht.arr[2].val == 1);
	assert(ht.arr[3].state == NONE);
	assert(ht.arr[4].val == 2);
	assert(ht.arr[5].state == NONE);
	assert(ht.arr[6].val == 3);
	assert(ht.arr[7].state == NONE);
}

static void
get()
{
	struct ht_int ht;
	int arr[] = { 0, 1, 2, 3, 4 };
	int val;

	ht = ht_int_from(arr, LEN);

	val = 4;
	ht_int_get(&ht, &val);
	assert(val == 4);
	val = 3;
	ht_int_get(&ht, &val);
	assert(val == 3);
	val = 2;
	ht_int_get(&ht, &val);
	assert(val == 2);
	val = 1;
	ht_int_get(&ht, &val);
	assert(val == 1);
	val = 0;
	ht_int_get(&ht, &val);
	assert(val == 0);
}

static void
insert()
{
	struct ht_int ht;

	ht = ht_int_new();

	ht_int_insert(&ht, 0);
	ht_int_insert(&ht, 1);
	ht_int_insert(&ht, 2);
	ht_int_insert(&ht, 3);
	ht_int_insert(&ht, 4);

	assert(ht.cap == 8);
	assert(ht_int_len(&ht) == 5);
	assert(ht.arr[0].val == 0);
	assert(ht.arr[1].val == 4);
	assert(ht.arr[2].val == 1);
	assert(ht.arr[3].state == NONE);
	assert(ht.arr[4].val == 2);
	assert(ht.arr[5].state == NONE);
	assert(ht.arr[6].val == 3);
	assert(ht.arr[7].state == NONE);
}

static void
remove()
{
	struct ht_int ht;
	int arr[] = { 0, 1, 2, 3, 4 };
	int val;

	ht = ht_int_from(arr, LEN);

	val = 4;
	ht_int_remove(&ht, &val);
	assert(val == 4);
	val = 3;
	ht_int_remove(&ht, &val);
	assert(val == 3);
	val = 2;
	ht_int_remove(&ht, &val);
	assert(val == 2);
	val = 1;
	ht_int_remove(&ht, &val);
	assert(val == 1);
	val = 0;
	ht_int_remove(&ht, &val);
	assert(val == 0);

	assert(ht.cap == 8);
	assert(ht_int_len(&ht) == 0);
}

static void
iter()
{
	struct ht_int_iter iter;
	struct ht_int ht;
	int arr[] = { 0, 1, 2, 3, 4 };
	int val;

	ht = ht_int_from(arr, LEN);
	iter = ht_int_iter(&ht);

	assert(ht_int_next(&iter, &val) == 0);
	assert(val == 0);
	assert(ht_int_next(&iter, &val) == 0);
	assert(val == 4);
	assert(ht_int_next(&iter, &val) == 0);
	assert(val == 1);
	assert(ht_int_next(&iter, &val) == 0);
	assert(val == 2);
	assert(ht_int_next(&iter, &val) == 0);
	assert(val == 3);
	assert(ht_int_next(&iter, &val) != 0);
}

int
main()
{
	from();
	get();
	insert();
	remove();
	iter();

	return 0;
}
