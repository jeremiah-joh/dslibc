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

#include "bst_set.h"
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
free(ptr);          \
ptr = NULL;

bst_set
bst_set_new()
{
    bst_set set = { NULL, 0 };
    return set;
}

int
bst_set_insert(bst_set *set, const int key)
{
    int
    new_node(struct bst_node **node, const int key)
    {
        *node = malloc(sizeof(struct bst_node));
        (*node)->key = key;
        (*node)->left = NULL;
        (*node)->right = NULL;
        set->len++;

        return *node ? 0 : -1;
    }

    if (set->root == NULL) {
        return new_node(&set->root, key);
    }

    struct bst_node *tmp = set->root;
    while (tmp != NULL) {
        int cmp = memcmp(&key, &tmp->key, sizeof(int));
        if (cmp < 0) {
            if (tmp->left == NULL)
                return new_node(&tmp->left, key);
            tmp = tmp->left;
        } else if (cmp > 0) {
            if (tmp->right == NULL)
                return new_node(&tmp->right, key);
            tmp = tmp->right;
        } else {
            return -1;
        }
    }

    return 0;
}

int
bst_set_remove(bst_set *set, const int key)
{
    struct bst_set_node *parent = NULL;
    struct bst_set_node *tmp = set->root;
    while (tmp != NULL) {
        int cmp = memcmp(&key, &tmp->key, sizeof(int));
        if (cmp < 0) {
            parent = tmp;
            tmp = tmp->left;
        } else if (cmp > 0) {
            parent = tmp;
            tmp = tmp->right;
        } else {
            if (parent == NULL) {
                parent = tmp;
                FREE(parent);
                set->root = tmp->left ? tmp->left : tmp->right;
            } else {
                if (parent->left == tmp)
                    parent->left = tmp->left ? tmp->left : tmp->right;
                else
                    parent->right = tmp->left ? tmp->left : tmp->right;
                FREE(tmp);
            }
            set->len--;
            return 0;
        }
    }

    return -1;
}

int
bst_set_search(bst_set *set, const int key)
{
    if (set->root != NULL) {
        struct bst_set_node *tmp = set->root;
        while (tmp != NULL) {
            int cmp = memcmp(&key, &tmp->key, sizeof(int));
            if (cmp < 0)
                tmp = tmp->left;
            else if (cmp > 0)
                tmp = tmp->right;
            else
                return 1;
        }
    }

    return 0;
}

static void
recursive_free(struct bst_set_node *node)
{
    if (node->left != NULL)
        recursive_free(node->left);
    if (node->right != NULL)
        recursive_free(node->right);
    FREE(node);
}

void
bst_set_free(bst_set set)
{
    recursive_free(set.root);
}
