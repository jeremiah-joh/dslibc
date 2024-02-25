#include "../src/vec.h"
#include <assert.h>
#include <string.h>

static void
test_slice()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vec all = vec_from(arr, 5);
    vec sli = vec_slice(&all, 2, 4);
    assert(vec_length(&sli) == 2);
    assert(sli.arr[0] == 3 && sli.arr[1] == 4);
}

static void
test_push_pop()
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
test_insert_search_remove()
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
test_get_set_rmv()
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
test_nth()
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
test_resize()
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
test_free()
{
    vec vec = vec_new();
    vec_free(&vec);
    assert(vec.arr == NULL && vec.len == 0 && vec.cap == 0);
}

int
main()
{
    test_slice();
    test_push_pop();
    test_insert_search_remove();
    test_get_set_rmv();
    test_nth();
    test_resize();
    test_free();

    return 0;
}
