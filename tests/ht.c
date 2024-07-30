#include "../src/ht.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static size_t
hash_int_t(int x)
{
	return x;
}

static int
cmp_int(int x, int y)
{
	return y - x;
}

INIT_HT(int, int, hash_int_t, cmp_int, malloc, free);

void
from()
{
	struct ht_int ht;
	int val[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(val, 5);

	assert(ht.len == 5);
	assert(ht.arr[0].data == 0);
	assert(ht.arr[1].data == 1);
	assert(ht.arr[2].data == 2);
	assert(ht.arr[3].data == 3);
	assert(ht.arr[4].data == 4);
}

void
copy()
{
	struct ht_int ht, cp;
	int val[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(val, 5);
        cp = ht_int_copy(ht);

	assert(ht.len == cp.len);
	assert(ht.cap == cp.cap);
	assert(memcmp(ht.arr, cp.arr, cp.cap * sizeof(struct ht_int_node)) == 0);
}

void
insert()
{
	struct ht_int ht;

	ht = ht_int_new();

	ht_int_insert(&ht, 0);
	ht_int_insert(&ht, 1);
	ht_int_insert(&ht, 2);
	ht_int_insert(&ht, 3);
	ht_int_insert(&ht, 4);

	assert(ht.len == 5);
	assert(ht.cap == 8);
	assert(ht.arr[0].data == 0);
	assert(ht.arr[1].data == 1);
	assert(ht.arr[2].data == 2);
	assert(ht.arr[3].data == 3);
	assert(ht.arr[4].data == 4);
}

void
search()
{
	struct ht_int ht;
	int val[] = { 0, 1, 2, 3, 4 };
	int v;

	ht = ht_int_from(val, 5);

	v = 3;
	assert(ht_int_search(&ht, &v) == 0);
}

void
remove()
{
	struct ht_int ht;
	int val[] = { 0, 1, 2, 3, 4 };
	int v;

	ht = ht_int_from(val, 5);

	v = 1;
	assert(ht_int_remove(&ht, &v) == 0);
	v = 2;
	assert(ht_int_remove(&ht, &v) == 0);
	v = 3;
	assert(ht_int_remove(&ht, &v) == 0);

	assert(ht.len == 2);
	assert(ht.cap == 4);
	assert(ht.arr[0].data == 0);
	assert(ht.arr[1].data == 4);
}

void
foreach()
{
	struct ht_int ht;
	struct ht_int_iter iter;
	int val[] = { 0, 1, 2, 3, 4 };
	int i, j;

	ht = ht_int_from(val, 5);
	iter = ht_int_iter(&ht);

	j = 0;
	FOR_EACH(int, i, iter) {
		assert(i == j++);
	}
}

int
main()
{
	from();
	copy();
	insert();
	search();
	remove();
	foreach();

	return 0;
}
