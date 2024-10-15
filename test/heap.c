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
 * If not, see <http://creatiheapommons.org/publicdomain/zero/1.0/>.
 */

#include "../src/heap.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 5

int cmp(int x, int y) { return x - y; }

INIT_MAX_HEAP_BOTH(int, int, cmp, malloc, realloc, free);

static void
from()
{
	struct heap_int heap;
	int arr[LEN] = { 0, 1, 2, 3, 4 };

	heap = heap_int_from(arr, LEN);

	assert(heap_int_len(&heap) == 5);
	assert(heap.arr[0] == 4);
	assert(heap.arr[1] == 3);
	assert(heap.arr[2] == 1);
	assert(heap.arr[3] == 0);
	assert(heap.arr[4] == 2);
}

static void
push()
{
	struct heap_int heap;

	heap = heap_int_new();

	heap_int_push(&heap, 0);
	heap_int_push(&heap, 1);
	heap_int_push(&heap, 2);
	heap_int_push(&heap, 3);
	heap_int_push(&heap, 4);

	assert(heap_int_len(&heap) == 5);
	assert(heap.arr[0] == 4);
	assert(heap.arr[1] == 3);
	assert(heap.arr[2] == 1);
	assert(heap.arr[3] == 0);
	assert(heap.arr[4] == 2);
}

static void
pop()
{
	struct heap_int heap;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	heap = heap_int_from(arr, LEN);

	heap_int_pop(&heap, &val);
	assert(val == 4);
	heap_int_pop(&heap, &val);
	assert(val == 3);
	heap_int_pop(&heap, &val);
	assert(val == 2);
	heap_int_pop(&heap, &val);
	assert(val == 1);
	heap_int_pop(&heap, &val);
	assert(val == 0);

	assert(heap_int_len(&heap) == 0);

	assert(heap_int_pop(&heap, &val) != 0);
}

static void
get()
{
	struct heap_int heap;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	heap = heap_int_from(arr, LEN);

	val = 0;
	heap_int_get(&heap, &val);
	assert(val == 0);
	val = 1;
	heap_int_get(&heap, &val);
	assert(val == 1);
	val = 2;
	heap_int_get(&heap, &val);
	assert(val == 2);
	val = 3;
	heap_int_get(&heap, &val);
	assert(val == 3);
	val = 4;
	heap_int_get(&heap, &val);
	assert(val == 4);

	val = 5;
	assert(heap_int_get(&heap, &val) != 0);
}

static void
iter()
{
	struct heap_int heap;
	struct heap_int_iter iter;
	int arr[LEN] = { 0, 1, 2, 3, 4 };
	int val;

	heap = heap_int_from(arr, LEN);
	iter = heap_int_iter(&heap);

	assert(heap_int_next(&iter, &val) == 0);
	assert(val == 4);
	assert(heap_int_next(&iter, &val) == 0);
	assert(val == 3);
	assert(heap_int_next(&iter, &val) == 0);
	assert(val == 1);
	assert(heap_int_next(&iter, &val) == 0);
	assert(val == 0);
	assert(heap_int_next(&iter, &val) == 0);
	assert(val == 2);
	assert(heap_int_next(&iter, &val) != 0);
}

int
main()
{
	from();
	push();
	pop();
	get();
	iter();

	return 0;
}
