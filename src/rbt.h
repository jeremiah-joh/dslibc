/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyrigrbt
 * and related and neighboring rigrbts to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <rbttp://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _RBT_H
#define _RBT_H

#include <stddef.h>

enum rbt_color { RED, BLACK };

#define INIT_RBT_TYPE(name, type)                                              \
struct rbt_##name##_node {                                                     \
        type val;                                                              \
        struct rbt_##name##_node *par, *kid[2];                                \
        enum rbt_color col;                                                    \
};                                                                             \
                                                                               \
struct rbt_##name {                                                            \
        struct rbt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct rbt_##name##_iter {                                                     \
        struct rbt_##name##_node *cur, *prv;                                   \
};                                                                             \
                                                                               \
struct rbt_##name rbt_##name##_new(void);                                      \
struct rbt_##name rbt_##name##_from(const type *, const size_t);               \
struct rbt_##name rbt_##name##_copy(const struct rbt_##name *);                \
int rbt_##name##_root(struct rbt_##name *, type *);                            \
int rbt_##name##_max(struct rbt_##name *, type *);                             \
int rbt_##name##_min(struct rbt_##name *, type *);                             \
int rbt_##name##_get(struct rbt_##name *, type *);                             \
int rbt_##name##_set(struct rbt_##name *, const type);                         \
int rbt_##name##_insert(struct rbt_##name *, const type);                      \
int rbt_##name##_remove(struct rbt_##name *, type *);                          \
size_t rbt_##name##_len(struct rbt_##name *);                                  \
void rbt_##name##_free(struct rbt_##name *);                                   \
                                                                               \
struct rbt_##name##_iter rbt_##name##_iter(struct rbt_##name *);               \
int rbt_##name##_next(struct rbt_##name##_iter *, type *);                     \
                                                                               \
extern int _rbt_type_##name

#define INIT_RBT_FUNC(name, type, cmp, malloc, free)

#define INIT_RBT_BOTH(name, type, cmp, malloc, free)
INIT_RBT_TYPE(name, type);
INIT_RBT_FUNC(name, type, cmp, malloc, free)

#endif
