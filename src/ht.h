/*
 * dslibc - collection of useful data structures written in ANSI C
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
#include <string.h>

#define FNV1_32_BASIS 0x811c9dc5
#define FNV1_32_PRIME 0x01000193
#define FNV1_64_BASIS 0xcbf29ce484222325
#define FNV1_64_PRIME 0x00000100000001B3

#define INIT_HT_TYPE(name, key_t, val_t)                                      \
struct ht_##name##_node {                                                     \
        key_t key;                                                            \
        val_t val;                                                            \
        enum { NONE, TOMB, SOME } state;                                      \
};                                                                            \
                                                                              \
struct ht_##name {                                                            \
        struct ht_##name##_node *arr;                                         \
        size_t len, cap;                                                      \
};                                                                            \
                                                                              \
struct ht_##name##_iter {                                                     \
        struct ht_##name *ht;                                                 \
        size_t nxt;                                                           \
};                                                                            \
                                                                              \
struct ht_##name ht_##name##_new();                                           \
struct ht_##name ht_##name##_copy(const struct ht_##name);                    \
struct ht_##name ht_##name##_from(const key_t [], const val_t [],             \
                                  const size_t);                              \
struct ht_##name##_iter ht_##name##_iter(struct ht_##name *);                 \
int ht_##name##_insert(struct ht_##name *, const key_t, const val_t);         \
int ht_##name##_search(struct ht_##name *, const key_t, val_t *);             \
int ht_##name##_remove(struct ht_##name *, const key_t, val_t *);             \
int ht_##name##_getnxt(struct ht_##name##_iter *, val_t *);                   \
val_t *ht_##name##_ptr(struct ht_##name *, const key_t);                      \
void ht_##name##_free(struct ht_##name *) /* to enforce semicolon */

#define INIT_HT_FUNC(name, key_t, val_t, hash, cmp, malloc, free)             \
static size_t                                                                 \
ht_##name##_cap(const size_t len)                                             \
{                                                                             \
        size_t cap;                                                           \
                                                                              \
        for (cap = 4; cap < len; cap <<= 1)                                   \
                ;                                                             \
                                                                              \
        return cap;                                                           \
}                                                                             \
                                                                              \
static int                                                                    \
ht_##name##_resize(struct ht_##name *ht, const size_t len)                    \
{                                                                             \
        struct ht_##name new, old;                                            \
        size_t i;                                                             \
                                                                              \
        new.cap = ht_##name##_cap(ht_##name##_cap(len));                      \
        new.len = 0;                                                          \
        new.arr = malloc(new.cap * sizeof(struct ht_##name##_node));          \
        memset(new.arr, 0, new.cap * sizeof(struct ht_##name##_node));        \
                                                                              \
        for (i = 0; i < ht->cap; i++) {                                       \
                if (ht->arr[i].state != SOME)                                 \
                        continue;                                             \
                if (ht_##name##_insert(&new, ht->arr[i].key, ht->arr[i].val)) \
                        return -1;                                            \
        }                                                                     \
                                                                              \
        old = *ht;                                                            \
        *ht = new;                                                            \
        ht_##name##_free(&old);                                               \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_new()                                                             \
{                                                                             \
        struct ht_##name ht;                                                  \
                                                                              \
        ht.arr = malloc(0);                                                   \
        ht.len = ht.cap = 0;                                                  \
                                                                              \
        return ht;                                                            \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_copy(const struct ht_##name ht)                                   \
{                                                                             \
        struct ht_##name cp;                                                  \
                                                                              \
        cp.len = ht.len;                                                      \
        cp.cap = ht.cap;                                                      \
        cp.arr = malloc(cp.cap * sizeof(struct ht_##name##_node));            \
        memset(cp.arr, 0, cp.cap * sizeof(struct ht_##name##_node));          \
                                                                              \
        memcpy(cp.arr, ht.arr, cp.cap * sizeof(struct ht_##name##_node));     \
                                                                              \
        return cp;                                                            \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_from(const key_t key[], const val_t val[], const size_t len)      \
{                                                                             \
        size_t i;                                                             \
        struct ht_##name ht;                                                  \
                                                                              \
        ht = ht_##name##_new();                                               \
                                                                              \
        for (i = 0; i < len; i++)                                             \
                if (ht_##name##_insert(&ht, key[i], val[i]))                  \
                        return ht;                                            \
                                                                              \
        return ht;                                                            \
}                                                                             \
                                                                              \
struct ht_##name##_iter                                                       \
ht_##name##_iter(struct ht_##name *ht)                                        \
{                                                                             \
        struct ht_##name##_iter iter;                                         \
                                                                              \
        iter.ht = ht;                                                         \
        iter.nxt = 0;                                                         \
                                                                              \
        return iter;                                                          \
}                                                                             \
                                                                              \
int                                                                           \
ht_##name##_insert(struct ht_##name *ht, const key_t key, const val_t val)    \
{                                                                             \
        size_t i, h;                                                          \
                                                                              \
        if (ht->cap == ht->len)                                               \
                if (ht_##name##_resize(ht, ht->len + 1))                      \
                        return -1;                                            \
                                                                              \
        h = hash(key) & (ht->cap - 1);                                        \
        for (i = h; ht->arr[i].state == SOME; i = (i + 1) % ht->cap)          \
                if (cmp(key, ht->arr[i].key) == 0 || i + 1 == h)              \
                        return -1;                                            \
                                                                              \
        ht->arr[i].key = key;                                                 \
        ht->arr[i].val = val;                                                 \
        ht->arr[i].state = SOME;                                              \
        ht->len++;                                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
ht_##name##_search(struct ht_##name *ht, const key_t key, val_t *val)         \
{                                                                             \
        size_t i, h;                                                          \
                                                                              \
        h = hash(key) & (ht->cap - 1);                                        \
        for (i = h; ht->arr[i].state != NONE; i = (i + 1) % ht->cap) {        \
                if (cmp(key, ht->arr[i].key) == 0)                            \
                        break;                                                \
                if (i + 1 == h)                                               \
                        return -1;                                            \
        }                                                                     \
                                                                              \
        *val = ht->arr[i].val;                                                \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
ht_##name##_remove(struct ht_##name *ht, const key_t key, val_t *val)         \
{                                                                             \
        size_t i, h;                                                          \
                                                                              \
        if (ht->len < ht->cap / 2)                                            \
                if (ht_##name##_resize(ht, ht->len))                          \
                        return -1;                                            \
                                                                              \
        h = hash(key) & (ht->cap - 1);                                        \
        for (i = h; ht->arr[i].state != NONE; i = (i + 1) % ht->cap) {        \
                if (cmp(key, ht->arr[i].key) == 0)                            \
                        break;                                                \
                if (i + 1 == h)                                               \
                        return -1;                                            \
        }                                                                     \
                                                                              \
        *val = ht->arr[i].val;                                                \
        ht->arr[i].state = TOMB;                                              \
        ht->len--;                                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
val_t *                                                                       \
ht_##name##_ptr(struct ht_##name *ht, const key_t key)                        \
{                                                                             \
        size_t i, h;                                                          \
                                                                              \
        h = hash(key) & (ht->cap - 1);                                        \
        for (i = h; ht->arr[i].state != NONE; i = (i + 1) % ht->cap) {        \
                if (cmp(key, ht->arr[i].key) == 0)                            \
                        break;                                                \
                if (i + i == h)                                               \
                        return NULL;                                          \
        }                                                                     \
                                                                              \
        return &ht->arr[i].val;                                               \
}                                                                             \
                                                                              \
int                                                                           \
ht_##name##_getnxt(struct ht_##name##_iter *iter, val_t *val)                 \
{                                                                             \
        while (iter->ht->arr[iter->nxt].state != SOME                         \
               && iter->nxt < iter->ht->cap)                                  \
                iter->nxt++;                                                  \
        if (iter->nxt < iter->ht->cap) {                                      \
                *val = iter->ht->arr[iter->nxt++].val;                        \
                return 0;                                                     \
        }                                                                     \
                                                                              \
        iter->nxt = 0;                                                        \
                                                                              \
        return -1;                                                            \
}                                                                             \
                                                                              \
void                                                                          \
ht_##name##_free(struct ht_##name *ht)                                        \
{                                                                             \
        free(ht->arr);                                                        \
        ht->arr = NULL;                                                       \
        ht->cap = ht->len = 0;                                                \
}                                                                             \
                                                                              \
struct ht_##name##_semi { char _; /* to enforce semicolon */ }

#define FOR_EACH(name, i, ht) while (!ht_##name##_getnxt(&iter, &i))

#define INIT_HT(name, key_t, val_t, hash, cmp, malloc, free)                  \
INIT_HT_TYPE(name, key_t, val_t);                                             \
INIT_HT_FUNC(name, key_t, val_t, hash, cmp, malloc, free)

/* FNV-1a hash function for string */
static size_t
hash_str_64(const char *str)
{
        size_t h;

        h = FNV1_64_BASIS;
        for (; *str; str++) {
                h ^= *str;
                h *= FNV1_64_PRIME;
        }

        return h;
}

static size_t
hash_str_32(const char *str)
{
        size_t h;

        h = FNV1_32_BASIS;
        for (; *str; str++) {
                h ^= *str;
                h *= FNV1_32_PRIME;
        }

        return h;
}

size_t
hash_str(const char *str)
{
        /* compiler would optimize it */
        if (sizeof(size_t) == 8)
                return hash_str_64(str);
        if (sizeof(size_t) == 4)
                return hash_str_32(str);

        /* unreachable unless cpu is neither 64 nor 32 bit */
        return 0;
}

#endif
