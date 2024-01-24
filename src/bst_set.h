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

struct bst_node {
    int key;

    struct bst_node *left;
    struct bst_node *right;
};

typedef struct {
    struct bst_node *root;
    size_t len;
} bst_set;

bst_set bst_set_new();
int bst_insert(bst_set *, const int);
int bst_remove(bst_set *, const int);
int bst_search(bst_set *, const int);
void bst_free(bst_set);
