#include "../src/vec.h"
#include <assert.h>

INIT_VEC(int, int);

int
main()
{
    vec_int vec, sli;
    vec = vec_int_new();
    vec_int_push_back(&vec, 0);
    vec_int_push_back(&vec, 1);
    vec_int_push_back(&vec, 2);
    vec_int_push_back(&vec, 3);
    vec_int_push_back(&vec, 4);

    assert(vec_int_length(&vec) == 5);
    assert(vec_int_sizeof(&vec) == 6 * sizeof(int));

    int val;
    vec_int_pop_back(&vec, &val);
    vec_int_pop_back(&vec, &val);
    vec_int_pop_back(&vec, &val);
    vec_int_pop_back(&vec, &val);
    vec_int_pop_back(&vec, &val);

    assert(vec_int_length(&vec) == 0);
    assert(vec_int_sizeof(&vec) == 4 * sizeof(int));

    int arr[5] = { 4, 3, 2, 1, 0 };
    vec = vec_int_from(arr, 5);
    sli = vec_int_slice(&vec, 1, 3);
    assert(vec_int_length(&sli) == 2);
    assert(sli.arr[0] == 3);
    assert(sli.arr[1] == 2);

    return 0;
}
