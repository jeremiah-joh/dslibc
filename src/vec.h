/*
 * Copyright (C) 2024 Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * This file is part of dslibc.
 *
 * dslibc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dslibc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

#define INIT_VEC(name, type)                                                  \
typedef struct {                                                              \
    type *val;                                                                \
    size_t len;                                                               \
} vec_##name;                                                                 \
                                                                              \
typedef struct {                                                              \
    vec_##name vec;                                                           \
    size_t cnt;                                                               \
} vec_##name##_iter;                                                          \
                                                                              \
vec_##name                                                                    \
vec_##name##_new()                                                            \
{                                                                             \
    vec_##name vec = { malloc(0), 0 };                                        \
    return vec;                                                               \
}                                                                             \
                                                                              \
vec_##name                                                                    \
vec_##name##_from(const type *val, const size_t len)                          \
{                                                                             \
    vec_##name vec = { malloc(0), 0 };                                        \
    memcpy(vec.val, val, sizeof(type) * len);                                 \
    return vec;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(vec_##name *vec, const type val)                       \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    vec->val = realloc(vec->val, sizeof(type) * ++vec->len);                  \
    vec->val[vec->len - 1] = val;                                             \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_back(vec_##name *vec, type *val)                             \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    vec->val = realloc(vec->val, sizeof(type) * --vec->len);                  \
    *val = vec->val[vec->len];                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_front(vec_##name *vec, const type val)                      \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    vec->val = realloc(vec->val, sizeof(type) * ++vec->len);                  \
    memmove(vec->val + 1, vec->val, sizeof(type) * (vec->len - 1));           \
    vec->val[0] = val;                                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_front(vec_##name *vec, type *val)                            \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    *val = vec->val[0];                                                       \
    memmove(vec->val, vec->val + 1, sizeof(type) * vec->len);                 \
    vec->val = realloc(vec->val, sizeof(type) * --vec->len);                  \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_insert(vec_##name *vec, const type val, const size_t at)         \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
    if (vec->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    vec->val = realloc(vec->val, sizeof(type) * ++vec->len);                  \
    memmove(vec->val + at + 1, vec->val + at, sizeof(type) * (vec->len - at));\
    vec->val[at] = val;                                                       \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_rmvnth(vec_##name *vec, const size_t at, type *val)              \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
    if (vec->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    *val = vec->val[at];                                                      \
    memmove(vec->val + at, vec->val + at + 1, sizeof(type) * (vec->len - at));\
    vec->val = realloc(vec->val, sizeof(type) * --vec->len);                  \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(vec_##name *vec, const size_t at, type *val)              \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
    if (vec->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    *val = vec->val[at];                                                      \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_setnth(vec_##name *vec, const size_t at, const type val)         \
{                                                                             \
    if (vec->val == NULL)                                                     \
        return -1;                                                            \
    if (vec->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    vec->val[at] = val;                                                       \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_append(vec_##name *l_vec, const vec_##name *r_vec)               \
{                                                                             \
    if (l_vec->val == NULL || r_vec->val == NULL)                             \
        return -1;                                                            \
                                                                              \
    if (r_vec->len == 0)                                                      \
        return 0;                                                             \
    if (l_vec->len == 0) {                                                    \
        memcpy(l_vec, r_vec, sizeof(vec_##name));                             \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    l_vec->val                                                                \
        = realloc(l_vec->val, sizeof(type) * (l_vec->len + r_vec->len));      \
    memcpy(l_vec->val + l_vec->len, r_vec->val, sizeof(type) * r_vec->len);   \
    l_vec->len += r_vec->len;                                                 \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
void                                                                          \
vec_##name##_free(vec_##name vec)                                             \
{                                                                             \
    FREE(vec.val);                                                            \
}                                                                             \
                                                                              \
vec_##name##_iter                                                             \
vec_##name##_iter_new(vec_##name vec)                                         \
{                                                                             \
    vec_##name##_iter iter = { vec, 0 };                                      \
    return iter;                                                              \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_iter_next(vec_##name##_iter *iter, type *val)                    \
{                                                                             \
    *val = iter->vec.val[iter->cnt++];                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_iter_map(vec_##name##_iter *iter,                                \
                      type (*fn)(type item), vec_##name *new)                 \
{                                                                             \
    new->val = malloc(sizeof(type) * iter->vec.len);                          \
    new->len = iter->vec.len;                                                 \
                                                                              \
    for (size_t i = 0; i < iter->vec.len; i++)                                \
        new->val[i] = (*fn)(iter->vec.val[i]);                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_iter_for_each(vec_##name##_iter *iter, type (*fn)(type item))    \
{                                                                             \
    for (size_t i = 0; i < iter->vec.len; i++)                                \
        iter->vec.val[i] = (*fn)(iter->vec.val[i]);                           \
                                                                              \
    return 0;                                                                 \
}                                                                             

#endif
