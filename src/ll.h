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

struct sll_node {
    int data;
    struct sll_node *next;
};

typedef struct {
    struct sll_node *head;
    struct sll_node *tail;
    size_t len;
} sll;

typedef struct {
    sll sll;
    struct sll_node *cur;
} sll_iter;

struct dll_node {
    int data;
    struct dll_node *next;
    struct dll_node *prev;
};

typedef struct {
    struct dll_node *head;
    struct dll_node *tail;
    size_t len;
} dll;

typedef struct {
    dll dll;
    struct dll_node *cur;
} dll_iter;

sll sll_new();
int sll_push_back(sll *, const int);
int sll_pop_back(sll *, int *);
int sll_insert(sll *, const int, const size_t);
int sll_remove(sll *, const int);
int sll_rmvnth(sll *, const size_t, int *);
int sll_getnth(sll *, const size_t, int *);
int sll_setnth(sll *, const size_t, const int);
int sll_search(sll *, const int, size_t *);
int sll_append(sll *, const sll *);
void sll_free(sll);

dll dll_new();
int dll_push_back(dll *, const int);
int dll_pop_back(dll *, int *);
int dll_push_front(dll *, const int);
int dll_pop_front(dll *, int *);
int dll_insert(dll *, const int, const size_t);
int dll_remove(dll *, const int);
int dll_rmvnth(dll *, const size_t, int *);
int dll_getnth(dll *, const size_t, int *);
int dll_setnth(dll *, const size_t, const int);
int dll_search_from_front(dll *, const int, size_t *);
int dll_search_from_back(dll *, const int, size_t *);
int dll_append(dll *, const dll *);
void dll_free(dll);

sll_iter sll_iter_new(sll);
int sll_iter_next(sll_iter *, int *);
int sll_iter_for_each(sll_iter *, int (*)(int));
int sll_iter_map(sll_iter *, int (*)(int), sll *);

dll_iter dll_iter_new(dll);
int dll_iter_next(dll_iter *, int *);
int dll_iter_for_each(dll_iter *, int (*)(int));
int dll_iter_map(dll_iter *, int (*)(int), dll *);
