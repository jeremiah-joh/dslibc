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

#ifndef _BST_H
#define _BST_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

#define INIT_BST_MAP(name, type)                                              \
struct bst_##name##_map_node {                                                \
    type key;                                                                 \
    type val;                                                                 \
                                                                              \
    struct bst_##name##_map_node *left;                                       \
    struct bst_##name##_map_node *right;                                      \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct bst_##name##_map_node *root;                                       \
    size_t len;                                                               \
} bst_##name##_map;                                                           \
                                                                              \
bst_##name##_map                                                              \
bst_##name##_map_new()                                                        \
{                                                                             \
    bst_##name##_map map = { NULL, 0 };                                       \
    return map;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_map_insert(bst_##name##_map *map, const type key, const type val)\
{                                                                             \
    int                                                                       \
    new_node(struct bst_##name##_map_node **node,                             \
             const type key, const type val)                                  \
    {                                                                         \
        *node = malloc(sizeof(struct bst_##name##_map_node));                 \
        if (*node == NULL)                                                    \
            return -1;                                                        \
        (*node)->key = key;                                                   \
        (*node)->val = val;                                                   \
        (*node)->left = NULL;                                                 \
        (*node)->right = NULL;                                                \
        map->len++;                                                           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    if (map->root == NULL)                                                    \
        return new_node(&map->root, key, val);                                \
                                                                              \
    struct bst_##name##_map_node *tmp = map->root;                            \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(type));                      \
        if (cmp < 0) {                                                        \
            if (tmp->left == NULL)                                            \
                return new_node(&tmp->left, key, val);                        \
            tmp = tmp->left;                                                  \
        } else {                                                              \
            if (tmp->right == NULL)                                           \
                return new_node(&tmp->right, key, val);                       \
            tmp = tmp->right;                                                 \
        }                                                                     \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_map_remove(bst_##name##_map *map, const type key, type *val)     \
{                                                                             \
    struct bst_##name##_map_node *parent = NULL;                              \
    struct bst_##name##_map_node *tmp = map->root;                            \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(type));                      \
        if (cmp < 0) {                                                        \
            parent = tmp;                                                     \
            tmp = tmp->left;                                                  \
        } else if (cmp > 0) {                                                 \
            parent = tmp;                                                     \
            tmp = tmp->right;                                                 \
        } else {                                                              \
            *val = tmp->val;                                                  \
                                                                              \
            if (parent == NULL) {                                             \
                parent = tmp;                                                 \
                FREE(parent);                                                 \
                map->root = tmp->left ? tmp->left : tmp->right;               \
            } else {                                                          \
                if (parent->left == tmp)                                      \
                    parent->left = tmp->left ? tmp->left : tmp->right;        \
                else                                                          \
                    parent->right = tmp->left ? tmp->left : tmp->right;       \
                FREE(tmp);                                                    \
            }                                                                 \
                                                                              \
            map->len--;                                                       \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_map_search(bst_##name##_map *map, const type key, type *val)     \
{                                                                             \
    struct bst_##name##_map_node *tmp = map->root;                            \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(type));                      \
        if (cmp < 0)                                                          \
            tmp = tmp->left;                                                  \
        else if (cmp > 0)                                                     \
            tmp = tmp->right;                                                 \
        else {                                                                \
            *val = tmp->val;                                                  \
                                                                              \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
static void                                                                   \
map_recursive_free(struct bst_##name##_map_node *node)                        \
{                                                                             \
    if (node->left != NULL)                                                   \
        map_recursive_free(node->left);                                       \
    if (node->right != NULL)                                                  \
        map_recursive_free(node->right);                                      \
    FREE(node);                                                               \
}                                                                             \
                                                                              \
void                                                                          \
bst_##name##_map_free(bst_##name##_map map)                                   \
{                                                                             \
    map_recursive_free(map.root);                                             \
}

#define INIT_BST_SET(name, type)                                              \
struct bst_##name##_set_node {                                                \
    type key;                                                                 \
                                                                              \
    struct bst_##name##_set_node *left;                                       \
    struct bst_##name##_set_node *right;                                      \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct bst_##name##_set_node *root;                                       \
    size_t len;                                                               \
} bst_##name##_set;                                                           \
                                                                              \
bst_##name##_set                                                              \
bst_##name##_set_new()                                                        \
{                                                                             \
    bst_##name##_set set = { NULL, 0 };                                       \
    return set;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_set_insert(bst_##name##_set *set, const type key)                \
{                                                                             \
    int                                                                       \
    new_node(struct bst_##name##_set_node **node, const type key)             \
    {                                                                         \
        *node = malloc(sizeof(struct bst_##name##_set_node));                 \
        if (*node == NULL)                                                    \
            return -1;                                                        \
        (*node)->key = key;                                                   \
        (*node)->left = NULL;                                                 \
        (*node)->right = NULL;                                                \
        set->len++;                                                           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    if (set->root == NULL) {                                                  \
        return new_node(&set->root, key);                                     \
    }                                                                         \
                                                                              \
    struct bst_##name##_set_node *tmp = set->root;                            \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(type));                      \
        if (cmp < 0) {                                                        \
            if (tmp->left == NULL)                                            \
                return new_node(&tmp->left, key);                             \
            tmp = tmp->left;                                                  \
        } else if (cmp > 0) {                                                 \
            if (tmp->right == NULL)                                           \
                return new_node(&tmp->right, key);                            \
            tmp = tmp->right;                                                 \
        } else {                                                              \
            return -1;                                                        \
        }                                                                     \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_set_remove(bst_##name##_set *set, const type key)                \
{                                                                             \
    struct bst_##name##_set_node *parent = NULL;                              \
    struct bst_##name##_set_node *tmp = set->root;                            \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(type));                      \
        if (cmp < 0) {                                                        \
            parent = tmp;                                                     \
            tmp = tmp->left;                                                  \
        } else if (cmp > 0) {                                                 \
            parent = tmp;                                                     \
            tmp = tmp->right;                                                 \
        } else {                                                              \
            if (parent == NULL) {                                             \
                parent = tmp;                                                 \
                FREE(parent);                                                 \
                set->root = tmp->left ? tmp->left : tmp->right;               \
            } else {                                                          \
                if (parent->left == tmp)                                      \
                    parent->left = tmp->left ? tmp->left : tmp->right;        \
                else                                                          \
                    parent->right = tmp->left ? tmp->left : tmp->right;       \
                FREE(tmp);                                                    \
            }                                                                 \
            set->len--;                                                       \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_set_search(bst_##name##_set *set, const type key)                \
{                                                                             \
    if (set->root != NULL) {                                                  \
        struct bst_##name##_set_node *tmp = set->root;                        \
        while (tmp != NULL) {                                                 \
            int cmp = memcmp(&key, &tmp->key, sizeof(type));                  \
            if (cmp < 0)                                                      \
                tmp = tmp->left;                                              \
            else if (cmp > 0)                                                 \
                tmp = tmp->right;                                             \
            else                                                              \
                return 1;                                                     \
        }                                                                     \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static void                                                                   \
set_recursive_free(struct bst_##name##_set_node *node)                        \
{                                                                             \
    if (node->left != NULL)                                                   \
        set_recursive_free(node->left);                                       \
    if (node->right != NULL)                                                  \
        set_recursive_free(node->right);                                      \
    FREE(node);                                                               \
}                                                                             \
                                                                              \
void                                                                          \
bst_##name##_set_free(bst_##name##_set set)                                   \
{                                                                             \
    set_recursive_free(set.root);                                             \
}

#endif
