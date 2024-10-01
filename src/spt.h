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

#ifndef _SPT_H
#define _SPT_H

#include <stddef.h>

#define INIT_SPT_TYPE(name, type)                                              \
struct spt_##name##_node {                                                     \
        type val;                                                              \
        struct spt_##name##_node *par, *kid[2];                                \
};                                                                             \
                                                                               \
struct spt_##name {                                                            \
        struct spt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct spt_##name##_iter {                                                     \
        struct spt_##name##_node *cur, *arr[MAX_DEPTH];                        \
        size_t top;                                                            \
};                                                                             \
                                                                               \
struct spt_##name spt_##name##_new(void);                                      \
struct spt_##name spt_##name##_from(const type *, const size_t);               \
struct spt_##name spt_##name##_copy(const struct spt_##name *);                \
int spt_##name##_root(struct spt_##name *, type *);                            \
int spt_##name##_max(struct spt_##name *, type *);                             \
int spt_##name##_min(struct spt_##name *, type *);                             \
int spt_##name##_get(struct spt_##name *, type *);                             \
int spt_##name##_set(struct spt_##name *, const type);                         \
int spt_##name##_insert(struct spt_##name *, const type);                      \
int spt_##name##_remove(struct spt_##name *, type *);                          \
size_t spt_##name##_len(struct spt_##name *);                                  \
void spt_##name##_free(struct spt_##name *);                                   \
                                                                               \
struct spt_##name##_iter spt_##name##_iter(struct spt_##name *);               \
int spt_##name##_next(struct spt_##name##_iter *, type *);

#define INIT_SPT_FUNC(name, type, cmp, malloc, free)

#define FOR_EACH_SPT(name, elem, iter) while (!spt_##name##_next(&iter, &elem))

#define INIT_SPT_BOTH(name, type, cmp, malloc, free)                           \
INIT_SPT_TYPE(name, type)                                                      \
INIT_SPT_FUNC(name, type, cmp, malloc, free)

#endif
