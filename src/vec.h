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

#include <stddef.h>

typedef struct {
    int *val;
    size_t len;
} vec;

typedef struct {
    vec vec;
    size_t cnt;
} vec_iter;

vec vec_new();
vec vec_from(const int *, const size_t);
int vec_push_back(vec *, const int);
int vec_pop_back(vec *, int *);
int vec_push_front(vec *, const int);
int vec_pop_front(vec *, int *);
int vec_insert(vec *, const int, const size_t);
int vec_rmvnth(vec *, const size_t, int *);
int vec_getnth(vec *, const size_t, int *);
int vec_setnth(vec *, const size_t, const int);
int vec_append(vec *, const vec *);
void vec_free(vec);

vec_iter vec_iter_new(vec);
int vec_iter_next(vec_iter *, int *);
int vec_iter_foreach(vec_iter *, int (*)(int));
int vec_iter_map(vec_iter *, int (*)(int), vec *);
