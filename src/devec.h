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
struct devec_##name {                                                          \
        type *arr;                                                             \
        size_t cap, beg, len;                                                  \
};                                                                             \
                                                                               \
struct devec_##name##_iter {                                                   \
        struct devec_##name *devec;                                            \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct devec_##name devec_##name##_new(void);                                  \
struct devec_##name devec_##name##_from(const type *, const size_t);           \
struct devec_##name devec_##name##_copy(const struct devec_##name *);          \
int devec_##name##_push_back(struct devec_##name *, const type);               \
int devec_##name##_pop_back(struct devec_##name *, type *);                    \
int devec_##name##_push_front(struct devec_##name *, const type);              \
int devec_##name##_pop_front(struct devec_##name *, type *);                   \
int devec_##name##_get(struct devec_##name *, type *, const size_t);           \
int devec_##name##_set(struct devec_##name *, const type, const size_t);       \
int devec_##name##_append(struct devec_##name *, const type *, const size_t);  \
int devec_##name##_insert(struct devec_##name *, const type, const size_t);    \
int devec_##name##_remove(struct devec_##name *, type *, const size_t);        \
int devec_##name##_shrink(struct devec_##name *, const size_t);                \
size_t devec_##name##_len(struct devec_##name *);                              \
void devec_##name##_free(struct devec_##name *);                               \
                                                                               \
struct devec_##name##_iter devec_##name##_iter(struct devec_##name *);         \
int devec_##name##_next(struct devec_##name##_iter *, type *);                 \
                                                                               \
extern int _devec_type_##name

#define INIT_DEV_FUNC(name, type, malloc, realloc, free)

#define INIT_DEV_BOTH(name, type, malloc, realloc, free)
INIT_DEV_TYPE(name, type);
INIT_DEV_FUNC(name, type, malloc, realloc, free)

#endif
