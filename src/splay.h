/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyrigsplay
 * and related and neighboring rigsplays to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <splaytp://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _SPLAY_H
#define _SPLAY_H

#include <stddef.h>

#define INIT_SPLAY_TYPE(name, type)                                            \
struct splay_##name##_node {                                                   \
        type val;                                                              \
        struct splay_##name##_node *kid[2];                                    \
};                                                                             \
                                                                               \
struct splay_##name {                                                          \
        struct splay_##name##_node *root;                                      \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct splay_##name##_iter {                                                   \
        struct splay_##name##_node *root;                                      \
};                                                                             \
                                                                               \
struct splay_##name splay_##name##_new(void);                                  \
struct splay_##name splay_##name##_from(const type *, const size_t);           \
struct splay_##name splay_##name##_copy(const struct splay_##name *);          \
int splay_##name##_root(struct splay_##name *, type *);                        \
int splay_##name##_max(struct splay_##name *, type *);                         \
int splay_##name##_min(struct splay_##name *, type *);                         \
int splay_##name##_get(struct splay_##name *, type *);                         \
int splay_##name##_set(struct splay_##name *, const type);                     \
int splay_##name##_insert(struct splay_##name *, const type);                  \
int splay_##name##_remove(struct splay_##name *, type *);                      \
size_t splay_##name##_len(struct splay_##name *);                              \
void splay_##name##_free(struct splay_##name *);                               \
                                                                               \
struct splay_##name##_iter splay_##name##_iter(struct splay_##name *);         \
int splay_##name##_next(struct splay_##name##_iter *, type *);                 \
                                                                               \
extern int _splay_type_##name

#define INIT_SPLAY_FUNC(name, type, cmp, malloc, free)

#define INIT_SPLAY_BOTH(name, type, cmp, malloc, free)
INIT_SPLAY_TYPE(name, type);
INIT_SPLAY_FUNC(name, type, cmp, malloc, free)

#endif
