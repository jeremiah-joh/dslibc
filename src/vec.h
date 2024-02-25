typedef int type;

#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAP 4

#define INIT_VEC(name, type)

typedef struct {
    type *arr;
    size_t cap, len;
} vec;

static int
update_capacity(vec *vec, size_t len)
{
    if (vec->arr == NULL)
        return -1;

    if (vec->cap < len) {
        while (vec->cap < len)
            vec->cap += vec->cap ? vec->cap / 2 : INIT_CAP;
    } else if (len < vec->cap / 2) {
        while (len < vec->cap - vec->cap / 3 && vec->cap > INIT_CAP)
            vec->cap -= (vec->cap > INIT_CAP) ? vec->cap / 3 : 0;
    } else {
        return 0;
    }

    vec->arr = realloc(vec->arr, sizeof(type) * vec->cap);

    return vec->arr ? 0 : -1;
}

static vec
vec_new()
{
    vec vec = { malloc(0), 0, 0 };
    return vec;
}

static vec
vec_from(type *arr, size_t len)
{
    vec vec = { malloc(0), 0, len };
    if (update_capacity(&vec, vec.len))
        return vec_new();

    memcpy(vec.arr, arr, sizeof(type) * vec.len);

    return vec;
}

static vec
vec_slice(const vec *origin, const size_t head, const size_t tail)
{
    vec sli;
    if (head >= tail || origin->arr == NULL)
        return vec_new();

    sli.arr = malloc(0);
    sli.len = tail - head;
    if (update_capacity(&sli, sli.len))
        return vec_new();

    memcpy(sli.arr, origin->arr + head, sizeof(type) * sli.len);

    return sli;
}

static void
vec_free(vec *vec)
{
    free(vec->arr);
    vec->arr = NULL;
    vec->cap = vec->len = 0;
}

static int
vec_push_back(vec *vec, const type val)
{
    if (update_capacity(vec, vec->len + 1))
        return -1;

    vec->arr[vec->len] = val;
    vec->len++;

    return 0;
}

static int
vec_push_front(vec *vec, const type val)
{
    if (update_capacity(vec, vec->len + 1))
        return -1;

    memmove(vec->arr + 1, vec->arr, sizeof(type) * vec->len);
    vec->arr[0] = val;
    vec->len++;

    return 0;
}

static int
vec_pop_back(vec *vec, type *val)
{
    *val = vec->arr[vec->len - 1];

    if (update_capacity(vec, vec->len - 1))
        return -1;

    vec->len--;

    return 0;
}

static int
vec_pop_front(vec *vec, type *val)
{
    *val = vec->arr[0];
    memmove(vec->arr, vec->arr + 1, sizeof(type) * (vec->len - 1));

    if (update_capacity(vec, vec->len - 1))
        return -1;

    vec->len--;

    return 0;
}

static int
vec_insert(vec *vec, const type val, const size_t at)
{
    if (update_capacity(vec, vec->len + 1))
        return -1;

    memmove(vec->arr + at + 1, vec->arr + at, sizeof(type) * (vec->len - at));
    vec->arr[at] = val;
    vec->len++;

    return 0;
}

static size_t
vec_search(vec *vec, const type target)
{
    size_t i;
    for (i = 0; i < vec->len; i++)
        if (memcmp(&target, &vec->arr[i], sizeof(type)) == 0)
            break;

    return i;
}

static size_t
vec_remove(vec *vec, const type target)
{
    size_t i = vec_search(vec, target);
    if (i >= vec->len)
        return i;

    memmove(vec->arr + i, vec->arr + i + 1, sizeof(type) * (vec->len - i));
    if (update_capacity(vec, vec->len - 1))
        return -1;
    vec->len--;

    return i;
}

static int
vec_getnth(const vec *vec, type *val, const size_t at)
{
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)
        return -1;

    *val = vec->arr[at];

    return 0;
}

static int
vec_setnth(const vec *vec, const type val, const size_t at)
{
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)
        return -1;

    vec->arr[at] = val;

    return 0;
}

static int
vec_rmvnth(vec *vec, type *val, const size_t at)
{
    if (vec_getnth(vec, val, at))
        return -1;

    memmove(vec->arr + at, vec->arr + 1, sizeof(type) * (vec->len - at));
    if (update_capacity(vec, vec->len - 1))
        return -1;
    vec->len--;

    return 0;
}

static type *
vec_nth(vec *vec, const size_t at)
{
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)
        return NULL;

    return vec->arr + at;
}

static type *
vec_front(vec *vec)
{
    return vec_nth(vec, 0);
}

static type *
vec_back(vec *vec)
{
    return vec_nth(vec, vec->len - 1);
}

static int
vec_resize(vec *vec, const size_t len)
{
    if (update_capacity(vec, len))
        return -1;

    vec->len = (len < vec->len) ? len : vec->len;

    return 0;
}

static size_t
vec_length(const vec *vec)
{
    return vec->len;
}

static size_t
vec_sizeof(const vec *vec)
{
    return vec->cap * sizeof(type);
}

#endif
