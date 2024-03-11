#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAP 4

#define INIT_VEC(name, type)                                                  \
                                                                              \
typedef struct {                                                              \
    type *arr;                                                                \
    size_t cap, len;                                                          \
} vec_##name;                                                                 \
                                                                              \
static int                                                                    \
update_capacity(vec_##name *vec, size_t len)                                  \
{                                                                             \
    if (vec->arr == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    if (vec->cap < len) {                                                     \
        while (vec->cap < len)                                                \
            vec->cap += vec->cap ? vec->cap / 2 : INIT_CAP;                   \
    } else if (len < vec->cap / 2) {                                          \
        while (len < vec->cap - vec->cap / 3 && vec->cap > INIT_CAP)          \
            vec->cap -= (vec->cap > INIT_CAP) ? vec->cap / 3 : 0;             \
    } else {                                                                  \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    vec->arr = realloc(vec->arr, sizeof(type) * vec->cap);                    \
                                                                              \
    return vec->arr ? 0 : -1;                                                 \
}                                                                             \
                                                                              \
vec_##name                                                                    \
vec_##name##_new()                                                            \
{                                                                             \
    vec_##name vec = { malloc(0), 0, 0 };                                     \
    return vec;                                                               \
}                                                                             \
                                                                              \
vec_##name                                                                    \
vec_##name##_copy(const vec_##name old)                                       \
{                                                                             \
    vec_##name cpy = { malloc(sizeof(type) * old.cap), old.cap, old.len };    \
    memcpy(cpy.arr, old.arr, sizeof(type) * old.cap);                         \
                                                                              \
    return cpy;                                                               \
}                                                                             \
                                                                              \
vec_##name                                                                    \
vec_##name##_from_arr(type *arr, size_t len)                                  \
{                                                                             \
    vec_##name vec = { malloc(0), 0, len };                                   \
    if (update_capacity(&vec, vec.len))                                       \
        return vec_##name##_new();                                            \
                                                                              \
    memcpy(vec.arr, arr, sizeof(type) * vec.len);                             \
                                                                              \
    return vec;                                                               \
}                                                                             \
                                                                              \
vec_##name                                                                    \
vec_##name##_slice(const vec_##name *origin,                                  \
                   const size_t head, const size_t tail)                      \
{                                                                             \
    vec_##name sli;                                                           \
    if (head >= tail || origin->arr == NULL)                                  \
        return vec_##name##_new();                                            \
                                                                              \
    sli.arr = malloc(0);                                                      \
    sli.len = tail - head;                                                    \
    if (update_capacity(&sli, sli.len))                                       \
        return vec_##name##_new();                                            \
                                                                              \
    memcpy(sli.arr, origin->arr + head, sizeof(type) * sli.len);              \
                                                                              \
    return sli;                                                               \
}                                                                             \
                                                                              \
void                                                                          \
vec_##name##_free(vec_##name *vec)                                            \
{                                                                             \
    free(vec->arr);                                                           \
    vec->arr = NULL;                                                          \
    vec->cap = vec->len = 0;                                                  \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(vec_##name *vec, const type val)                       \
{                                                                             \
    if (update_capacity(vec, vec->len + 1))                                   \
        return -1;                                                            \
                                                                              \
    vec->arr[vec->len] = val;                                                 \
    vec->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_front(vec_##name *vec, const type val)                      \
{                                                                             \
    if (update_capacity(vec, vec->len + 1))                                   \
        return -1;                                                            \
                                                                              \
    memmove(vec->arr + 1, vec->arr, sizeof(type) * vec->len);                 \
    vec->arr[0] = val;                                                        \
    vec->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_back(vec_##name *vec, type *val)                             \
{                                                                             \
    *val = vec->arr[vec->len - 1];                                            \
                                                                              \
    if (update_capacity(vec, vec->len - 1))                                   \
        return -1;                                                            \
                                                                              \
    vec->len--;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_front(vec_##name *vec, type *val)                            \
{                                                                             \
    *val = vec->arr[0];                                                       \
    memmove(vec->arr, vec->arr + 1, sizeof(type) * (vec->len - 1));           \
                                                                              \
    if (update_capacity(vec, vec->len - 1))                                   \
        return -1;                                                            \
                                                                              \
    vec->len--;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_insert(vec_##name *vec, const type val, const size_t at)         \
{                                                                             \
    if (update_capacity(vec, vec->len + 1))                                   \
        return -1;                                                            \
                                                                              \
    memmove(vec->arr + at + 1, vec->arr + at, sizeof(type) * (vec->len - at));\
    vec->arr[at] = val;                                                       \
    vec->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_search(vec_##name *vec, const type target)                       \
{                                                                             \
    size_t i;                                                                 \
    for (i = 0; i < vec->len; i++)                                            \
        if (memcmp(&target, &vec->arr[i], sizeof(type)) == 0)                 \
            break;                                                            \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_remove(vec_##name *vec, const type target)                       \
{                                                                             \
    size_t i = vec_##name##_search(vec, target);                              \
    if (i >= vec->len)                                                        \
        return i;                                                             \
                                                                              \
    memmove(vec->arr + i, vec->arr + i + 1, sizeof(type) * (vec->len - i));   \
    if (update_capacity(vec, vec->len - 1))                                   \
        return -1;                                                            \
    vec->len--;                                                               \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(const vec_##name *vec, type *val, const size_t at)        \
{                                                                             \
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)                  \
        return -1;                                                            \
                                                                              \
    *val = vec->arr[at];                                                      \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_setnth(const vec_##name *vec, const type val, const size_t at)   \
{                                                                             \
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)                  \
        return -1;                                                            \
                                                                              \
    vec->arr[at] = val;                                                       \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_rmvnth(vec_##name *vec, type *val, const size_t at)              \
{                                                                             \
    if (vec_##name##_getnth(vec, val, at))                                    \
        return -1;                                                            \
                                                                              \
    memmove(vec->arr + at, vec->arr + 1, sizeof(type) * (vec->len - at));     \
    if (update_capacity(vec, vec->len - 1))                                   \
        return -1;                                                            \
    vec->len--;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_nthptr(vec_##name *vec, const size_t at)                         \
{                                                                             \
    if (vec->arr == NULL || vec->len == 0 || vec->len <= at)                  \
        return NULL;                                                          \
                                                                              \
    return vec->arr + at;                                                     \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_first(vec_##name *vec)                                           \
{                                                                             \
    return vec_##name##_nthptr(vec, 0);                                       \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_last(vec_##name *vec)                                            \
{                                                                             \
    return vec_##name##_nthptr(vec, vec->len - 1);                            \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_resize(vec_##name *vec, const size_t len)                        \
{                                                                             \
    if (update_capacity(vec, len))                                            \
        return -1;                                                            \
                                                                              \
    vec->len = (len < vec->len) ? len : vec->len;                             \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_length(const vec_##name *vec)                                    \
{                                                                             \
    return vec->len;                                                          \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_sizeof(const vec_##name *vec)                                    \
{                                                                             \
    return vec->cap * sizeof(type);                                           \
}                                                                             \
                                                                              \
struct _vec_##name { /* to enforce semicolon */ }

#endif
