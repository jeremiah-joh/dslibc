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

#ifndef _HT_H
#define _HT_H

#include <stddef.h>

#define INIT_SIZE 4

#define NEXT(i, c) (((i) + 1) % (c))
#define THREE_FOURTH(i) ((i - (i >> 2))) /* i - (i / 4) == i * 3 / 4*/

#define INIT_HT_TYPE(name, type)                                               \
struct ht_##name##_node {                                                      \
        type val;                                                              \
        enum { NONE, SOME, TOMB } state;                                       \
};                                                                             \
                                                                               \
struct ht_##name {                                                             \
        struct ht_##name##_node *arr;                                          \
        size_t cap, len;                                                       \
};                                                                             \
                                                                               \
struct ht_##name##_iter {                                                      \
        struct ht_##name *ht;                                                  \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct ht_##name ht_##name##_new(void);                                        \
struct ht_##name ht_##name##_from(const type *, const size_t);                 \
struct ht_##name ht_##name##_copy(const struct ht_##name *);                   \
int ht_##name##_get(struct ht_##name *, type *);                               \
int ht_##name##_set(struct ht_##name *, const type);                           \
int ht_##name##_insert(struct ht_##name *, const type);                        \
int ht_##name##_remove(struct ht_##name *, type *);                            \
size_t ht_##name##_len(struct ht_##name *);                                    \
void ht_##name##_free(struct ht_##name *);                                     \
                                                                               \
struct ht_##name##_iter ht_##name##_iter(struct ht_##name *);                  \
int ht_##name##_next(struct ht_##name##_iter *, type *);                       \
                                                                               \
extern int _ht_##name##_type

#define INIT_HT_FUNC(name, type, hash, cmp, malloc, free)                      \
static struct ht_##name##_node *                                               \
ht_##name##_calloc(const size_t cap)                                           \
{                                                                              \
        struct ht_##name##_node *arr;                                          \
        size_t i;                                                              \
                                                                               \
        if ((arr = malloc(cap * sizeof(struct ht_##name##_node))) == NULL)     \
                return NULL;                                                   \
        for (i = 0; i < cap; i++)                                              \
                arr[i].state = NONE;                                           \
                                                                               \
        return arr;                                                            \
}                                                                              \
                                                                               \
static int                                                                     \
ht_##name##_place(struct ht_##name *ht, const type val)                        \
{                                                                              \
        size_t h, i;                                                           \
                                                                               \
        i = h = hash(val) & (ht->cap - 1);                                     \
        while (ht->arr[i].state == SOME)                                       \
                if ((i = NEXT(i, ht->cap)) == h)                               \
                        return -1;                                             \
                                                                               \
        ht->arr[i].val = val;                                                  \
        ht->arr[i].state = SOME;                                               \
        ht->len++;                                                             \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
static size_t                                                                  \
ht_##name##_match(struct ht_##name *ht, const type val)                        \
{                                                                              \
        size_t h, i;                                                           \
                                                                               \
        h = hash(val) & (ht->cap - 1);                                         \
        for (i = h; NEXT(i, ht->cap) != h; i = NEXT(i, ht->cap)) {             \
                switch (ht->arr[i].state) {                                    \
                case NONE:                                                     \
                        return ht->cap;                                        \
                case TOMB:                                                     \
                        continue;                                              \
                case SOME:                                                     \
                        if (cmp(val, ht->arr[i].val) == 0)                     \
                                return i;                                      \
                }                                                              \
        }                                                                      \
                                                                               \
        return ht->cap;                                                        \
}                                                                              \
                                                                               \
static int                                                                     \
ht_##name##_extend(struct ht_##name *ht)                                       \
{                                                                              \
        struct ht_##name cp;                                                   \
        size_t i;                                                              \
                                                                               \
        if (ht->len < THREE_FOURTH(ht->cap))                                   \
                return 0;                                                      \
                                                                               \
        cp.cap = ht->cap ? ht->cap << 1 : INIT_SIZE;                           \
        cp.len = 0;                                                            \
                                                                               \
        if ((cp.arr = ht_##name##_calloc(cp.cap)) == NULL)                     \
                return -1;                                                     \
        for (i = 0; i < ht->cap; i++)                                          \
                if (ht->arr[i].state == SOME)                                  \
                        if (ht_##name##_place(&cp, ht->arr[i].val))            \
                                return -1;                                     \
                                                                               \
        free(ht->arr);                                                         \
        *ht = cp;                                                              \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
struct ht_##name                                                               \
ht_##name##_new(void)                                                          \
{                                                                              \
        struct ht_##name ht;                                                   \
                                                                               \
        ht.arr = malloc(0);                                                    \
        ht.cap = ht.len = 0;                                                   \
                                                                               \
        return ht;                                                             \
}                                                                              \
                                                                               \
struct ht_##name                                                               \
ht_##name##_from(const type *arr, const size_t len)                            \
{                                                                              \
        struct ht_##name ht;                                                   \
        size_t i;                                                              \
                                                                               \
        ht.len = 0;                                                            \
                                                                               \
        for (ht.cap = INIT_SIZE; ht.cap < len; ht.cap <<= 1)                   \
                ;                                                              \
        if ((ht.arr = ht_##name##_calloc(ht.cap)) == NULL)                     \
                return ht_##name##_new();                                      \
        for (i = 0; i < len; i++)                                              \
                if (ht_##name##_place(&ht, arr[i]))                            \
                        break;                                                 \
                                                                               \
        return ht;                                                             \
}                                                                              \
                                                                               \
struct ht_##name                                                               \
ht_##name##_copy(const struct ht_##name *ht)                                   \
{                                                                              \
        struct ht_##name cp;                                                   \
        size_t i;                                                              \
                                                                               \
        cp.cap = ht->cap;                                                      \
                                                                               \
        if ((cp.arr = ht_##name##_calloc(cp.cap)) == NULL)                     \
                return ht_##name##_new();                                      \
        for (i = 0; i < ht->len; i++)                                          \
                if (ht->arr[i].state == SOME)                                  \
                        if (ht_##name##_place(&cp, ht->arr[i].val))            \
                                break;                                         \
                                                                               \
        return cp;                                                             \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_get(struct ht_##name *ht, type *val)                               \
{                                                                              \
        size_t i;                                                              \
                                                                               \
        if (ht->arr == NULL || ht->cap == 0 || ht->len == 0 || val == NULL)    \
                return -1;                                                     \
        if ((i = ht_##name##_match(ht, *val)) == ht->cap)                      \
                return -1;                                                     \
                                                                               \
        *val = ht->arr[i].val;                                                 \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_set(struct ht_##name *ht, const type val)                          \
{                                                                              \
        size_t i;                                                              \
                                                                               \
        if (ht->arr == NULL || ht->cap == 0 || ht->len == 0)                   \
                return -1;                                                     \
        if ((i = ht_##name##_match(ht, val)) == ht->cap)                       \
                return -1;                                                     \
                                                                               \
        ht->arr[i].val = val;                                                  \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_insert(struct ht_##name *ht, const type val)                       \
{                                                                              \
        if (ht->arr == NULL)                                                   \
                return -1;                                                     \
        if (ht_##name##_extend(ht))                                            \
                return -1;                                                     \
                                                                               \
        return ht_##name##_place(ht, val);                                     \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_remove(struct ht_##name *ht, type *val)                            \
{                                                                              \
        size_t i;                                                              \
                                                                               \
        if (ht->arr == NULL || ht->cap == 0 || ht->len == 0 || val == NULL)    \
                return -1;                                                     \
        if ((i = ht_##name##_match(ht, *val)) == ht->cap)                      \
                return -1;                                                     \
                                                                               \
        *val = ht->arr[i].val;                                                 \
        ht->arr[i].state = TOMB;                                               \
        ht->len--;                                                             \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
ht_##name##_len(struct ht_##name *ht)                                          \
{                                                                              \
        return ht->len;                                                        \
}                                                                              \
                                                                               \
void                                                                           \
ht_##name##_free(struct ht_##name *ht)                                         \
{                                                                              \
        free(ht->arr);                                                         \
        ht->arr = NULL;                                                        \
        ht->cap = ht->len = 0;                                                 \
}                                                                              \
                                                                               \
struct ht_##name##_iter                                                        \
ht_##name##_iter(struct ht_##name *ht)                                         \
{                                                                              \
        struct ht_##name##_iter iter;                                          \
                                                                               \
        iter.ht = ht;                                                          \
        iter.idx = 0;                                                          \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_next(struct ht_##name##_iter *iter, type *val)                     \
{                                                                              \
        for (; iter->idx < iter->ht->cap; iter->idx++) {                       \
                if (iter->ht->arr[iter->idx].state == SOME) {                  \
                        if (val)                                               \
                                *val = iter->ht->arr[iter->idx++].val;         \
                                                                               \
                        return 0;                                              \
                }                                                              \
        }                                                                      \
                                                                               \
        return -1;                                                             \
}                                                                              \
                                                                               \
extern int _ht_##name##_func

#define INIT_HT_BOTH(name, type, hash, cmp, malloc, free)                      \
INIT_HT_TYPE(name, type);                                                      \
INIT_HT_FUNC(name, type, hash, cmp, malloc, free)

#define FOR_EACH_HT(name, elem, iter) while (!ht_##name##_next(&iter, &elem))

#endif
