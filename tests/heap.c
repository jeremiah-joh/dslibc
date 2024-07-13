#include "../src/heap.h"
#include <assert.h>

static int
cmp_int(int x, int y)
{
	return x - y;
}

INIT_MIN_HEAP(int, int, cmp_int);

void
from()
{
	struct heap_int heap;
	int arr[] = { 4, 3, 2, 1, 0 };

	heap = heap_int_from(arr, 5);

	assert(heap.len == 5);
	assert(heap.arr[0] == 0);
	assert(heap.arr[1] == 1);
	assert(heap.arr[2] == 3);
	assert(heap.arr[3] == 4);
	assert(heap.arr[4] == 2);
}

void
push()
{
	struct heap_int heap;

	heap = heap_int_new();

	heap_int_push(&heap, 4);
	heap_int_push(&heap, 3);
	heap_int_push(&heap, 2);
	heap_int_push(&heap, 1);
	heap_int_push(&heap, 0);

	assert(heap.len == 5);
	assert(heap.cap == 8);
	assert(heap.arr[0] == 0);
	assert(heap.arr[1] == 1);
	assert(heap.arr[2] == 3);
	assert(heap.arr[3] == 4);
	assert(heap.arr[4] == 2);
}

void
pop()
{
	struct heap_int heap;
	int arr[] = { 4, 3, 2, 1, 0 };
	int val;

	heap = heap_int_from(arr, 5);
	heap_int_pop(&heap, &val);

	assert(heap.len == 4);
	assert(heap.cap == 8);
	assert(heap.arr[0] == 1);
	assert(heap.arr[1] == 2);
	assert(heap.arr[2] == 3);
	assert(heap.arr[3] == 4);
}

void
foreach()
{
	int *i, j, val[] = { 1, 2, 3, 4, 5 };
	struct heap_int heap;

	heap = heap_int_from(val, 5);

	j = 1;
	FOR_EACH(int, i, heap) {
		assert(*i == j++);
	}
}

int
main()
{
	from();
	push();
	pop();
	foreach();

	return 0;
}
