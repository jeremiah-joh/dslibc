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
	int (*cmp)(key_t, key_t);                                             \
} /* to enforce semicolon */

#define INIT_BST_FUNC(name, key_t, val_t)                                     \
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
bst_##name##_get_node(struct bst_##name##_node **par,                         \
                      struct bst_##name##_node **cur,                         \
		      const key_t key, int (*cmp)(key_t, key_t))              \
{                                                                             \
	int res;                                                              \
                                                                              \
	if (*par == NULL)                                                     \
		return -1;                                                    \
	                                                                      \
	for (*cur = *par; *cur != NULL; ) {                                   \
		*par = *cur;                                                  \
		res = cmp(key, (*cur)->key);                                  \
		if (res < 0)                                                  \
			*cur = (*cur)->lch;                                   \
		else if (res > 0)                                             \
			*cur = (*cur)->rch;                                   \
		else                                                          \
			return 0;                                             \
	}                                                                     \
                                                                              \
	return -1;                                                            \
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
struct bst_##name                                                             \
bst_##name##_new(int (*cmp)(key_t, key_t))                                    \
{                                                                             \
	struct bst_##name bst = { NULL, 0, cmp };                             \
	return bst;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_insert(struct bst_##name *bst, const key_t key, const val_t val) \
{                                                                             \
	int res;                                                              \
	struct bst_##name##_node **tmp;                                       \
                                                                              \
	for (tmp = &bst->root; *tmp != NULL; ) {                              \
		res = bst->cmp(key, (*tmp)->key);                             \
		if (res < 0)                                                  \
			tmp = &(*tmp)->lch;                                   \
		else if (res > 0)                                             \
			tmp = &(*tmp)->rch;                                   \
		else                                                          \
			return -1;                                            \
	}                                                                     \
                                                                              \
	if ((*tmp = bst_##name##_new_node(key, val)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	bst->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
struct bst_##name                                                             \
bst_##name##_from(const key_t key[], const val_t val[],                       \
                  const size_t len, int (*cmp)(key_t, key_t))                 \
{                                                                             \
	size_t i;                                                             \
	struct bst_##name bst = { NULL, 0, cmp };                             \
                                                                              \
	for (i = 0; i < len; i++)                                             \
		bst_##name##_insert(&bst, key[i], val[i]);                    \
                                                                              \
	return bst;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
bst_##name##_search(struct bst_##name *bst, const key_t key, val_t *val)      \
{                                                                             \
	struct bst_##name##_node *tmp, *par;                                  \
                                                                              \
	par = bst->root;                                                      \
                                                                              \
	if (bst_##name##_get_node(&par, &tmp, key, bst->cmp))                 \
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
                                                                              \
	if (bst_##name##_get_node(&par, &tmp, key, bst->cmp))                 \
		return -1;                                                    \
	                                                                      \
	*val = tmp->val;                                                      \
                                                                              \
	if (tmp == par->lch)                                                  \
		par->lch = tmp->lch ? tmp->lch : tmp->rch;                    \
	else                                                                  \
		par->rch = tmp->rch ? tmp->rch : tmp->lch;                    \
	                                                                      \
	bst->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
val_t *                                                                       \
bst_##name##_getptr(struct bst_##name *bst, const key_t key)                  \
{                                                                             \
	struct bst_##name##_node *par, *tmp;                                  \
                                                                              \
	par = bst->root;                                                      \
                                                                              \
	if (bst_##name##_get_node(&par, &tmp, key, bst->cmp))                 \
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
bst_##name##_free(struct bst_##name *bst)                                     \
{                                                                             \
	bst_##name##_free_node(bst->root);                                    \
	bst->root = NULL;                                                     \
	bst->len = 0;                                                         \
}                                                                             \
                                                                              \
struct bst_##name##_semi { /* to enforce semicolon */ }

#define INIT_BST(name, key_t, val_t)                                          \
INIT_BST_TYPE(name, key_t, val_t);                                            \
INIT_BST_FUNC(name, key_t, val_t)

#endif
