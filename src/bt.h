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

#ifndef _BT_H
#define _BT_H

#include <stddef.h>

#define INIT_BT_TYPE(name, type, ord)                                          \
struct bt_##name##_node {                                                      \
        type val[ord - 1];                                                     \
        struct bt_##name##_node *kid[ord];                                     \
};                                                                             \
                                                                               \
struct bt_##name {                                                             \
        struct bt_##name##_node *root;                                         \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct bt_##name##_iter {                                                      \
        structb bt_##name##_node *cur;                                         \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct bt_##name bt_##name##_new(void);                                        \
struct bt_##name bt_##name##_from(const type *, const size_t);                 \
struct bt_##name bt_##name##_copy(const struct bt_##name *);                   \
int bt_##name##_root(struct bt_##name *, type *);                              \
int bt_##name##_max(struct bt_##name *, type *);                               \
int bt_##name##_min(struct bt_##name *, type *);                               \
int bt_##name##_get(struct bt_##name *, type *);                               \
int bt_##name##_set(struct bt_##name *, const type);                           \
int bt_##name##_insert(struct bt_##name *, const type);                        \
int bt_##name##_remove(struct bt_##name *, type *);                            \
size_t bt_##name##_length(struct bt_##name *);                                 \
size_t bt_##name##_sizeof(struct bt_##name *);                                 \
void bt_##name##_free(struct bt_##name *);                                     \
                                                                               \
struct bt_##name##_iter bt_##name##_iter(struct bt_##name *);                  \
int bt_##name##_next(struct bt_##name##_iter *, type *);

#define INIT_BT_FUNC(name, type, ord, cmp, malloc, free)

#define INIT_BT_BOTH(name, type, ord, cmp, malloc, free)                       \
INIT_BT_TYPE(name, type, ord)                                                  \
INIT_BT_FUNC(name, type, ord, cmp, malloc, free)

#define FOR_EACH_BT(name, elem, iter) while (!bt_##name##_next(&iter, &elem))

#endif
