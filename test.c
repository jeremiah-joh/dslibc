#include "src/vec.h"
#include "src/ll.h"
#include <assert.h>
#include <string.h>

static void
test_vec_slice()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vec all = vec_from_arr(arr, 5);
    vec sli = vec_slice(&all, 2, 4);
    assert(vec_length(&sli) == 2);
    assert(sli.arr[0] == 3 && sli.arr[1] == 4);
}

static void
test_vec_push_pop()
{
    int i, tmp;
    vec vec = vec_new();
    for (i = 0; i < 4; i++)
        vec_push_back(&vec, i);
    for (i = 0; i < 4; i++)
        vec_push_front(&vec, i);
    assert(vec_length(&vec) == 8);
    assert(vec_sizeof(&vec) == sizeof(int) * 9);

    for (i = 0; i < 4; i++) {
        vec_pop_back(&vec, &tmp);
        assert(tmp == 3 - i);
    }
    for (i = 0; i < 4; i++) {
        vec_pop_front(&vec, &tmp);
        assert(tmp == 3 - i);
    }
    assert(vec_length(&vec) == 0);
    assert(vec_sizeof(&vec) == sizeof(int) * 4);
}

static void
test_vec_insert_search_remove()
{
    vec vec = vec_new();
    int i;
    for (i = 0; i < 8; i++)
        vec_push_back(&vec, i);
    
    vec_insert(&vec, 11, 4);
    assert(vec.arr[4] == 11);
    assert(vec_search(&vec, 11) == 4);
    assert(vec_remove(&vec, 11) == 4);
}

static void
test_vec_get_set_rmv()
{
    vec vec = vec_new();
    int i, tmp;
    for (i = 0; i < 8; i++)
        vec_push_back(&vec, i);

    vec_getnth(&vec, &tmp, 3);
    assert(tmp == 3);

    vec_setnth(&vec, 10, 3);
    assert(vec.arr[3] == 10);

    vec_rmvnth(&vec, &tmp, 3);
    assert(tmp == 10);
    assert(vec_length(&vec) == 7);
}

static void
test_vec_nth()
{
    vec vec = vec_new();
    int i, tmp;
    for (i = 0; i < 8; i++)
        vec_push_back(&vec, i);
    
    tmp = *vec_nth(&vec, 3);
    assert(tmp == 3);

    *vec_front(&vec) = tmp;
    assert(vec.arr[0] == 3);

    tmp = *vec_back(&vec);
    assert(tmp == 7);
}

static void
test_vec_resize()
{
    vec vec = vec_new();
    int i;
    for (i = 0; i < 8; i++)
        vec_push_back(&vec, i);
    
    vec_resize(&vec, 0);
    assert(vec_length(&vec) == 0);
    assert(vec_sizeof(&vec) == sizeof(int) * 4);

    vec_resize(&vec, 10);
    assert(vec_length(&vec) == 0);
    assert(vec_sizeof(&vec) == sizeof(int) * 13);
}

static void
test_vec_free()
{
    vec vec = vec_new();
    vec_free(&vec);
    assert(vec.arr == NULL && vec.len == 0 && vec.cap == 0);
}

static void
test_sll_push()
{
    sll ll = sll_new();
    sll_push_back(&ll, 0);
    sll_push_back(&ll, 1);

    assert(ll.head->data == 0);
    assert(ll.head->next->data == 1);
    assert(ll.tail == ll.head->next);
}

int
main()
{
    test_vec_slice();
    test_vec_push_pop();
    test_vec_insert_search_remove();
    test_vec_get_set_rmv();
    test_vec_nth();
    test_vec_resize();
    test_vec_free();

    test_sll_push();

    return 0;
}
