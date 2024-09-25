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

#ifndef _SGT_H
#define _SGT_H

#include <stddef.h>

#define MAX_DEPTH (sizeof(size_t) * 8)

#define INIT_SGT_TYPE(name, type)                                              \
struct sgt_##name##_node {                                                     \
        type val;                                                              \
        struct sgt_##name##_node *kid[2];                                      \
};                                                                             \
                                                                               \
struct sgt_##name {                                                            \
        struct sgt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct sgt_##name##_iter {                                                     \
        struct sgt_##name##_node *cur, *arr[MAX_DEPTH];                        \
        size_t top;                                                            \
};                                                                             \
                                                                               \
struct sgt_##name sgt_##name##_new(void);                                      \
struct sgt_##name sgt_##name##_from(const type *, const size_t);               \
struct sgt_##name sgt_##name##_copy(const struct sgt_##name *);                \
int sgt_##name##_root(struct sgt_##name *, type *);                            \
int sgt_##name##_max(struct sgt_##name *, type *);                             \
int sgt_##name##_min(struct sgt_##name *, type *);                             \
int sgt_##name##_get(struct sgt_##name *, type *);                             \
int sgt_##name##_set(struct sgt_##name *, const type);                         \
int sgt_##name##_insert(struct sgt_##name *, const type);                      \
int sgt_##name##_remove(struct sgt_##name *, type *);                          \
size_t sgt_##name##_length(struct sgt_##name *);                               \
size_t sgt_##name##_sizeof(struct sgt_##name *);                               \
void sgt_##name##_free(struct sgt_##name *);                                   \
                                                                               \
struct sgt_##name##_iter sgt_##name##_iter(struct sgt_##name *);               \
int sgt_##name##_next(struct sgt_##name##_iter *, type *);

#define INIT_SGT_FUNC(name, type, cmp, malloc, free)                           \

#define INIT_SGT_BOTH(name, type, cmp, malloc, free)                           \
INIT_SGT_TYPE(name, type)                                                      \
INIT_SGT_FUNC(name, type, cmp, malloc, free)

#define FOR_EACH_SGT(name, elem, iter) while (!sgt_##name##_next(&iter, &elem))

#endif
