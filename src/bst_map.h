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

struct bst_map_node {
    int key;
    int val;

    struct bst_map_node *left;
    struct bst_map_node *right;
};

typedef struct {
    struct bst_map_node *root;
    size_t len;
} bst_map;

bst_map bst_map_new();
int bst_map_insert(bst_map *, const int, const int);
int bst_map_remove(bst_map *, const int, int *);
int bst_map_search(bst_map *, const int, int *);
void bst_map_free(bst_map);
