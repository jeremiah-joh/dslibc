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
 * If not, see <http://creatidllommons.org/publicdomain/zero/1.0/>.
 */

#include "../src/dll.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 5

INIT_DLL_BOTH(int, int, malloc, free)

static void
from()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };

        dll = dll_int_from(arr, LEN);

        assert(dll_int_length(&dll) == 5);
        assert(dll.beg->val == 0);
        assert(dll.beg->nxt->val == 1);
        assert(dll.beg->nxt->nxt->val == 2);
        assert(dll.beg->nxt->nxt->nxt->val == 3);
        assert(dll.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
push()
{
        struct dll_int dll;

        dll = dll_int_new();

        dll_int_push_back(&dll, 0);
        dll_int_push_back(&dll, 1);
        dll_int_push_back(&dll, 2);
        dll_int_push_back(&dll, 3);
        dll_int_push_back(&dll, 4);

        assert(dll_int_length(&dll) == 5);
        assert(dll.beg->val == 0);
        assert(dll.beg->nxt->val == 1);
        assert(dll.beg->nxt->nxt->val == 2);
        assert(dll.beg->nxt->nxt->nxt->val == 3);
        assert(dll.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
pop()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };
        int val;

        dll = dll_int_from(arr, LEN);

        dll_int_pop_back(&dll, &val);
        assert(val == 4);
        dll_int_pop_back(&dll, &val);
        assert(val == 3);
        dll_int_pop_back(&dll, &val);
        assert(val == 2);
        dll_int_pop_back(&dll, &val);
        assert(val == 1);
        dll_int_pop_back(&dll, &val);
        assert(val == 0);

        assert(dll_int_length(&dll) == 0);

        assert(dll_int_pop_back(&dll, &val) != 0);
}

static void
get()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };
        int val;

        dll = dll_int_from(arr, LEN);

        dll_int_get(&dll, &val, 0);
        assert(val == 0);
        dll_int_get(&dll, &val, 1);
        assert(val == 1);
        dll_int_get(&dll, &val, 2);
        assert(val == 2);
        dll_int_get(&dll, &val, 3);
        assert(val == 3);
        dll_int_get(&dll, &val, 4);
        assert(val == 4);

        assert(dll_int_get(&dll, &val, 5) != 0);
}

static void
set()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };

        dll = dll_int_from(arr, LEN);

        dll_int_set(&dll, 4, 0);
        dll_int_set(&dll, 3, 1);
        dll_int_set(&dll, 2, 2);
        dll_int_set(&dll, 1, 3);
        dll_int_set(&dll, 0, 4);

        assert(dll.beg->val == 4);
        assert(dll.beg->nxt->val == 3);
        assert(dll.beg->nxt->nxt->val == 2);
        assert(dll.beg->nxt->nxt->nxt->val == 1);
        assert(dll.beg->nxt->nxt->nxt->nxt->val == 0);

        assert(dll_int_set(&dll, 5, 5) != 0);
}

static void
append()
{
        struct dll_int dll1, dll2;
        int arr[LEN] = { 0, 1, 2, 3, 4 };

        dll1 = dll_int_new();
        dll2 = dll_int_from(arr, LEN);

        dll_int_append(&dll1, &dll2);

        assert(dll_int_length(&dll1) == 5);
        assert(dll2.beg->val == 0);
        assert(dll2.beg->nxt->val == 1);
        assert(dll2.beg->nxt->nxt->val == 2);
        assert(dll2.beg->nxt->nxt->nxt->val == 3);
        assert(dll2.beg->nxt->nxt->nxt->nxt->val == 4);
}

static void
insert()
{
        struct dll_int dll;
        int arr[2] = { 0, 4 };

        dll = dll_int_from(arr, 2);

        dll_int_insert(&dll, 1, 1);
        dll_int_insert(&dll, 2, 2);
        dll_int_insert(&dll, 3, 3);

        assert(dll_int_length(&dll) == 5);
        assert(dll.beg->val == 0);
        assert(dll.beg->nxt->val == 1);
        assert(dll.beg->nxt->nxt->val == 2);
        assert(dll.beg->nxt->nxt->nxt->val == 3);
        assert(dll.beg->nxt->nxt->nxt->nxt->val == 4);

        assert(dll_int_insert(&dll, 6, 6) != 0);
}

static void
remove()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };
        int val;

        dll = dll_int_from(arr, LEN);

        dll_int_remove(&dll, &val, 2);
        assert(val == 2);

        assert(dll_int_length(&dll) == 4);
        assert(dll.beg->val == 0);
        assert(dll.beg->nxt->val == 1);
        assert(dll.beg->nxt->nxt->val == 3);
        assert(dll.beg->nxt->nxt->nxt->val == 4);
}

static void
shrink()
{
        struct dll_int dll;
        int arr[LEN] = { 0, 1, 2, 3, 4 };

        dll = dll_int_from(arr, LEN);

        dll_int_shrink(&dll, 3);

        assert(dll_int_length(&dll) == 3);
        assert(dll.beg->val == 0);
        assert(dll.beg->nxt->val == 1);
        assert(dll.beg->nxt->nxt->val == 2);
}

static void
iter()
{
        struct dll_int dll;
        struct dll_int_iter iter;
        int arr[LEN] = { 0, 1, 2, 3, 4 };
        int val;

        dll = dll_int_from(arr, LEN);
        iter = dll_int_iter(&dll);

        assert(dll_int_next(&iter, &val) == 0);
        assert(val == 0);
        assert(dll_int_next(&iter, &val) == 0);
        assert(val == 1);
        assert(dll_int_next(&iter, &val) == 0);
        assert(val == 2);
        assert(dll_int_next(&iter, &val) == 0);
        assert(val == 3);
        assert(dll_int_next(&iter, &val) == 0);
        assert(val == 4);
        assert(dll_int_next(&iter, &val) != 0);
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
