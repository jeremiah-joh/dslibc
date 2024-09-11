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

#ifndef _HT_H
#define _HT_H

#include <stddef.h>
#include <string.h>

#define NEXT(i, c) (((i) + 1) % (c))

#define INIT_HT_TYPE(name, type)                                               \
struct ht_##name##_node {                                                      \
	type val;                                                              \
	enum { NONE = 0, SOME, TOMB } state;                                   \
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
size_t ht_##name##_length(struct ht_##name *);                                 \
size_t ht_##name##_sizeof(struct ht_##name *);                                 \
void ht_##name##_free(struct ht_##name *);                                     \
                                                                               \
struct ht_##name##_iter ht_##name##_iter(struct ht_##name *);                  \
int ht_##name##_next(struct ht_##name##_iter *, type *);

#define INIT_HT_FUNC(name, type, hash, cmp, malloc, free)                      \
static struct ht_##name                                                        \
ht_##name##_size(const size_t len)                                             \
{                                                                              \
	struct ht_##name ht;                                                   \
                                                                               \
	for (ht.cap = 4; ht.cap < len; ht.cap <<= 1)                           \
		;                                                              \
                                                                               \
	ht.arr = malloc(ht.cap * sizeof(struct ht_##name##_node));             \
	ht.len = 0;                                                            \
                                                                               \
	return ht;                                                             \
}                                                                              \
                                                                               \
static size_t                                                                  \
ht_##name##_empty(struct ht_##name *ht, const type val)                        \
{                                                                              \
	size_t h, i;                                                           \
                                                                               \
	h = hash(val) & (ht->cap - 1);                                         \
	for (i = h; NEXT(i, ht->cap) != h; i = NEXT(i, ht->cap)) {             \
		if (ht->arr[i].state != SOME)                                  \
			return i;                                              \
		if (cmp(val, ht->arr[i].val) == 0)                             \
			break;                                                 \
	}                                                                      \
                                                                               \
	return ht->cap;                                                        \
}                                                                              \
                                                                               \
static size_t                                                                  \
ht_##name##_match(struct ht_##name *ht, const type val)                        \
{                                                                              \
	size_t h, i;                                                           \
                                                                               \
	h = hash(val) & (ht->cap - 1);                                         \
	for (i = h; NEXT(i, ht->cap) != h; i = NEXT(i, ht->cap)) {             \
		if (ht->arr[i].state == NONE)                                  \
			break;                                                 \
		if (ht->arr[i].state == TOMB)                                  \
			continue;                                              \
		if (cmp(val, ht->arr[i].val) == 0)                             \
			return i;                                              \
	}                                                                      \
                                                                               \
	return ht->cap;                                                        \
}                                                                              \
                                                                               \
static int                                                                     \
ht_##name##_resize(struct ht_##name *ht, const size_t len)                     \
{                                                                              \
	struct ht_##name new;                                                  \
	size_t i, j;                                                           \
                                                                               \
	if (ht->cap >> 2 < ht->len && ht->len < ht->cap >> 1)                  \
		return 0;                                                      \
	for (new = ht_##name##_size(len), i = 0; i < ht->cap; i++) {           \
		if (ht->arr[i].state != SOME)                                  \
			continue;                                              \
		if ((j = ht_##name##_empty(&new, ht->arr[i].val)) == new.cap)  \
			return -1;                                             \
		                                                               \
		new.arr[j].val = ht->arr[i].val;                               \
		new.arr[j].state = SOME;                                       \
		new.len++;                                                     \
	}                                                                      \
                                                                               \
	free(ht->arr);                                                         \
	*ht = new;                                                             \
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
	size_t i, j;                                                           \
                                                                               \
	ht = ht_##name##_size(len);                                            \
                                                                               \
	for (i = 0; i < len; i++) {                                            \
		if ((j = ht_##name##_empty(&ht, arr[i])) == ht.cap)            \
			break;                                                 \
	                                                                       \
		ht.arr[j].val = arr[i];                                        \
		ht.arr[j].state = SOME;                                        \
		ht.len++;                                                      \
	}                                                                      \
                                                                               \
	return ht;                                                             \
}                                                                              \
                                                                               \
struct ht_##name                                                               \
ht_##name##_copy(const struct ht_##name *ht)                                   \
{                                                                              \
	struct ht_##name cp;                                                   \
	size_t i, j;                                                           \
                                                                               \
	cp = ht_##name##_size(ht->len);                                        \
                                                                               \
	for (i = 0; i < ht->len; i++) {                                        \
		if (ht->arr[i].state != SOME)                                  \
			continue;                                              \
		if ((j = ht_##name##_empty(&cp, ht->arr[i].val)) == cp.cap)    \
			break;                                                 \
	                                                                       \
		cp.arr[j].val = ht->arr[i].val;                                \
		cp.arr[j].state = SOME;                                        \
		cp.len++;                                                      \
	}                                                                      \
                                                                               \
	return cp;                                                             \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_get(struct ht_##name *ht, type *val)                               \
{                                                                              \
	size_t i;                                                              \
                                                                               \
	if (ht->arr == NULL || ht->cap == 0 || ht->len == 0)                   \
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
	size_t i;                                                              \
                                                                               \
	if (ht->arr == NULL)                                                   \
		return -1;                                                     \
	if (ht_##name##_resize(ht, ht->len + 1))                               \
		return -1;                                                     \
	if ((i = ht_##name##_empty(ht, val)) == ht->cap)                       \
		return -1;                                                     \
	                                                                       \
	ht->arr[i].val = val;                                                  \
	ht->arr[i].state = SOME;                                               \
	ht->len++;                                                             \
                                                                               \
	return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
ht_##name##_remove(struct ht_##name *ht, type *val)                            \
{                                                                              \
	size_t i;                                                              \
                                                                               \
	if (ht->arr == NULL || ht->cap == 0 || ht->len == 0)                   \
		return -1;                                                     \
	if ((i = ht_##name##_match(ht, *val)) == ht->cap)                      \
		return -1;                                                     \
                                                                               \
	*val = ht->arr[i].val;                                                 \
	ht->arr[i].state =TOMB;                                                \
	ht->len--;                                                             \
                                                                               \
	return ht_##name##_resize(ht, ht->len);                                \
}                                                                              \
                                                                               \
size_t                                                                         \
ht_##name##_length(struct ht_##name *ht)                                       \
{                                                                              \
	return ht->len;                                                        \
}                                                                              \
                                                                               \
size_t                                                                         \
ht_##name##_sizeof(struct ht_##name *ht)                                       \
{                                                                              \
	return ht->len * sizeof(type) + sizeof(*ht);                           \
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
			*val = iter->ht->arr[iter->idx++].val;                 \
			return 0;                                              \
		}                                                              \
	}                                                                      \
                                                                               \
	return -1;                                                             \
}

#define FOR_EACH_HT(name, elem, iter) while (!ht_##name##_next(&iter, &elem))

#define INIT_HT_BOTH(name, type, hash, cmp, malloc, free)                      \
INIT_HT_TYPE(name, type)                                                       \
INIT_HT_FUNC(name, type, hash, cmp, malloc, free)

#endif
