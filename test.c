#include "src/vec.h"
#include "src/ll.h"
#include <assert.h>
#include <string.h>

static void
test_vec_copy()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vec old = vec_from_arr(arr, 5);
    vec cpy = vec_copy(old);

    assert(memcmp(old.arr, cpy.arr, sizeof(int) * old.len) == 0);
}

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
test_vec_nthptr()
{
    vec vec = vec_new();
    int i, tmp;
    for (i = 0; i < 8; i++)
        vec_push_back(&vec, i);
    
    tmp = *vec_nthptr(&vec, 3);
    assert(tmp == 3);

    *vec_first(&vec) = tmp;
    assert(vec.arr[0] == 3);

    tmp = *vec_last(&vec);
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
test_sll_copy()
{
    sll ll, copy;
    size_t i;

    ll = sll_new();

    sll_push(&ll, 0);
    sll_push(&ll, 1);
    sll_push(&ll, 2);

    copy = sll_copy(ll);

    for (i = 0; i < sll_length(&ll); i++)
        assert(*sll_nthptr(&ll, i) == *sll_nthptr(&copy, i));
}

static void
test_sll_push()
{
    sll ll = sll_new();
    sll_push(&ll, 0);
    sll_push(&ll, 1);

    assert(ll.root->data == 1);
    assert(ll.root->next->data == 0);
}

static void
test_sll_pop()
{
    sll ll = sll_new();
    type data;

    sll_push(&ll, 0);
    sll_push(&ll, 1);

    sll_pop(&ll, &data);
    assert(ll.root->data == 0);
    assert(data == 1);
    assert(sll_length(&ll) == 1);
}

static void
test_sll_insert()
{
    sll ll = sll_new();

    sll_push(&ll, 0);
    sll_push(&ll, 1);

    sll_insert(&ll, 2, 1);

    assert(ll.root->data == 1);
    assert(ll.root->next->data == 2);
    assert(ll.root->next->next->data == 0);
    assert(sll_length(&ll) == 3);
}

static void
test_sll_search_remove()
{
    size_t i;
    sll ll = sll_new();

    for (i = 0; i < 8; i++)
        sll_push(&ll, i);
    
    assert(sll_search(&ll, 4) == 3);
    assert(sll_remove(&ll, 4) == 3);
    assert(sll_length(&ll) == 7);
}

static void
test_sll_get_set_rmv()
{
    type data;
    sll ll = sll_new();

    sll_push(&ll, 0);
    sll_push(&ll, 1);
    sll_push(&ll, 2);

    sll_getnth(&ll, &data, 1);
    assert(data == 1);

    sll_setnth(&ll, data, 0);
    assert(ll.root->data == data);

    sll_rmvnth(&ll, &data, 2);
    assert(ll.len == 2);
    assert(ll.root->next->next == NULL);
}

static void
test_sll_nthptr()
{
    sll ll = sll_new();

    sll_push(&ll, 0);
    sll_push(&ll, 1);

    assert(*sll_nthptr(&ll, 0) == ll.root->data);
    assert(*sll_nthptr(&ll, 1) == ll.root->next->data);

    assert(*sll_first(&ll) == 1);
    assert(*sll_last(&ll) == 0);
}

static void
test_sll_free()
{
    int i;
    sll ll = sll_new();
    
    for (i = 0; i < 8; i++)
        sll_push(&ll, i);
    
    sll_free(&ll);

    assert(ll.root == NULL);
    assert(sll_length(&ll) == 0);
}

static void
test_dll_copy()
{
    dll old, cpy;
    size_t i;

    old = dll_new();
    for (i = 0; i < 8; i++)
        dll_push_back(&old, i);

    cpy = dll_copy(old);
    for (i = 0; i < 8; i++)
        assert(*dll_nthptr(&old, i) == *dll_nthptr(&cpy, i));
}

static void
test_dll_push()
{
    struct dll_node *tmp;
    dll ll = dll_new();
    size_t i;

    for (i = 0; i < 8; i++)
        dll_push_back(&ll, i);

    for (i = 0, tmp = ll.head; tmp != NULL; i++, tmp = tmp->next)
        assert(tmp->data == i);
    
    ll = dll_new();
    
    for (i = 0; i < 8; i++)
        dll_push_front(&ll, i);

    for (i = 0, tmp = ll.tail; tmp != NULL; i++, tmp = tmp->prev)
        assert(tmp->data == i);
}

static void
test_dll_pop()
{
    dll ll = dll_new();
    size_t i;
    int data;

    for (i = 0; i < 4; i++)
        dll_push_back(&ll, i);

    dll_pop_back(&ll, &data);
    assert(data == 3);

    dll_pop_front(&ll, &data);
    assert(data == 0);

    assert(dll_length(&ll) == 2);
}

static void
test_dll_insert()
{
    dll ll = dll_new();
    size_t i;

    for (i = 0; i < 4; i++)
        dll_push_back(&ll, i);

    dll_insert(&ll, 10, 1);
    assert(*dll_nthptr(&ll, 1) == 10);
}

static void
test_dll_search_remove()
{
    dll ll = dll_new();
    size_t i;

    for (i = 0; i < 4; i++)
        dll_push_back(&ll, i);

    assert(dll_search(&ll, 1) == 1);
    assert(dll_remove(&ll, 1) == 1);
}

static void
test_dll_get_set_rmv()
{
    dll ll = dll_new();
    size_t i;
    int data;

    for (i = 0; i < 4; i++)
        dll_push_back(&ll, i);

    dll_getnth(&ll, &data, 1);
    assert(data == 1);

    dll_setnth(&ll, 2, 1);
    assert(*dll_nthptr(&ll, 1) == 2);

    dll_rmvnth(&ll, &data, 1);
    assert(data == 2);
}

static void
test_dll_nthptr()
{
    dll ll = dll_new();
    size_t i;

    for (i = 0; i < 4; i++)
        dll_push_back(&ll, i);

    assert(*dll_nthptr(&ll, 2) == 2);
    assert(*dll_first(&ll) == 0);
    assert(*dll_last(&ll) == 3);
}

int
main()
{
    test_vec_copy();
    test_vec_slice();
    test_vec_push_pop();
    test_vec_insert_search_remove();
    test_vec_get_set_rmv();
    test_vec_nthptr();
    test_vec_resize();
    test_vec_free();

    test_sll_copy();
    test_sll_push();
    test_sll_pop();
    test_sll_insert();
    test_sll_search_remove();
    test_sll_get_set_rmv();
    test_sll_nthptr();
    test_sll_free();

    test_dll_copy();
    test_dll_push();
    test_dll_pop();
    test_dll_insert();
    test_dll_search_remove();
    test_dll_get_set_rmv();
    test_dll_nthptr();

    return 0;
}
