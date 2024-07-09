#include "../src/ht.h"
#include <assert.h>
#include <string.h>

static size_t
hash_int(int x)
{
	return x;
}

static int
cmp_int(int x, int y)
{
	return y - x;
}

INIT_HT(int, int, int, hash_int, cmp_int);

void
from()
{
	struct ht_int ht;
	int key[] = { 0, 1, 2, 3, 4 };
	int val[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(key, val, 5);

	assert(ht.len == 5);
	assert(ht.arr[0].val == 0);
	assert(ht.arr[1].val == 1);
	assert(ht.arr[2].val == 2);
	assert(ht.arr[3].val == 3);
	assert(ht.arr[4].val == 4);
}

void
copy()
{
	struct ht_int ht, cp;
	int key[] = { 0, 1, 2, 3, 4 };
	int val[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(key, val, 5);
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

	ht_int_insert(&ht, 0, 0);
	ht_int_insert(&ht, 1, 1);
	ht_int_insert(&ht, 2, 2);
	ht_int_insert(&ht, 3, 3);
	ht_int_insert(&ht, 4, 4);

	assert(ht.len == 5);
	assert(ht.cap == 8);
	assert(ht.arr[0].val == 0);
	assert(ht.arr[1].val == 1);
	assert(ht.arr[2].val == 2);
	assert(ht.arr[3].val == 3);
	assert(ht.arr[4].val == 4);
}

void
search()
{
	struct ht_int ht;
	int key[] = { 0, 1, 2, 3, 4 };
	int val[] = { 0, 1, 2, 3, 4 };
	int v;

	ht = ht_int_from(key, val, 5);
	assert(ht_int_search(&ht, 3, &v) == 0);

	assert(v == 3);
}

void
remove()
{
	struct ht_int ht;
	int key[] = { 0, 1, 2, 3, 4 };
	int val[] = { 0, 1, 2, 3, 4 };
	int v;

	ht = ht_int_from(key, val, 5);
	assert(ht_int_remove(&ht, 1, &v) == 0);
	assert(ht_int_remove(&ht, 2, &v) == 0);
	assert(ht_int_remove(&ht, 3, &v) == 0);

	assert(ht.len == 2);
	assert(ht.cap == 4);
	assert(ht.arr[0].val == 0);
	assert(ht.arr[1].val == 4);
}

void
ptr()
{
	struct ht_int ht;
	int key[] = { 0, 1, 2, 3, 4 };
	int val[] = { 0, 1, 2, 3, 4 };

	ht = ht_int_from(key, val, 5);

	assert(*ht_int_ptr(&ht, 2) == 2);
}

int
main()
{
	from();
	copy();
	insert();
	search();
	remove();
	ptr();

	return 0;
}
