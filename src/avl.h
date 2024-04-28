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

#ifndef _AVL_H
#define _AVL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_AVL_TYPE(name, key_t, val_t)                                     \
struct avl_##name##_node {                                                    \
	key_t key;                                                            \
	val_t val;                                                            \
	struct avl_##name##_node *par, *lch, *rch;                            \
	signed char bf;                                                       \
};                                                                            \
                                                                              \
struct avl_##name {                                                           \
	struct avl_##name##_node *root;                                       \
	size_t len;                                                           \
	int (*cmp)(key_t, key_t);                                             \
};                                                                            \
                                                                              \
struct avl_##name avl_##name##_new(int (*cmp)(key_t, key_t));                 \
struct avl_##name avl_##name##_copy(const struct avl_##name);                 \
struct avl_##name avl_##name##_from(const key_t [], const val_t [],           \
                                    const size_t, int (*cmp)(key_t, key_t));  \
int avl_##name##_insert(struct avl_##name *, const key_t, const val_t);       \
int avl_##name##_search(struct avl_##name *, const key_t, val_t *);           \
int avl_##name##_remove(struct avl_##name *, const key_t, val_t *);           \
val_t *avl_##name##_ptr(struct avl_##name *, const key_t);                    \
val_t *avl_##name##_root(struct avl_##name *);                                \
val_t *avl_##name##_max(struct avl_##name *);                                 \
val_t *avl_##name##_min(struct avl_##name *);                                 \
void avl_##name##_free(struct avl_##name *) /* to enforce semicolon */
