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
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <string.h>

#define INIT_VEC_TYPE(name, type)                                              \
struct vec_##name {                                                            \
        type *arr;                                                             \
        size_t cap, len;                                                       \
};                                                                             \
                                                                               \
struct vec_##name##_iter {                                                     \
        struct vec_##name *vec;                                                \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct vec_##name vec_##name##_new(void);                                      \
struct vec_##name vec_##name##_from(const type *, const size_t);               \
struct vec_##name vec_##name##_copy(const struct vec_##name *);                \
int vec_##name##_push(struct vec_##name *, const type);                        \
int vec_##name##_pop(struct vec_##name *, type *);                             \
int vec_##name##_get(struct vec_##name *, type *, const size_t);               \
int vec_##name##_set(struct vec_##name *, const type, const size_t);           \
int vec_##name##_append(struct vec_##name *, const type *, const size_t);      \
int vec_##name##_insert(struct vec_##name *, const type, const size_t);        \
int vec_##name##_remove(struct vec_##name *, type *, const size_t);            \
int vec_##name##_shrink(struct vec_##name *, const size_t);                    \
size_t vec_##name##_len(struct vec_##name *);                                  \
void vec_##name##_free(struct vec_##name *);                                   \
                                                                               \
struct vec_##name##_iter vec_##name##_iter(struct vec_##name *);               \
int vec_##name##_next(struct vec_##name##_iter *, type *);                     \
                                                                               \
extern int _vec_##name##_type

#define INIT_VEC_FUNC(name, type, malloc, realloc, free)                       \
static int                                                                     \
vec_##name##_extend(struct vec_##name *vec, const size_t len)                  \
{                                                                              \
        if (vec->len < vec->cap)                                               \
                return 0;                                                      \
        if (vec->cap == 0)                                                     \
                vec->cap = 1;                                                  \
        for (; vec->cap < len; vec->cap <<= 1)                                 \
                ;                                                              \
        if ((vec->arr = realloc(vec->arr, vec->cap * sizeof(type))) == NULL)   \
                return -1;                                                     \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
struct vec_##name                                                              \
vec_##name##_new(void)                                                         \
{                                                                              \
        struct vec_##name vec;                                                 \
                                                                               \
        vec.arr = malloc(0);                                                   \
        vec.cap = vec.len = 0;                                                 \
                                                                               \
        return vec;                                                            \
}                                                                              \
                                                                               \
struct vec_##name                                                              \
vec_##name##_from(const type *arr, const size_t len)                           \
{                                                                              \
        struct vec_##name vec;                                                 \
                                                                               \
        for (vec.cap = 1; vec.cap < len; vec.cap <<= 1)                        \
                ;                                                              \
        if ((vec.arr = malloc(vec.cap * sizeof(type))) == NULL)                \
                return vec_##name##_new();                                     \
                                                                               \
        memcpy(vec.arr, arr, len * sizeof(type));                              \
        vec.len = len;                                                         \
                                                                               \
        return vec;                                                            \
}                                                                              \
                                                                               \
struct vec_##name                                                              \
vec_##name##_copy(const struct vec_##name *vec)                                \
{                                                                              \
        struct vec_##name cpy;                                                 \
                                                                               \
        if ((cpy.arr = malloc(vec->cap * sizeof(type))) == NULL)               \
                return vec_##name##_new();                                     \
                                                                               \
        memcpy(cpy.arr, vec->arr, vec->cap * sizeof(type));                    \
        cpy.cap = vec->cap;                                                    \
        cpy.len = vec->len;                                                    \
                                                                               \
        return cpy;                                                            \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_push(struct vec_##name *vec, const type val)                      \
{                                                                              \
        if (vec->arr == NULL)                                                  \
                return -1;                                                     \
        if (vec_##name##_extend(vec, vec->len + 1))                            \
                return -1;                                                     \
                                                                               \
        vec->arr[vec->len++] = val;                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_pop(struct vec_##name *vec, type *val)                            \
{                                                                              \
        if (vec->arr == NULL || vec->cap == 0 || vec->len == 0)                \
                return -1;                                                     \
                                                                               \
        *val = vec->arr[--vec->len];                                           \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_get(struct vec_##name *vec, type *val, const size_t idx)          \
{                                                                              \
        if (vec->arr == NULL || vec->cap == 0 || vec->len == 0)                \
                return -1;                                                     \
        if (vec->len <= idx)                                                   \
                return -1;                                                     \
                                                                               \
        *val = vec->arr[idx];                                                  \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_set(struct vec_##name *vec, const type val, const size_t idx)     \
{                                                                              \
        if (vec->arr == NULL || vec->cap == 0 || vec->len == 0)                \
                return -1;                                                     \
        if (vec->len <= idx)                                                   \
                return -1;                                                     \
                                                                               \
        vec->arr[idx] = val;                                                   \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_append(struct vec_##name *vec, const type *arr, const size_t len) \
{                                                                              \
        if (arr == NULL || len == 0)                                           \
                return 0;                                                      \
        if (vec->arr == NULL)                                                  \
                return -1;                                                     \
        if (vec_##name##_extend(vec, vec->len + len))                          \
                return -1;                                                     \
                                                                               \
        memcpy(vec->arr + vec->len, arr, len * sizeof(type));                  \
        vec->len += len;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_insert(struct vec_##name *vec, const type val, const size_t idx)  \
{                                                                              \
        if (vec->arr == NULL)                                                  \
                return -1;                                                     \
        if (vec->len < idx)                                                    \
                return -1;                                                     \
        if (vec_##name##_extend(vec, vec->len + 1))                            \
                return -1;                                                     \
                                                                               \
        memmove(vec->arr + idx + 1,                                            \
                vec->arr + idx,                                                \
                (vec->len - idx) * sizeof(type));                              \
        vec->arr[idx] = val;                                                   \
        vec->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_remove(struct vec_##name *vec, type *val, const size_t idx)       \
{                                                                              \
        if (vec->arr == NULL)                                                  \
                return -1;                                                     \
        if (vec->len <= idx)                                                   \
                return -1;                                                     \
                                                                               \
        *val = vec->arr[idx];                                                  \
        memmove(vec->arr + idx,                                                \
                vec->arr + idx + 1,                                            \
                (vec->len - idx) * sizeof(type));                              \
        vec->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_shrink(struct vec_##name *vec, const size_t len)                  \
{                                                                              \
        if (vec->arr == NULL)                                                  \
                return -1;                                                     \
        if (vec->len <= len)                                                   \
                return 0;                                                      \
        for (vec->cap = 1; vec->cap < len; vec->cap <<= 1)                     \
                ;                                                              \
        if ((vec->arr = realloc(vec->arr, vec->cap * sizeof(type))) == NULL)   \
                return -1;                                                     \
                                                                               \
        vec->len = len;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
vec_##name##_len(struct vec_##name *vec)                                       \
{                                                                              \
        return vec->len;                                                       \
}                                                                              \
                                                                               \
void                                                                           \
vec_##name##_free(struct vec_##name *vec)                                      \
{                                                                              \
        free(vec->arr);                                                        \
        vec->arr = NULL;                                                       \
        vec->cap = vec->len = 0;                                               \
}                                                                              \
                                                                               \
struct vec_##name##_iter                                                       \
vec_##name##_iter(struct vec_##name *vec)                                      \
{                                                                              \
        struct vec_##name##_iter iter;                                         \
                                                                               \
        iter.vec = vec;                                                        \
        iter.idx = 0;                                                          \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
vec_##name##_next(struct vec_##name##_iter *iter, type *val)                   \
{                                                                              \
        if (iter->idx == iter->vec->len)                                       \
                return -1;                                                     \
                                                                               \
        *val = iter->vec->arr[iter->idx++];                                    \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
extern int _vec_##name##_func

#define INIT_VEC_BOTH(name, type, malloc, realloc, free)                       \
INIT_VEC_TYPE(name, type);                                                     \
INIT_VEC_FUNC(name, type, malloc, realloc, free)

#define FOR_EACH_VEC(name, elem, iter) while (!vec_##name##_next(&iter, &elem))

#endif
