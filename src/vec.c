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

#include "vec.h"
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
free(ptr);          \
ptr = NULL;

vec
vec_new()
{
    vec vec = { malloc(0), 0 };
    return vec;
}

vec
vec_from(const int *val, const size_t len)
{
    vec vec = { malloc(0), 0 };
    memcpy(vec.val, val, sizeof(int) * len);
    return vec;
}

int
vec_push_back(vec *vec, const int val)
{
    if (vec->val == NULL)
        return -1;

    vec->val = realloc(vec->val, sizeof(int) * ++vec->len);
    vec->val[vec->len - 1] = val;

    return 0;
}

int
vec_pop_back(vec *vec, int *val)
{
    if (vec->val == NULL)
        return -1;

    vec->val = realloc(vec->val, sizeof(int) * --vec->len);
    *val = vec->val[vec->len];

    return 0;
}

int
vec_push_front(vec *vec, const int val)
{
    if (vec->val == NULL)
        return -1;

    vec->val = realloc(vec->val, sizeof(int) * ++vec->len);
    memmove(vec->val + 1, vec->val, sizeof(int) * (vec->len - 1));
    vec->val[0] = val;

    return 0;
}

int
vec_pop_front(vec *vec, int *val)
{
    if (vec->val == NULL)
        return -1;

    *val = vec->val[0];
    memmove(vec->val, vec->val + 1, sizeof(int) * vec->len);
    vec->val = realloc(vec->val, sizeof(int) * --vec->len);

    return 0;
}

int
vec_insert(vec *vec, const int val, const size_t at)
{
    if (vec->val == NULL)
        return -1;
    if (vec->len <= at)
        return -1;
    
    vec->val = realloc(vec->val, sizeof(int) * ++vec->len);
    memmove(vec->val + at + 1, vec->val + at, sizeof(int) * (vec->len - at));
    vec->val[at] = val;

    return 0;
}

int
vec_rmvnth(vec *vec, const size_t at, int *val)
{
    if (vec->val == NULL)
        return -1;
    if (vec->len <= at)
        return -1;
    
    *val = vec->val[at];
    memmove(vec->val + at, vec->val + at + 1, sizeof(int) * (vec->len - at));
    vec->val = realloc(vec->val, sizeof(int) * --vec->len);

    return 0;
}

int
vec_getnth(vec *vec, const size_t at, int *val)
{
    if (vec->val == NULL)
        return -1;
    if (vec->len <= at)
        return -1;
    
    *val = vec->val[at];

    return 0;
}

int
vec_setnth(vec *vec, const size_t at, const int val)
{
    if (vec->val == NULL)
        return -1;
    if (vec->len <= at)
        return -1;
    
    vec->val[at] = val;

    return 0;
}

int
vec_append(vec *l_vec, const vec *r_vec)
{
    if (l_vec->val == NULL || r_vec->val == NULL)
        return -1;
    
    if (r_vec->len == 0)
        return 0;
    if (l_vec->len == 0) {
        memcpy(l_vec, r_vec, sizeof(vec));
        return 0;
    }

    l_vec->val = realloc(l_vec->val, sizeof(int) * (l_vec->len + r_vec->len));
    memcpy(l_vec->val + l_vec->len, r_vec->val, sizeof(int) * r_vec->len);
    l_vec->len += r_vec->len;

    return 0;
}

void
vec_free(vec vec)
{
    FREE(vec.val);
}

vec_iter
vec_iter_new(vec vec)
{
    vec_iter iter = { vec, 0 };
    return iter;
}

int
vec_iter_next(vec_iter *iter, int *val)
{
    *val = iter->vec.val[iter->cnt++];

    return 0;
}

int
vec_iter_map(vec_iter *iter, int (*fn)(int item), vec *new)
{
    new->val = malloc(sizeof(int) * iter->vec.len);
    new->len = iter->vec.len;

    for (size_t i = 0; i < iter->vec.len; i++)
        new->val[i] = (*fn)(iter->vec.val[i]);

    return 0;
}

int
vec_iter_for_each(vec_iter *iter, int (*fn)(int item))
{
    for (size_t i = 0; i < iter->vec.len; i++)
        iter->vec.val[i] = (*fn)(iter->vec.val[i]);

    return 0;
}
