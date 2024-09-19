#include "../src/bst.h"
#include <stdlib.h>
#include <assert.h>

#define LEN 5

int cmp(int x, int y) { return x - y; }

INIT_BST_BOTH(int, int, cmp, malloc, free)

static void
from()
{
        struct bst_int bst;
        int arr[] = { 3, 4, 1, 0, 2 };

        bst = bst_int_from(arr, LEN);

        assert(bst_int_length(&bst) == 5);
        assert(bst.root->val == 3);
        assert(bst.root->kid[0]->val == 1);
        assert(bst.root->kid[1]->val == 4);
        assert(bst.root->kid[0]->kid[0]->val == 0);
        assert(bst.root->kid[0]->kid[1]->val == 2);
}

static void
get()
{
        struct bst_int bst;
        int arr[] = { 3, 4, 1, 0, 2 };
        int val;

        bst = bst_int_from(arr, LEN);

        val = 0;
        bst_int_get(&bst, &val);
        assert(val == 0);
        val = 1;
        bst_int_get(&bst, &val);
        assert(val == 1);
        val = 2;
        bst_int_get(&bst, &val);
        assert(val == 2);
        val = 3;
        bst_int_get(&bst, &val);
        assert(val == 3);
        val = 4;
        bst_int_get(&bst, &val);
        assert(val == 4);
}

static void
insert()
{
        struct bst_int bst;
        int arr[] = { 3, 4, 1, 0, 2 };

        bst = bst_int_new();

        bst_int_insert(&bst, arr[0]);
        bst_int_insert(&bst, arr[1]);
        bst_int_insert(&bst, arr[2]);
        bst_int_insert(&bst, arr[3]);
        bst_int_insert(&bst, arr[4]);

        assert(bst_int_length(&bst) == 5);
        assert(bst.root->val == 3);
        assert(bst.root->kid[0]->val == 1);
        assert(bst.root->kid[1]->val == 4);
        assert(bst.root->kid[0]->kid[0]->val == 0);
        assert(bst.root->kid[0]->kid[1]->val == 2);
}

static void
remove()
{
        struct bst_int bst;
        int arr[] = { 3, 4, 1, 0, 2 };
        int val;

        bst = bst_int_from(arr, LEN);

        val = 1;
        bst_int_remove(&bst, &val);
        assert(val == 1);
        val = 0;
        bst_int_remove(&bst, &val);
        assert(val == 0);
        val = 3;
        bst_int_remove(&bst, &val);
        assert(val == 3);
        val = 4;
        bst_int_remove(&bst, &val);
        assert(val == 4);
        val = 2;
        bst_int_remove(&bst, &val);
        assert(val == 2);

        assert(bst_int_length(&bst) == 0);
}

static void
iter()
{
        struct bst_int bst;
        struct bst_int_iter iter;
        int arr[] = { 3, 4, 1, 0, 2 };
        int val;

        bst = bst_int_from(arr, LEN);
        iter = bst_int_iter(&bst);

        bst_int_next(&iter, &val);
        assert(val == 0);
        bst_int_next(&iter, &val);
        assert(val == 1);
        bst_int_next(&iter, &val);
        assert(val == 2);
        bst_int_next(&iter, &val);
        assert(val == 3);
        bst_int_next(&iter, &val);
        assert(val == 4);
        
        assert(bst_int_next(&iter, &val) != 0);
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
