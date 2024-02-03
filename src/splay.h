#ifndef splay_H
#define splay_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define INIT_SPLAY_MAP(name, k_ty, v_ty)                                      \
struct splay_##name##_map_node {                                              \
    k_ty key;                                                                 \
    v_ty val;                                                                 \
    struct splay_##name##_map_node *left, *right, *parent;                    \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct splay_##name##_map_node *root;                                     \
    size_t len;                                                               \
} splay_##name##_map;                                                         \
                                                                              \
static void                                                                   \
rotate_left(splay_##name##_map *map, struct splay_##name##_map_node *root)    \
{                                                                             \
    struct splay_##name##_map_node *right = root->right;                      \
    if (right != NULL) {                                                      \
        root->right = right->left;                                            \
        if (right->left != NULL)                                              \
            right->left->parent = root;                                       \
        right->parent = root->parent;                                         \
    }                                                                         \
                                                                              \
    if (root->parent == NULL)                                                 \
        map->root = right;                                                    \
    else if (root->parent->left == root)                                      \
        root->parent->left = right;                                           \
    else                                                                      \
        root->parent->right = right;                                          \
                                                                              \
    if (right != NULL)                                                        \
        right->left = root;                                                   \
                                                                              \
    root->parent = right;                                                     \
}                                                                             \
                                                                              \
static void                                                                   \
rotate_right(splay_##name##_map *map, struct splay_##name##_map_node *root)   \
{                                                                             \
    struct splay_##name##_map_node *left = root->left;                        \
    if (left != NULL) {                                                       \
        root->left = left->right;                                             \
        if (left->right != NULL)                                              \
            left->right->parent = root;                                       \
        left->parent = root->parent;                                          \
    }                                                                         \
                                                                              \
    if (root->parent == NULL)                                                 \
        map->root = left;                                                     \
    else if (root->parent->left == root)                                      \
        root->parent->left = left;                                            \
    else                                                                      \
        root->parent->right = left;                                           \
                                                                              \
    if (left != NULL)                                                         \
        left->right = root;                                                   \
    root->parent = left;                                                      \
}                                                                             \
                                                                              \
static void                                                                   \
splay(splay_##name##_map *map, struct splay_##name##_map_node *node)          \
{                                                                             \
    while (node->parent != NULL) {                                            \
        if (node->parent->parent == NULL) {                                   \
            if (node->parent->left == node)                                   \
                rotate_right(map, node->parent);                              \
            else                                                              \
                rotate_left(map, node->parent);                               \
        } else if (node->parent->left == node                                 \
                   && node->parent->parent->left == node->parent) {           \
            rotate_right(map, node->parent->parent);                          \
            rotate_right(map, node->parent);                                  \
        } else if (node->parent->right == node                                \
                   && node->parent->parent->right == node->parent) {          \
            rotate_left(map, node->parent->parent);                           \
            rotate_left(map, node->parent);                                   \
        } else if (node->parent->left == node                                 \
                   && node->parent->parent->right == node->parent) {          \
            rotate_right(map, node->parent);                                  \
            rotate_left(map, node->parent);                                   \
        } else {                                                              \
            rotate_left(map, node->parent);                                   \
            rotate_right(map, node->parent);                                  \
        }                                                                     \
    }                                                                         \
                                                                              \
    map->root = node;                                                         \
}                                                                             \
                                                                              \
static int                                                                    \
new_node(splay_##name##_map *map, struct splay_##name##_map_node **node,      \
         k_ty key, v_ty val, struct splay_##name##_map_node *parent)          \
{                                                                             \
    (*node) = malloc(sizeof(struct splay_##name##_map_node));                 \
    if (node == NULL)                                                         \
        return -1;                                                            \
    (*node)->key = key;                                                       \
    (*node)->val = val;                                                       \
    (*node)->left = NULL;                                                     \
    (*node)->right = NULL;                                                    \
    (*node)->parent = parent;                                                 \
    splay(map, *node);                                                        \
    map->len++;                                                               \
    return 0;                                                                 \
}                                                                             \
                                                                              \
splay_##name##_map                                                            \
splay_##name##_map_new()                                                      \
{                                                                             \
    splay_##name##_map map = { NULL, 0 };                                     \
    return map;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
splay_##name##_map_insert(splay_##name##_map *map,                            \
                          const k_ty key, const v_ty val)                     \
{                                                                             \
    if (map->root == NULL)                                                    \
        return new_node(map, &map->root, key, val, NULL);                     \
                                                                              \
    struct splay_##name##_map_node *tmp = map->root;                          \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(key));                       \
        if (cmp < 0) {                                                        \
            if (tmp->left == NULL)                                            \
                return new_node(map, &tmp->left, key, val, tmp);              \
            tmp = tmp->left;                                                  \
        } else if (cmp > 0) {                                                 \
            if (tmp->right == NULL)                                           \
                return new_node(map, &tmp->right, key, val, tmp);             \
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
splay_##name##_map_remove(splay_##name##_map *map, const k_ty key, v_ty *val) \
{                                                                             \
    struct splay_##name##_map_node *tmp = map->root;                          \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(key));                       \
        if (cmp < 0)                                                          \
            tmp = tmp->left;                                                  \
        else if (cmp > 0)                                                     \
            tmp = tmp->right;                                                 \
        else {                                                                \
            *val = tmp->val;                                                  \
            splay(map, tmp);                                                  \
            if (tmp->left == NULL)                                            \
                map->root = tmp->right;                                       \
            else if (tmp->right == NULL)                                      \
                map->root = tmp->left;                                        \
            else {                                                            \
                struct splay_##name##_map_node *max = map->root->left;        \
                while (max->right != NULL)                                    \
                    max = max->right;                                         \
                splay_##name##_map buf = splay_##name##_map_new();            \
                splay(&buf, max);                                             \
                max->left = map->root;                                        \
                map->root->parent = max->left;                                \
                map->root = max;                                              \
            }                                                                 \
            free(tmp);                                                        \
            tmp = NULL;                                                       \
            map->len--;                                                       \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
splay_##name##_map_search(splay_##name##_map *map, const k_ty key, v_ty *val) \
{                                                                             \
    struct splay_##name##_map_node *tmp = map->root;                          \
    while (tmp != NULL) {                                                     \
        int cmp = memcmp(&key, &tmp->key, sizeof(key));                       \
        if (cmp < 0)                                                          \
            tmp = tmp->left;                                                  \
        else if (cmp > 0)                                                     \
            tmp = tmp->right;                                                 \
        else {                                                                \
            *val = tmp->val;                                                  \
            splay(map, tmp);                                                  \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
size_t                                                                        \
splay_##name##_map_length(splay_##name##_map map)                             \
{                                                                             \
    return map.len;                                                           \
}                                                                             \
                                                                              \
static void                                                                   \
splay_map_recursive_free(struct splay_##name##_map_node *node)                \
{                                                                             \
    if (node->left != NULL)                                                   \
        splay_map_recursive_free(node->left);                                 \
    if (node->right != NULL)                                                  \
        splay_map_recursive_free(node->right);                                \
    free(node);                                                               \
    node = NULL;                                                              \
}                                                                             \
                                                                              \
void                                                                          \
splay_##name##_map_free(splay_##name##_map map)                               \
{                                                                             \
    splay_map_recursive_free(map.root);                                       \
}

#endif
