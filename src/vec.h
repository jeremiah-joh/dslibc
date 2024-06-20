/*
 * dslibc - collection of useful data structures written in ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VEC_TYPE(name, type)                                             \
struct vec_##name {                                                           \
        type *arr;                                                            \
        size_t cap, len;                                                      \
};                                                                            \
                                                                              \
struct vec_##name vec_##name##_new();                                         \
struct vec_##name vec_##name##_from(const type *, const size_t);              \
struct vec_##name vec_##name##_copy(const struct vec_##name);                 \
struct vec_##name vec_##name##_slice(const struct vec_##name,                 \
                                     const size_t, const size_t);             \
int vec_##name##_push_back(struct vec_##name *, const type);                  \
int vec_##name##_push_front(struct vec_##name *, const type);                 \
int vec_##name##_pop_back(struct vec_##name *, type *);                       \
int vec_##name##_pop_front(struct vec_##name *, type *);                      \
int vec_##name##_append(struct vec_##name *, const type *, const size_t);     \
int vec_##name##_insert(struct vec_##name *, const type, const size_t);       \
int vec_##name##_shrink(struct vec_##name *, const size_t);                   \
int vec_##name##_getnth(struct vec_##name *, type *, const size_t);           \
int vec_##name##_setnth(struct vec_##name *, const type, const size_t);       \
int vec_##name##_rmvnth(struct vec_##name *, type *, const size_t);           \
int vec_##name##_retain(struct vec_##name *, int (*)(type));                  \
type *vec_##name##_ptr(struct vec_##name *, const size_t);                    \
type *vec_##name##_head(struct vec_##name *);                                 \
type *vec_##name##_tail(struct vec_##name *);                                 \
void vec_##name##_foreach(struct vec_##name *, void (*)(type *));             \
void vec_##name##_free(struct vec_##name *) /* to enforce semicolon */

#define INIT_VEC_FUNC(name, type)                                             \
static size_t                                                                 \
vec_##name##_new_cap(const size_t len)                                        \
{                                                                             \
        size_t i;                                                             \
        for (i = 4; i < len; i <<= 1)                                         \
                ;                                                             \
                                                                              \
        return i * sizeof(type);                                              \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_new()                                                            \
{                                                                             \
        struct vec_##name vec = { malloc(0), 0, 0 };                          \
        return vec;                                                           \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_from(const type *arr, const size_t len)                          \
{                                                                             \
        size_t cap = vec_##name##_new_cap(len);                               \
        struct vec_##name vec = { malloc(cap), cap, len };                    \
                                                                              \
        memcpy(vec.arr, arr, sizeof(*arr) * len);                             \
                                                                              \
        return vec;                                                           \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_copy(const struct vec_##name vec)                                \
{                                                                             \
        struct vec_##name cpy = { malloc(vec.cap), vec.cap, vec.len };        \
        memcpy(cpy.arr, vec.arr, vec.cap);                                    \
                                                                              \
        return cpy;                                                           \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_slice(const struct vec_##name vec,                               \
                   const size_t head, const size_t tail)                      \
{                                                                             \
        struct vec_##name sli;                                                \
                                                                              \
        if (tail <= head)                                                     \
                return vec_##name##_new();                                    \
                                                                              \
        sli.cap = vec_##name##_new_cap(tail - head);                          \
        sli.arr = malloc(sli.cap);                                            \
        sli.len = tail - head;                                                \
                                                                              \
        memcpy(sli.arr, vec.arr + head, sizeof(type) * sli.len);              \
                                                                              \
        return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(struct vec_##name *vec, const type val)                \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
                                                                              \
        vec->cap = vec_##name##_new_cap(vec->len + 1);                        \
        if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
                return -1;                                                    \
                                                                              \
        vec->arr[vec->len] = val;                                             \
        vec->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_front(struct vec_##name *vec, const type val)               \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
                                                                              \
        vec->cap = vec_##name##_new_cap(vec->len + 1);                        \
        if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
                return -1;                                                    \
                                                                              \
        memmove(vec->arr + 1, vec->arr, sizeof(type) * vec->len);             \
        vec->arr[0] = val;                                                    \
        vec->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_back(struct vec_##name *vec, type *val)                      \
{                                                                             \
        if (vec->arr == NULL || vec->len == 0)                                \
                return -1;                                                    \
                                                                              \
        *val = vec->arr[vec->len - 1];                                        \
        vec->cap = vec_##name##_new_cap(vec->len - 1);                        \
        vec->len--;                                                           \
                                                                              \
        return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_front(struct vec_##name *vec, type *val)                     \
{                                                                             \
        if (vec->arr == NULL || vec->len == 0)                                \
                return -1;                                                    \
                                                                              \
        *val = vec->arr[0];                                                   \
        vec->cap = vec_##name##_new_cap(vec->len - 1);                        \
        memmove(vec->arr, vec->arr + 1, sizeof(type) * vec->len);             \
        vec->len--;                                                           \
                                                                              \
        return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_append(struct vec_##name *des,                                   \
                    const type *arr, const size_t len)                        \
{                                                                             \
        if (arr == NULL || len == 0)                                          \
                return 0;                                                     \
        if (des->arr == NULL || des->len == 0) {                              \
                *des = vec_##name##_from(arr, len);                           \
                return 0;                                                     \
        }                                                                     \
                                                                              \
        des->cap = vec_##name##_new_cap(des->len + len);                      \
        if ((des->arr = realloc(des->arr, des->cap)) == NULL)                 \
                return -1;                                                    \
                                                                              \
        memcpy(des->arr + des->len, arr, sizeof(*arr) * len);                 \
                                                                              \
        des->len += len;                                                      \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_insert(struct vec_##name *vec, const type val, const size_t idx) \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
        if (vec->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        vec->cap = vec_##name##_new_cap(vec->len + 1);                        \
        if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
                return -1;                                                    \
                                                                              \
        memmove(vec->arr + idx,                                               \
                vec->arr + idx + 1,                                           \
                sizeof(type) * (vec->len - idx));                             \
        vec->arr[idx] = val;                                                  \
                                                                              \
        vec->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_shrink(struct vec_##name *vec, const size_t len)                 \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
        if (vec->len < len)                                                   \
                return -1;                                                    \
        if (vec->len == len)                                                  \
                return 0;                                                     \
                                                                              \
        vec->len = len;                                                       \
        vec->cap = vec_##name##_new_cap(len);                                 \
                                                                              \
        return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(struct vec_##name *vec, type *val, const size_t idx)      \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
        if (vec->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        *val = vec->arr[idx];                                                 \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_setnth(struct vec_##name *vec, const type val, const size_t idx) \
{                                                                             \
        if (vec->arr == NULL)                                                 \
                return -1;                                                    \
        if (vec->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        vec->arr[idx] = val;                                                  \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_rmvnth(struct vec_##name *vec, type *val, const size_t idx)      \
{                                                                             \
        if (vec->arr == NULL || vec->len == 0)                                \
                return -1;                                                    \
        if (vec->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        *val = vec->arr[idx];                                                 \
        memmove(vec->arr + idx,                                               \
                vec->arr + idx + 1,                                           \
                sizeof(type) * (vec->len - idx));                             \
                                                                              \
        vec->cap = vec_##name##_new_cap(vec->len - 1);                        \
        if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
                return -1;                                                    \
                                                                              \
        vec->len--;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_retain(struct vec_##name *vec, int (*fn)(type))                  \
{                                                                             \
    size_t i, j;                                                          \
                                                                              \
    if (vec->arr == NULL || vec->len == 0)                                \
    	return 0;                                                     \
                                                                          \
    for (i = 0, j = 0; i < vec->len; i++) {                               \
    	if (!fn(vec->arr[i]))                                         \
    		continue;                                             \
    	vec->arr[j++] = vec->arr[i];                                  \
    }                                                                     \
                                                                              \
    vec->len = j;                                                         \
    vec->cap = vec_##name##_new_cap(j);                                   \
    return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_ptr(struct vec_##name *vec, const size_t idx)                    \
{                                                                             \
        return (idx < vec->len) ? &vec->arr[idx] : NULL;                      \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_head(struct vec_##name *vec)                                     \
{                                                                             \
        return vec->arr ? &vec->arr[0] : NULL;                                \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_tail(struct vec_##name *vec)                                     \
{                                                                             \
        return vec->arr ? &vec->arr[vec->len - 1] : NULL;                     \
}                                                                             \
                                                                              \
void                                                                          \
vec_##name##_foreach(struct vec_##name *vec, void (*fn)(type *))              \
{                                                                             \
    size_t i;                                                             \
                                                                              \
    for (i = 0; i < vec->len; i++)                                        \
    	fn(&vec->arr[i]);                                             \
}                                                                             \
                                                                              \
void                                                                          \
vec_##name##_free(struct vec_##name *vec)                                     \
{                                                                             \
        free(vec->arr);                                                       \
        vec->arr = NULL;                                                      \
        vec->cap = vec->len = 0;                                              \
}                                                                             \
                                                                              \
struct vec_##name##_semi { /* to enforce semicolon */ }

#define INIT_VEC(name, type)                                                  \
INIT_VEC_TYPE(name, type);                                                    \
INIT_VEC_FUNC(name, type)

#endif
