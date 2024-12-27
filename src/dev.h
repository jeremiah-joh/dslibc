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
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _DEV_H
#define _DEV_H

#include <stddef.h>

#define INIT_DEV_TYPE(name, type)                                              \
struct dev_##name {                                                            \
        type *arr;                                                             \
        size_t cap, beg, len;                                                  \
};                                                                             \
                                                                               \
struct dev_##name##_iter {                                                     \
        struct dev_##name *dev;                                                \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct dev_##name dev_##name##_new(void);                                      \
struct dev_##name dev_##name##_from(const type *, const size_t);               \
struct dev_##name dev_##name##_copy(const struct dev_##name *);                \
int dev_##name##_push_back(struct dev_##name *, const type);                   \
int dev_##name##_pop_back(struct dev_##name *, type *);                        \
int dev_##name##_push_front(struct dev_##name *, const type);                  \
int dev_##name##_pop_front(struct dev_##name *, type *);                       \
int dev_##name##_get(struct dev_##name *, type *, const size_t);               \
int dev_##name##_set(struct dev_##name *, const type, const size_t);           \
int dev_##name##_append(struct dev_##name *, const type *, const size_t);      \
int dev_##name##_insert(struct dev_##name *, const type, const size_t);        \
int dev_##name##_remove(struct dev_##name *, type *, const size_t);            \
int dev_##name##_shrink(struct dev_##name *, const size_t);                    \
size_t dev_##name##_len(struct dev_##name *);                                  \
void dev_##name##_free(struct dev_##name *);                                   \
                                                                               \
struct dev_##name##_iter dev_##name##_iter(struct dev_##name *);               \
int dev_##name##_next(struct dev_##name##_iter *, type *);                     \
                                                                               \
extern int _dev_##name##_type

#define INIT_DEV_FUNC(name, type, malloc, realloc, free)

#define INIT_DEV_BOTH(name, type, malloc, realloc, free)
INIT_DEV_TYPE(name, type);
INIT_DEV_FUNC(name, type, malloc, realloc, free)

#endif
