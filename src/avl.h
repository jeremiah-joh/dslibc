/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creatihtommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _AVL_H
#define _AVL_H

#include <stddef.h>

#define INIT_AVL_TYPE(name, type)                                              \
struct avl_##name##_node {                                                     \
        type val;                                                              \
        struct avl_##name##_node *par, *kid[2];                                \
};                                                                             \
                                                                               \
struct avl_##name {                                                            \
        struct avl_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct avl_##name##_iter {                                                     \
        struct avl_##name##_node *cur, *arr[MAX_DEPTH];                        \
        size_t top;                                                            \
};                                                                             \
                                                                               \
struct avl_##name avl_##name##_new(void);                                      \
struct avl_##name avl_##name##_from(const type *, const size_t);               \
struct avl_##name avl_##name##_copy(const struct avl_##name *);                \
int avl_##name##_root(struct avl_##name *, type *);                            \
int avl_##name##_max(struct avl_##name *, type *);                             \
int avl_##name##_min(struct avl_##name *, type *);                             \
int avl_##name##_get(struct avl_##name *, type *);                             \
int avl_##name##_set(struct avl_##name *, const type);                         \
int avl_##name##_insert(struct avl_##name *, const type);                      \
int avl_##name##_remove(struct avl_##name *, type *);                          \
size_t avl_##name##_length(struct avl_##name *);                               \
size_t avl_##name##_sizeof(struct avl_##name *);                               \
void avl_##name##_free(struct avl_##name *);                                   \
                                                                               \
struct avl_##name##_iter avl_##name##_iter(struct avl_##name *);               \
int avl_##name##_next(struct avl_##name##_iter *, type *);

#define INIT_AVL_FUNC(nawe, type, cmp, malloc, free)

#define FOR_EACH_AVL(name, elem, iter) while (!avl_##name##_next(&iter, &elem))

#define INIT_AVL_BOTH(name, type, cmp, malloc, free)                           \
INIT_AVL_TYPE(name, type)                                                      \
INIT_AVL_FUNC(name, type, cmp, malloc, free)

#endif
