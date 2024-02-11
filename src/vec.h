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

#ifndef VEC
#define VEC

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

#define INIT_NVEC(name, type)                                                 \
typedef struct {                                                              \
    type *val;                                                                \
    size_t len;                                                               \
} nvec_##name;                                                                \
                                                                              \
typedef struct {                                                              \
    nvec_##name nvec;                                                         \
    size_t cnt;                                                               \
} nvec_##name##_iter;                                                         \
                                                                              \
nvec_##name                                                                   \
nvec_##name##_new()                                                           \
{                                                                             \
    nvec_##name nvec = { malloc(0), 0 };                                      \
    return nvec;                                                              \
}                                                                             \
                                                                              \
nvec_##name                                                                   \
nvec_##name##_from(const type *val, const size_t len)                         \
{                                                                             \
    nvec_##name nvec = { malloc(0), 0 };                                      \
    memcpy(nvec.val, val, sizeof(type) * len);                                \
    return nvec;                                                              \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_push_back(nvec_##name *nvec, const type val)                    \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
                                                                              \
    nvec->val = realloc(nvec->val, sizeof(type) * ++nvec->len);               \
    nvec->val[nvec->len - 1] = val;                                           \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_pop_back(nvec_##name *nvec, type *val)                          \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
                                                                              \
    nvec->val = realloc(nvec->val, sizeof(type) * --nvec->len);               \
    *val = nvec->val[nvec->len];                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_push_front(nvec_##name *nvec, const type val)                   \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
                                                                              \
    nvec->val = realloc(nvec->val, sizeof(type) * ++nvec->len);               \
    memmove(nvec->val + 1, nvec->val, sizeof(type) * (nvec->len - 1));        \
    nvec->val[0] = val;                                                       \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_pop_front(nvec_##name *nvec, type *val)                         \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
                                                                              \
    *val = nvec->val[0];                                                      \
    memmove(nvec->val, nvec->val + 1, sizeof(type) * nvec->len);              \
    nvec->val = realloc(nvec->val, sizeof(type) * --nvec->len);               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_insert(nvec_##name *nvec, const type val, const size_t at)      \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
    if (nvec->len <= at)                                                      \
        return -1;                                                            \
                                                                              \
    nvec->val = realloc(nvec->val, sizeof(type) * ++nvec->len);               \
    memmove(nvec->val + at + 1,                                               \
            nvec->val + at,                                                   \
            sizeof(type) * (nvec->len - at));                                 \
    nvec->val[at] = val;                                                      \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_rmvnth(nvec_##name *nvec, const size_t at, type *val)           \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
    if (nvec->len <= at)                                                      \
        return -1;                                                            \
                                                                              \
    *val = nvec->val[at];                                                     \
    memmove(nvec->val + at,                                                   \
            nvec->val + at + 1,                                               \
            sizeof(type) * (nvec->len - at));                                 \
    nvec->val = realloc(nvec->val, sizeof(type) * --nvec->len);               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_getnth(nvec_##name *nvec, const size_t at, type *val)           \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
    if (nvec->len <= at)                                                      \
        return -1;                                                            \
                                                                              \
    *val = nvec->val[at];                                                     \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_setnth(nvec_##name *nvec, const size_t at, const type val)      \
{                                                                             \
    if (nvec->val == NULL)                                                    \
        return -1;                                                            \
    if (nvec->len <= at)                                                      \
        return -1;                                                            \
                                                                              \
    nvec->val[at] = val;                                                      \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_append(nvec_##name *l_nvec, const nvec_##name *r_nvec)          \
{                                                                             \
    if (l_nvec->val == NULL || r_nvec->val == NULL)                           \
        return -1;                                                            \
                                                                              \
    if (r_nvec->len == 0)                                                     \
        return 0;                                                             \
    if (l_nvec->len == 0) {                                                   \
        memcpy(l_nvec, r_nvec, sizeof(type));                                 \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    l_nvec->val                                                               \
        = realloc(l_nvec->val, sizeof(type) * (l_nvec->len + r_nvec->len));   \
    memcpy(l_nvec->val + l_nvec->len,                                         \
           r_nvec->val,                                                       \
           sizeof(type) * r_nvec->len);                                       \
    l_nvec->len += r_nvec->len;                                               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_shrink(nvec_##name *nvec, const size_t len)                     \
{                                                                             \
    if (len > nvec->len)                                                      \
        return -1;                                                            \
    if (len == nvec->len)                                                     \
        return 0;                                                             \
    if ((nvec->val = realloc(nvec->val, len)) == NULL)                        \
        return -1;                                                            \
    nvec->len = len;                                                          \
    return 0;                                                                 \
}                                                                             \
                                                                              \
size_t                                                                        \
nvec_##name##_length(nvec_##name nvec)                                        \
{                                                                             \
    return nvec.len;                                                          \
}                                                                             \
                                                                              \
void                                                                          \
nvec_##name##_free(nvec_##name nvec)                                          \
{                                                                             \
    FREE(nvec.val);                                                           \
}                                                                             \
                                                                              \
nvec_##name##_iter                                                            \
nvec_##name##_iter_new(nvec_##name nvec)                                      \
{                                                                             \
    nvec_##name##_iter iter = { nvec, 0 };                                    \
    return iter;                                                              \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_iter_next(nvec_##name##_iter *iter, type *val)                  \
{                                                                             \
    *val = iter->nvec.val[iter->cnt++];                                       \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_iter_map(nvec_##name##_iter *iter,                              \
                      type (*fn)(type item), nvec_##name *vec)                \
{                                                                             \
    vec->val = malloc(sizeof(type) * iter->nvec.len);                         \
    vec->len = iter->nvec.len;                                                \
                                                                              \
    for (size_t i = 0; i < iter->nvec.len; i++)                               \
        vec->val[i] = (*fn)(iter->nvec.val[i]);                               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
nvec_##name##_iter_for_each(nvec_##name##_iter *iter, type (*fn)(type item))  \
{                                                                             \
    for (size_t i = 0; i < iter->nvec.len; i++)                               \
        iter->nvec.val[i] = (*fn)(iter->nvec.val[i]);                         \
    return 0;                                                                 \
}

#define INIT_LEN 4
#define INIT_VEC(name, type)                                                  \
typedef struct {                                                              \
    type *val;                                                                \
    size_t len, cap;                                                          \
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
    vec_##name vec_##name = { malloc(0), 0, 0 };                              \
    return vec_##name;                                                        \
}                                                                             \
                                                                              \
static int                                                                    \
vec_##name##_try_extend(vec_##name *vec)                                      \
{                                                                             \
    if (vec->len < vec->cap)                                                  \
        return 0;                                                             \
    vec->cap += vec->cap ? vec->cap / 2 : INIT_LEN;                           \
    vec->val = realloc(vec->val, sizeof(type) * vec->cap);                    \
    return vec->val ? 0 : -1;                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
vec_##name##_try_shrink(vec_##name *vec)                                      \
{                                                                             \
    if (vec->len > vec->cap / 2 || vec->len <= INIT_LEN)                      \
        return 0;                                                             \
    vec->cap -= vec->cap / 3;                                                 \
    vec->val = realloc(vec->val, sizeof(type) * vec->cap);                    \
    return vec->val ? 0 : -1;                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(vec_##name *vec, type val)                             \
{                                                                             \
    if (vec_##name##_try_extend(vec))                                         \
        return -1;                                                            \
    vec->val[vec->len++] = val;                                               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_back(vec_##name *vec, type *val)                             \
{                                                                             \
    *val = vec->val[--vec->len];                                              \
    if (vec_##name##_try_shrink(vec))                                         \
        return -1;                                                            \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_front(vec_##name *vec, type val)                            \
{                                                                             \
    if (vec_##name##_try_extend(vec))                                         \
        return -1;                                                            \
    memmove(vec->val + 1,                                                     \
            vec->val,                                                         \
            sizeof(type) * vec->len++);                                       \
    vec->val[0] = val;                                                        \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_front(vec_##name *vec, type *val)                            \
{                                                                             \
    *val = vec->val[0];                                                       \
    memmove(vec->val,                                                         \
            vec->val + 1,                                                     \
            sizeof(type) * --vec->len);                                       \
    if (vec_##name##_try_shrink(vec))                                         \
        return -1;                                                            \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_insert(vec_##name *vec, type val, const size_t at)               \
{                                                                             \
    if (at >= vec->len)                                                       \
        return -1;                                                            \
    if (vec_##name##_try_extend(vec))                                         \
        return -1;                                                            \
    memmove(vec->val + at + 1,                                                \
            vec->val + at,                                                    \
            sizeof(type) * (vec->len++ - at));                                \
    vec->val[at] = val;                                                       \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_rmvnth(vec_##name *vec, const size_t at, type *val)              \
{                                                                             \
    if (at == 0)                                                              \
        return vec_##name##_pop_front(vec, val);                              \
    if (at == vec->len - 1)                                                   \
        return vec_##name##_pop_back(vec, val);                               \
    *val = vec->val[at];                                                      \
    memmove(vec->val + at,                                                    \
            vec->val + at + 1,                                                \
            sizeof(type) * (vec->len - at));                                  \
    if (vec_##name##_try_shrink(vec))                                         \
        return -1;                                                            \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(vec_##name *vec, const size_t at, type *val)              \
{                                                                             \
    if (at >= vec->len)                                                       \
        return -1;                                                            \
    *val = vec->val[at];                                                      \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_setnth(vec_##name *vec, const size_t at, type val)               \
{                                                                             \
    if (at >= vec->len)                                                       \
        return -1;                                                            \
    vec->val[at] = val;                                                       \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_append(vec_##name *l_vec, const vec_##name *r_vec)               \
{                                                                             \
    if (l_vec->val == NULL || r_vec->val == NULL)                             \
        return -1;                                                            \
    for (size_t i = 0; i < r_vec->len; i++)                                   \
        if (vec_##name##_push_back(l_vec, r_vec->val[i]))                     \
            return -1;                                                        \
    return 0;                                                                 \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_length(const vec_##name vec)                                     \
{                                                                             \
    return vec.len;                                                           \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_sizeof(const vec_##name vec)                                     \
{                                                                             \
    return vec.cap * sizeof(type);                                            \
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
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_iter_map(vec_##name##_iter *iter,                                \
                      type (*fn)(type item), vec_##name *vec)                 \
{                                                                             \
    vec->val = malloc(sizeof(type) * iter->vec.len);                          \
    vec->len = iter->vec.len;                                                 \
                                                                              \
    for (size_t i = 0; i < iter->vec.len; i++)                                \
        vec->val[i] = (*fn)(iter->vec.val[i]);                                \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_iter_for_each(vec_##name##_iter *iter, type (*fn)(type item))    \
{                                                                             \
    for (size_t i = 0; i < iter->vec.len; i++)                                \
        iter->vec.val[i] = (*fn)(iter->vec.val[i]);                           \
    return 0;                                                                 \
}                                                                             

#endif
