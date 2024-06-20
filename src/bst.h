/*
 * dslibc - collection of useful data structures written in ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _BST_H
#define _BST_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_BST_TYPE(name, key_t, val_t)                                     \
struct bst_##name##_node {                                                    \
        key_t key;                                                            \
        val_t val;                                                            \
        struct bst_##name##_node *lch, *rch;                                  \
};                                                                            \
                                                                              \
struct bst_##name {                                                           \
        struct bst_##name##_node *root;                                       \
        size_t len;                                                           \
};                                                                            \
                                                                              \
struct bst_##name bst_##name##_new();                                         \
struct bst_##name bst_##name##_copy(const struct bst_##name);                 \
struct bst_##name bst_##name##_from(const key_t [], const val_t [],           \
                                    const size_t);                            \
int bst_##name##_insert(struct bst_##name *, const key_t, const val_t);       \
int bst_##name##_search(struct bst_##name *, const key_t, val_t *);           \
int bst_##name##_remove(struct bst_##name *, const key_t, val_t *);           \
int bst_##name##_retain(struct bst_##name *, int (*)(val_t));                 \
val_t *bst_##name##_ptr(struct bst_##name *, const key_t);                    \
val_t *bst_##name##_root(struct bst_##name *);                                \
val_t *bst_##name##_max(struct bst_##name *);                                 \
val_t *bst_##name##_min(struct bst_##name *);                                 \
void bst_##name##_foreach(struct bst_##name *, void (*)(val_t *));            \
void bst_##name##_free(struct bst_##name *) /* to enforce semicolon */

#define INIT_BST_FUNC(name, key_t, val_t, cmp)                                \
static struct bst_##name##_node *                                             \
bst_##name##_new_node(const key_t key, const val_t val)                       \
{                                                                             \
        struct bst_##name##_node *new;                                        \
        if ((new = malloc(sizeof(struct bst_##name##_node))) == NULL)         \
                return NULL;                                                  \
                                                                              \
        new->key = key;                                                       \
        new->val = val;                                                       \
        new->lch = new->rch = NULL;                                           \
                                                                              \
        return new;                                                           \
}                                                                             \
                                                                              \
static int                                                                    \
bst_##name##_get(struct bst_##name##_node **par,                              \
                 struct bst_##name##_node **cur,                              \
                 const key_t key)                                             \
{                                                                             \
        int res;                                                              \
                                                                              \
        for (*cur = *par; *cur != NULL; ) {                                   \
                *par = *cur;                                                  \
                res = cmp(key, (*cur)->key);                                  \
                if (res < 0)                                                  \
                        *cur = (*cur)->lch;                                   \
                else if (res > 0)                                             \
                        *cur = (*cur)->rch;                                   \
                else                                                          \
                        return res;                                           \
        }                                                                     \
                                                                              \
        return res;                                                           \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_copy_node(struct bst_##name *cpy, struct bst_##name##_node *node)\
{                                                                             \
        bst_##name##_insert(cpy, node->key, node->val);                       \
                                                                              \
        if (node->lch != NULL)                                                \
                bst_##name##_copy_node(cpy, node->lch);                       \
        if (node->rch != NULL)                                                \
                bst_##name##_copy_node(cpy, node->rch);                       \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_free_node(struct bst_##name##_node *node)                        \
{                                                                             \
        if (node->lch != NULL)                                                \
                bst_##name##_free_node(node->lch);                            \
        if (node->rch != NULL)                                                \
                bst_##name##_free_node(node->rch);                            \
                                                                              \
        free(node);                                                           \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_rmv1(struct bst_##name##_node **tmp)                             \
{                                                                             \
        struct bst_##name##_node *suc;                                        \
                                                                              \
        for (suc = (*tmp)->rch; suc->lch; suc = suc->lch)                     \
                ;                                                             \
                                                                              \
        (*tmp)->key = suc->key;                                               \
        (*tmp)->val = suc->val;                                               \
                                                                              \
        *tmp = suc;                                                           \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_rmv2(struct bst_##name##_node *par,                              \
                  struct bst_##name##_node *tmp)                              \
{                                                                             \
        if (par->lch == tmp)                                                  \
                par->lch = NULL;                                              \
        else                                                                  \
                par->rch = NULL;                                              \
                                                                              \
        free(tmp);                                                            \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_rmv3(struct bst_##name##_node *par,                              \
                  struct bst_##name##_node *tmp)                              \
{                                                                             \
        if (par->lch == tmp)                                                  \
                par->lch = tmp->lch ? tmp->lch : tmp->rch;                    \
        else                                                                  \
                par->rch = tmp->rch ? tmp->rch : tmp->lch;                    \
                                                                              \
        free(tmp);                                                            \
}                                                                             \
                                                                              \
static int                                                                    \
bst_##name##_retain_rec(struct bst_##name *bst,                               \
                        struct bst_##name##_node *cur,                        \
                        int (*fn)(val_t))                                     \
{                                                                             \
	if (fn(cur->val))                                                     \
		if (bst_##name##_insert(bst, cur->key, cur->val))             \
			return -1;                                            \
                                                                              \
	if (cur->lch)                                                         \
		if (bst_##name##_retain_rec(bst, cur->lch, fn))               \
			return -1;                                            \
	if (cur->rch)                                                         \
		if (bst_##name##_retain_rec(bst, cur->rch, fn))               \
			return -1;                                            \
	                                                                      \
	return 0;                                                             \
}                                                                             \
                                                                              \
static void                                                                   \
bst_##name##_foreach_rec(struct bst_##name *bst,                              \
                         struct bst_##name##_node *cur,                       \
			 void (*fn)(val_t *))                                 \
{                                                                             \
	fn(&cur->val);                                                        \
                                                                              \
	if (cur->lch)                                                         \
		bst_##name##_foreach_rec(bst, cur->lch, fn);                  \
	if (cur->rch)                                                         \
		bst_##name##_foreach_rec(bst, cur->rch, fn);                  \
}                                                                             \
                                                                              \
struct bst_##name                                                             \
bst_##name##_new()                                                            \
{                                                                             \
        struct bst_##name bst = { NULL, 0 };                                  \
        return bst;                                                           \
}                                                                             \
                                                                              \
struct bst_##name                                                             \
bst_##name##_copy(const struct bst_##name bst)                                \
{                                                                             \
        struct bst_##name cpy;                                                \
                                                                              \
        cpy = bst_##name##_new();                                             \
        bst_##name##_copy_node(&cpy, bst.root);                               \
                                                                              \
        return cpy;                                                           \
}                                                                             \
                                                                              \
struct bst_##name                                                             \
bst_##name##_from(const key_t key[], const val_t val[],                       \
                  const size_t len)                                           \
{                                                                             \
        size_t i;                                                             \
        struct bst_##name bst = { NULL, 0 };                                  \
                                                                              \
        for (i = 0; i < len; i++)                                             \
                bst_##name##_insert(&bst, key[i], val[i]);                    \
                                                                              \
        return bst;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_insert(struct bst_##name *bst, const key_t key, const val_t val) \
{                                                                             \
        int res;                                                              \
        struct bst_##name##_node *tmp, *par;                                  \
                                                                              \
        if (bst->root == NULL || bst->len == 0) {                             \
                bst->root = bst_##name##_new_node(key, val);                  \
        } else {                                                              \
                par = bst->root;                                              \
                if ((res = bst_##name##_get(&par, &tmp, key)) == 0)           \
                        return -1;                                            \
                                                                              \
                if (res < 0)                                                  \
                        par->lch = bst_##name##_new_node(key, val);           \
                else                                                          \
                        par->rch = bst_##name##_new_node(key, val);           \
        }                                                                     \
                                                                              \
        bst->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_search(struct bst_##name *bst, const key_t key, val_t *val)      \
{                                                                             \
        struct bst_##name##_node *tmp, *par;                                  \
                                                                              \
        par = bst->root;                                                      \
        if (bst_##name##_get(&par, &tmp, key) != 0)                           \
                return -1;                                                    \
                                                                              \
        *val = tmp->val;                                                      \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_remove(struct bst_##name *bst, const key_t key, val_t *val)      \
{                                                                             \
        struct bst_##name##_node *tmp, *par;                                  \
                                                                              \
        par = bst->root;                                                      \
        if (bst_##name##_get(&par, &tmp, key) != 0)                           \
                return -1;                                                    \
                                                                              \
        *val = tmp->val;                                                      \
                                                                              \
        if (tmp->lch && tmp->rch)                                             \
                bst_##name##_rmv1(&tmp);                                      \
        if (tmp->lch == NULL && tmp->rch == NULL)                             \
                bst_##name##_rmv2(par, tmp);                                  \
        else                                                                  \
                bst_##name##_rmv3(par, tmp);                                  \
                                                                              \
        bst->len--;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_retain(struct bst_##name *bst, int (*fn)(val_t))                 \
{                                                                             \
	struct bst_##name cpy;                                                \
                                                                              \
	cpy = bst_##name##_new();                                             \
                                                                              \
	if (bst_##name##_retain_rec(&cpy, bst->root, fn))                     \
		return -1;                                                    \
                                                                              \
	bst_##name##_free(bst);                                               \
	*bst = cpy;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
val_t *                                                                       \
bst_##name##_ptr(struct bst_##name *bst, const key_t key)                     \
{                                                                             \
        struct bst_##name##_node *par, *tmp;                                  \
                                                                              \
        par = bst->root;                                                      \
                                                                              \
        if (bst_##name##_get(&par, &tmp, key) != 0)                           \
                return NULL;                                                  \
                                                                              \
        return &tmp->val;                                                     \
}                                                                             \
                                                                              \
val_t *                                                                       \
bst_##name##_root(struct bst_##name *bst)                                     \
{                                                                             \
        return &bst->root->val;                                               \
}                                                                             \
                                                                              \
val_t *                                                                       \
bst_##name##_max(struct bst_##name *bst)                                      \
{                                                                             \
        struct bst_##name##_node *max;                                        \
                                                                              \
        for (max = bst->root; max->rch != NULL; max = max->rch)               \
                ;                                                             \
                                                                              \
        return &max->val;                                                     \
}                                                                             \
                                                                              \
val_t *                                                                       \
bst_##name##_min(struct bst_##name *bst)                                      \
{                                                                             \
        struct bst_##name##_node *min;                                        \
                                                                              \
        for (min = bst->root; min->lch != NULL; min = min->lch)               \
                ;                                                             \
                                                                              \
        return &min->val;                                                     \
}                                                                             \
                                                                              \
void                                                                          \
bst_##name##_foreach(struct bst_##name *bst, void (*fn)(val_t *))             \
{                                                                             \
	bst_##name##_foreach_rec(bst, bst->root, fn);                         \
}                                                                             \
                                                                              \
void                                                                          \
bst_##name##_free(struct bst_##name *bst)                                     \
{                                                                             \
        bst_##name##_free_node(bst->root);                                    \
        bst->root = NULL;                                                     \
        bst->len = 0;                                                         \
}                                                                             \
                                                                              \
struct bst_##name##_semi { /* to enforce semicolon */ }

#define INIT_BST(name, key_t, val_t, cmp)                                     \
INIT_BST_TYPE(name, key_t, val_t);                                            \
INIT_BST_FUNC(name, key_t, val_t, cmp)

#endif
