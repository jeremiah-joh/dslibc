#include "../src/ht.h"
#include <assert.h>

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
construct()
{
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

int
main()
{
	insert();

	return 0;
}
