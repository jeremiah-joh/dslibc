/*
 * Copyright (C) 2024 Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * This file is part of dslibc.
 *
 * dslibc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dslibc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _HT_H
#define _HT_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define INIT_LEN 16
#define KEY_LEN 16
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

#define INIT_HASH_MAP(name, type)                                             \
struct hash_##name##_map_node {                                               \
    type key;                                                                 \
    type val;                                                                 \
    struct hash_##name##_map_node *next;                                      \
};                                                                            \
                                                                              \
struct map_sll {                                                              \
    struct hash_##name##_map_node *head;                                      \
    struct hash_##name##_map_node *tail;                                      \
    size_t len;                                                               \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct map_sll *sll;                                                      \
    size_t sll_len;                                                           \
    size_t len;                                                               \
    char key[KEY_LEN];                                                        \
} hash_##name##_map;                                                          \
                                                                              \
int hash_##name##_map_insert(hash_##name##_map *, const type, const type);    \
                                                                              \
static int                                                                    \
map_sll_push_back(struct map_sll *sll, const type key, const type val)        \
{                                                                             \
    if (sll->head == NULL) {                                                  \
        sll->head = sll->tail = malloc(sizeof(struct hash_##name##_map_node));\
        sll->head->key = key;                                                 \
        sll->head->val = val;                                                 \
        sll->head->next = NULL;                                               \
    } else {                                                                  \
        sll->tail->next = malloc(sizeof(struct hash_##name##_map_node));      \
        sll->tail->next->key = key;                                           \
        sll->tail->next->val = val;                                           \
        sll->tail->next->next = NULL;                                         \
        sll->tail = sll->tail->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
map_sll_remove(struct map_sll *sll, const type key, type *val)                \
{                                                                             \
    struct hash_##name##_map_node *tmp, *tmp_p = NULL;                        \
    for (tmp = sll->head; tmp != NULL; tmp = tmp->next) {                     \
        if (tmp->key == key) {                                                \
            struct hash_##name##_map_node *rmv = tmp;                         \
            *val = rmv->val;                                                  \
            if (tmp_p != NULL)                                                \
                tmp_p->next = rmv->next;                                      \
            else                                                              \
                sll->head->next = rmv->next;                                  \
            FREE(rmv);                                                        \
                                                                              \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        tmp_p = tmp;                                                          \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
static int                                                                    \
hash_##name##_map_resize(hash_##name##_map *map, size_t new_size)             \
{                                                                             \
    struct map_sll *old = map->sll;                                           \
    size_t old_size = map->sll_len;                                           \
    map->sll_len = new_size;                                                  \
    map->sll = malloc(sizeof(struct map_sll) * map->sll_len);                 \
    for (size_t i = 0; i < map->sll_len; i++)                                 \
        map->sll[i].head = map->sll[i].tail = NULL;                           \
    map->len = 0;                                                             \
                                                                              \
    struct hash_##name##_map_node *node;                                      \
    for (size_t i = 0; i < old_size; i++)                                     \
        for (node = old[i].head; node != NULL; node = node->next)             \
            if (hash_##name##_map_insert(map, node->key, node->val))          \
                return -1;                                                    \
    FREE(old);                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
hash_##name##_map                                                             \
hash_##name##_map_new()                                                       \
{                                                                             \
    hash_##name##_map map;                                                    \
    map.sll = malloc(sizeof(struct map_sll) * INIT_LEN);                      \
    for (size_t i = 0; i < INIT_LEN; i++)                                     \
        map.sll[i].head = map.sll[i].tail = NULL;                             \
    map.sll_len = INIT_LEN;                                                   \
    map.len = 0;                                                              \
    memset(map.key, 0, sizeof(map.key)); /* DEBUG, shall not be used */       \
                                                                              \
    return map;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_map_insert(hash_##name##_map *map,                              \
                         const type key, const type val)                      \
{                                                                             \
    if (map->sll_len < map->len)                                              \
        return -1;                                                            \
    if (map->sll_len == map->len)                                             \
        hash_##name##_map_resize(map, map->sll_len * 2);                      \
                                                                              \
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;       \
    if (map_sll_push_back(&map->sll[idx], key, val))                          \
        return -1;                                                            \
                                                                              \
    map->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_map_remove(hash_##name##_map *map, const type key, type *val)   \
{                                                                             \
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;       \
    if (map_sll_remove(&map->sll[idx], key, val))                             \
        return -1;                                                            \
                                                                              \
    map->len--;                                                               \
                                                                              \
    if (map->len > INIT_LEN * 2 && map->sll_len / 3 >= map->len)              \
        if (hash_##name##_map_resize(map, map->sll_len / 2))                  \
            return -1;                                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_map_search(hash_##name##_map *map, const type key, type *val)   \
{                                                                             \
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;       \
    struct hash_##name##_map_node *tmp;                                       \
    for (tmp = map->sll[idx].head; tmp != NULL; tmp = tmp->next) {            \
        if (tmp->key == key) {                                                \
            *val = tmp->val;                                                  \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
void                                                                          \
hash_##name##_map_free(hash_##name##_map map)                                 \
{                                                                             \
    FREE(map.sll);                                                            \
}

#define INIT_HASH_SET(name, type)                                             \
struct hash_##name##_set_node {                                               \
    type key;                                                                 \
    struct hash_##name##_set_node *next;                                      \
};                                                                            \
                                                                              \
struct set_sll {                                                              \
    struct hash_##name##_set_node *head;                                      \
    struct hash_##name##_set_node *tail;                                      \
    size_t len;                                                               \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct set_sll *sll;                                                      \
    size_t sll_len;                                                           \
    size_t len;                                                               \
    char key[KEY_LEN];                                                        \
} hash_##name##_set;                                                          \
                                                                              \
int hash_##name##_set_insert(hash_##name##_set *, const type);                \
                                                                              \
static int                                                                    \
set_sll_push_back(struct set_sll *sll, const type key)                        \
{                                                                             \
    if (sll->head == NULL) {                                                  \
        sll->head = sll->tail = malloc(sizeof(struct hash_##name##_set_node));\
        sll->head->key = key;                                                 \
        sll->head->next = NULL;                                               \
    } else {                                                                  \
        sll->tail->next = malloc(sizeof(struct hash_##name##_set_node));      \
        sll->tail->next->key = key;                                           \
        sll->tail->next->next = NULL;                                         \
        sll->tail = sll->tail->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
set_sll_remove(struct set_sll *sll, const type key)                           \
{                                                                             \
    struct hash_##name##_set_node *tmp, *tmp_p = NULL;                        \
    for (tmp = sll->head; tmp != NULL; tmp = tmp->next) {                     \
        if (tmp->key == key) {                                                \
            struct hash_##name##_set_node *rmv = tmp;                         \
            if (tmp_p != NULL)                                                \
                tmp_p->next = rmv->next;                                      \
            else                                                              \
                sll->head->next = rmv->next;                                  \
            FREE(rmv);                                                        \
                                                                              \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        tmp_p = tmp;                                                          \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
static int                                                                    \
hash_##name##_set_resize(hash_##name##_set *set, size_t new_size)             \
{                                                                             \
    struct set_sll *old = set->sll;                                           \
    size_t old_size = set->sll_len;                                           \
    set->sll_len = new_size;                                                  \
    set->sll = malloc(sizeof(struct set_sll) * set->sll_len);                 \
    for (size_t i = 0; i < set->sll_len; i++)                                 \
        set->sll[i].head = set->sll[i].tail = NULL;                           \
    set->len = 0;                                                             \
                                                                              \
    struct hash_##name##_set_node *node;                                      \
    for (size_t i = 0; i < old_size; i++)                                     \
        for (node = old[i].head; node != NULL; node = node->next)             \
            if (hash_##name##_set_insert(set, node->key))                     \
                return -1;                                                    \
    FREE(old);                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
hash_##name##_set                                                             \
hash_##name##_set_new()                                                       \
{                                                                             \
    hash_##name##_set set;                                                    \
    set.sll = malloc(sizeof(struct set_sll) * INIT_LEN);                      \
    for (size_t i = 0; i < INIT_LEN; i++)                                     \
        set.sll[i].head = set.sll[i].tail = NULL;                             \
    set.sll_len = INIT_LEN;                                                   \
    set.len = 0;                                                              \
    memset(set.key, 0, sizeof(set.key)); /* DEBUG, shall not be used */       \
                                                                              \
    return set;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_set_insert(hash_##name##_set *set, const type key)              \
{                                                                             \
    if (set->sll_len < set->len)                                              \
        return -1;                                                            \
    if (set->sll_len == set->len)                                             \
        hash_##name##_set_resize(set, set->sll_len * 2);                      \
                                                                              \
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;       \
    if (set_sll_push_back(&set->sll[idx], key))                               \
        return -1;                                                            \
                                                                              \
    set->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_set_remove(hash_##name##_set *set, const type key)              \
{                                                                             \
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;       \
    if (set_sll_remove(&set->sll[idx], key))                                  \
        return -1;                                                            \
                                                                              \
    set->len--;                                                               \
                                                                              \
    if (set->len > INIT_LEN * 2 && set->sll_len / 3 >= set->len)              \
        if (hash_##name##_set_resize(set, set->sll_len / 2))                  \
            return -1;                                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
hash_##name##_set_search(hash_##name##_set *set, const type key)              \
{                                                                             \
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;       \
    struct hash_##name##_set_node *tmp;                                       \
    for (tmp = set->sll[idx].head; tmp != NULL; tmp = tmp->next) {            \
        if (tmp->key == key) {                                                \
            return 1;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
void                                                                          \
hash_##name##_set_free(hash_##name##_set set)                                 \
{                                                                             \
    FREE(set.sll);                                                            \
}

/* <MIT License>
 Copyright (c) 2013  Marek Majkowski <marek@popcount.org>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 </MIT License>

 Original location:
    https://github.com/majek/csiphash/

 Solution inspired by code from:
    Samuel Neves (supercop/crypto_auth/siphash24/little)
    djb (supercop/crypto_auth/siphash24/little2)
    Jean-Philippe Aumasson (https://131002.net/siphash/siphash24.c)
*/

#include <stdint.h>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
	__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define _le64toh(x) ((uint64_t)(x))
#elif defined(_WIN32)
/* Windows is always little endian, unless you're on xbox360
   http://msdn.microsoft.com/en-us/library/b0084kay(v=vs.80).aspx */
#  define _le64toh(x) ((uint64_t)(x))
#elif defined(__APPLE__)
#  include <libkern/OSByteOrder.h>
#  define _le64toh(x) OSSwapLittleToHostInt64(x)
#else

/* See: http://sourceforge.net/p/predef/wiki/Endianness/ */
#  if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#    include <sys/endian.h>
#  else
#    include <endian.h>
#  endif
#  if defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && \
	__BYTE_ORDER == __LITTLE_ENDIAN
#    define _le64toh(x) ((uint64_t)(x))
#  else
#    define _le64toh(x) le64toh(x)
#  endif

#endif


#define ROTATE(x, b) (uint64_t)( ((x) << (b)) | ( (x) >> (64 - (b))) )

#define HALF_ROUND(a,b,c,d,s,t)		\
	a += b; c += d;				    \
	b = ROTATE(b, s) ^ a;			\
	d = ROTATE(d, t) ^ c;			\
	a = ROTATE(a, 32);

#define DOUBLE_ROUND(v0,v1,v2,v3)		\
	HALF_ROUND(v0,v1,v2,v3,13,16);		\
	HALF_ROUND(v2,v1,v0,v3,17,21);		\
	HALF_ROUND(v0,v1,v2,v3,13,16);		\
	HALF_ROUND(v2,v1,v0,v3,17,21);


static uint64_t
siphash24(const void *src, unsigned long src_sz, const char key[16])
{
	const uint64_t *_key = (uint64_t *)key;
	uint64_t k0 = _le64toh(_key[0]);
	uint64_t k1 = _le64toh(_key[1]);
	uint64_t b = (uint64_t)src_sz << 56;
	const uint64_t *in = (uint64_t*)src;

	uint64_t v0 = k0 ^ 0x736f6d6570736575ULL;
	uint64_t v1 = k1 ^ 0x646f72616e646f6dULL;
	uint64_t v2 = k0 ^ 0x6c7967656e657261ULL;
	uint64_t v3 = k1 ^ 0x7465646279746573ULL;

	while (src_sz >= 8) {
		uint64_t mi = _le64toh(*in);
		in += 1; src_sz -= 8;
		v3 ^= mi;
		DOUBLE_ROUND(v0,v1,v2,v3);
		v0 ^= mi;
	}

	uint64_t t = 0; uint8_t *pt = (uint8_t *)&t; uint8_t *m = (uint8_t *)in;
	switch (src_sz) {
	case 7: pt[6] = m[6];
	case 6: pt[5] = m[5];
	case 5: pt[4] = m[4];
	case 4: *((uint32_t*)&pt[0]) = *((uint32_t*)&m[0]); break;
	case 3: pt[2] = m[2];
	case 2: pt[1] = m[1];
	case 1: pt[0] = m[0];
	}
	b |= _le64toh(t);

	v3 ^= b;
	DOUBLE_ROUND(v0,v1,v2,v3);
	v0 ^= b; v2 ^= 0xff;
	DOUBLE_ROUND(v0,v1,v2,v3);
	DOUBLE_ROUND(v0,v1,v2,v3);
	return (v0 ^ v1) ^ (v2 ^ v3);
}

#endif
