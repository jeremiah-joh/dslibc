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

#include "bst_map.h"
#include <stdlib.h>
#include <string.h>

bst_map
bst_map_new()
{
    bst_map map = { NULL, 0 };
    return map;
}

int
bst_map_insert(bst_map *map, const int key, const int val)
{
    int
    new_node(struct bst_node **node, const int key, const int val)
    {
        *node = malloc(sizeof(struct bst_node));
        (*node)->key = key;
        (*node)->val = val;
        (*node)->left = NULL;
        (*node)->right = NULL;
        map->len++;
    
        return *node ? 0 : -1;
    }

    if (map->root == NULL)
        return new_node(&map->root, key, val);

    struct bst_node *tmp = map->root;
    while (tmp != NULL) {
        int cmp = memcmp(&key, &tmp->key, sizeof(int));
        if (cmp < 0) {
            if (tmp->left == NULL)
                return new_node(&tmp->left, key, val);
            tmp = tmp->left;
        } else {
            if (tmp->right == NULL)
                return new_node(&tmp->right, key, val);
            tmp = tmp->right;
        }
    }

    return 0;
}

int
bst_map_remove(bst_map *map, const int key, int *val)
{
    struct bst_node *parent = NULL;
    struct bst_node *tmp = map->root;
    while (tmp != NULL) {
        int cmp = memcmp(&key, &tmp->key, sizeof(int));
        if (cmp < 0) {
            parent = tmp;
            tmp = tmp->left;
        } else if (cmp > 0) {
            parent = tmp;
            tmp = tmp->right;
        } else {
            *val = tmp->val;

            if (parent == NULL) {
                parent = tmp;
                free(parent);
                map->root = tmp->left ? tmp->left : tmp->right;
            } else {
                if (parent->left == tmp)
                    parent->left = tmp->left ? tmp->left : tmp->right;
                else
                    parent->right = tmp->left ? tmp->left : tmp->right;
                free(tmp);
            }

            map->len--;
            return 0;
        }
    }

    return -1;
}

int
bst_map_search(bst_map *map, const int key, int *val)
{
    struct bst_node *tmp = map->root;
    while (tmp != NULL) {
        int cmp = memcmp(&key, &tmp->key, sizeof(int));
        if (cmp < 0)
            tmp = tmp->left;
        else if (cmp > 0)
            tmp = tmp->right;
        else {
            *val = tmp->val;

            return 0;
        }
    }

    return -1;
}
