/*
 * Copyright (C) 2024 Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 * 
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _RBT_H
#define _RBT_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_RBT_TYPE(name, key_t, val_t)                                     \
struct rbt_##name##_node {                                                    \
	key_t key;                                                            \
	val_t val;                                                            \
	struct rbt_##name##_node *par, *lch, *rch;                            \
	enum { RED, BLACK } color;                                            \
};                                                                            \
                                                                              \
struct rbt_##name {                                                           \
	struct rbt_##name##_node *root;                                       \
	size_t len;                                                           \
	int (*cmp)(key_t, key_t);                                             \
};                                                                            \
                                                                              \
struct rbt_##name rbt_##name##_new(int (*cmp)(key_t, key_t));                 \
struct rbt_##name rbt_##name##_copy(const struct rbt_##name);                 \
struct rbt_##name rbt_##name##_from(const key_t [], const val_t [],           \
                                    const size_t, int (*cmp)(key_t, key_t));  \
int rbt_##name##_insert(struct rbt_##name *, const key_t, const val_t);       \
int rbt_##name##_search(struct rbt_##name *, const key_t, val_t *);           \
int rbt_##name##_remove(struct rbt_##name *, const key_t, val_t *);           \
val_t *rbt_##name##_ptr(struct rbt_##name *, const key_t);                    \
val_t *rbt_##name##_root(struct rbt_##name *);                                \
val_t *rbt_##name##_max(struct rbt_##name *);                                 \
val_t *rbt_##name##_min(struct rbt_##name *);                                 \
void rbt_##name##_free(struct rbt_##name *) /* to enforce semicolon */
