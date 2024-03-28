#ifndef _SLL_H
#define _SLL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_SLL_HEAD(name, type)                                             \
struct sll_##name##_node {                                                    \
	type val;                                                             \
	struct sll_##name##_node *nxt;                                        \
};                                                                            \
                                                                              \
struct sll_##name {                                                           \
	struct sll_##name##_node *head, *tail;                                \
	size_t len;                                                           \
} /* to enforce semicolon */

#define INIT_SLL_FUNC(name, type)                                             \
static struct sll_##name##_node *                                             \
sll_##name##_new_node(const type val)                                         \
{                                                                             \
	struct sll_##name##_node *new;                                        \
	if ((new = malloc(sizeof(struct sll_##name##_node))) == NULL)         \
		return NULL;                                                  \
	new->val = val;                                                       \
	new->nxt = NULL;                                                      \
                                                                              \
	return new;                                                           \
}                                                                             \
                                                                              \
struct sll_##name                                                             \
sll_##name##_new()                                                            \
{                                                                             \
	struct sll_##name sll = { NULL, NULL, 0 };                            \
	return sll;                                                           \
}                                                                             \
                                                                              \
struct sll_##name                                                             \
sll_##name##_from(const type *arr, const size_t len)                          \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name sll = { NULL, NULL, len };                          \
                                                                              \
	sll.head = sll.tail = sll_##name##_new_node(arr[0]);                  \
                                                                              \
	for (i = 1; i < len; i++)                                             \
		sll.tail = sll.tail->nxt = sll_##name##_new_node(arr[i]);     \
                                                                              \
	return sll;                                                           \
}                                                                             \
                                                                              \
struct sll_##name                                                             \
sll_##name##_copy(const struct sll_##name sll)                                \
{                                                                             \
	struct sll_##name cpy;                                                \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	cpy.head = cpy.tail = sll_##name##_new_node(sll.head->val);           \
                                                                              \
	for (tmp = sll.head->nxt; tmp != NULL; tmp = tmp->nxt)                \
		cpy.tail = cpy.tail->nxt = sll_##name##_new_node(tmp->val);   \
                                                                              \
	cpy.len = sll.len;                                                    \
                                                                              \
	return cpy;                                                           \
}                                                                             \
                                                                              \
struct sll_##name                                                             \
sll_##name##_slice(const struct sll_##name sll,                               \
                   const size_t head, const size_t tail)                      \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name sli;                                                \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	if (tail - 1 <= head)                                                 \
		return sll_##name##_new();                                    \
                                                                              \
	tmp = sll.head;                                                       \
	i = 0;                                                                \
	for (; i < head; i++)                                                 \
		tmp = tmp->nxt;                                               \
                                                                              \
	sli.head = sli.tail = sll_##name##_new_node(tmp->val);                \
                                                                              \
	for (; i < tail; i++) {                                               \
		tmp = tmp->nxt;                                               \
		sli.tail = sli.tail->nxt = sll_##name##_new_node(tmp->val);   \
	}                                                                     \
                                                                              \
	sli.len = tail - head;                                                \
                                                                              \
	return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_push(struct sll_##name *sll, const type val)                     \
{                                                                             \
	if (sll->head == NULL) {                                              \
		sll->head = sll->tail = sll_##name##_new_node(val);           \
		sll->len = 1;                                                 \
		return sll->head ? 0 : -1;                                    \
	}                                                                     \
                                                                              \
	sll->tail = sll->tail->nxt = sll_##name##_new_node(val);              \
	if (sll->tail == NULL)                                                \
		return -1;                                                    \
                                                                              \
	sll->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_pop(struct sll_##name *sll, type *val)                           \
{                                                                             \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	if (sll->head == NULL)                                                \
		return -1;                                                    \
	                                                                      \
	*val = sll->tail->val;                                                \
	for (tmp = sll->head; tmp->nxt == sll->tail; tmp = tmp->nxt)          \
		;                                                             \
                                                                              \
	free(sll->tail);                                                      \
	sll->tail = tmp;                                                      \
                                                                              \
	sll->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_append(struct sll_##name *des, const struct sll_##name src)      \
{                                                                             \
	struct sll_##name new;                                                \
                                                                              \
	if (des->head == NULL && src.head == NULL)                            \
		return -1;                                                    \
	if (src.head == NULL)                                                 \
		return 0;                                                     \
	if (des->head == NULL) {                                              \
		*des = src;                                                   \
		return 0;                                                     \
	}                                                                     \
                                                                              \
	new = sll_##name##_copy(src);                                         \
	des->tail->nxt = new.head;                                            \
	des->tail = new.tail;                                                 \
                                                                              \
	des->len += new.len;                                                  \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_insert(struct sll_##name *sll, const type val, const size_t idx) \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *tmp, *new;                                  \
                                                                              \
	tmp = sll->head;                                                      \
	for (i = 0; i < idx - 1; i++) {                                       \
		if (tmp == NULL)                                              \
			return -1;                                            \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	new = sll_##name##_new_node(val);                                     \
	tmp->nxt = new;                                                       \
	new->nxt = tmp->nxt;                                                  \
                                                                              \
	sll->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
size_t                                                                        \
sll_##name##_search(struct sll_##name *sll, const type val)                   \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	tmp = sll->head;                                                      \
	for (i = 0; tmp != NULL; i++) {                                       \
		if (tmp->val == val)                                          \
			return i;                                             \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	return sll->len;                                                      \
}                                                                             \
                                                                              \
size_t                                                                        \
sll_##name##_remove(struct sll_##name *sll, const type val)                   \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *prv, *tmp;                                  \
                                                                              \
	tmp = sll->head;                                                      \
	for (i = 0; tmp->val != val; i++) {                                   \
		if (tmp == NULL)                                              \
			return sll->len;                                      \
                                                                              \
		prv = tmp;                                                    \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	prv->nxt = tmp->nxt;                                                  \
	free(tmp);                                                            \
                                                                              \
	sll->len--;                                                           \
                                                                              \
	return i;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_getnth(struct sll_##name *sll, type *val, const size_t idx)      \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	if (sll->head == NULL)                                                \
		return -1;                                                    \
	if (sll->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	tmp = sll->head;                                                      \
	for (i = 0; i < idx; i++) {                                           \
		if (tmp == NULL)                                              \
			return -1;                                            \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	*val = tmp->val;                                                      \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_setnth(struct sll_##name *sll, const type val, const size_t idx) \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	if (sll->head == NULL)                                                \
		return -1;                                                    \
	if (sll->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	tmp = sll->head;                                                      \
	for (i = 0; i < idx; i++) {                                           \
		if (tmp == NULL)                                              \
			return -1;                                            \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	tmp->val = val;                                                       \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_rmvnth(struct sll_##name *sll, type *val, const size_t idx)      \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *prv, *tmp;                                  \
                                                                              \
	if (sll->head == NULL)                                                \
		return -1;                                                    \
	if (sll->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	tmp = sll->head;                                                      \
	for (i = 0; i < idx; i++) {                                           \
		prv = tmp;                                                    \
		if (tmp == NULL)                                              \
			return -1;                                            \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	*val = tmp->val;                                                      \
	prv->nxt = tmp->nxt;                                                  \
	free(tmp);                                                            \
                                                                              \
	sll->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
sll_##name##_getptr(struct sll_##name *sll, const size_t idx)                 \
{                                                                             \
	size_t i;                                                             \
	struct sll_##name##_node *tmp;                                        \
                                                                              \
	if (sll->head == NULL)                                                \
		return NULL;                                                  \
	if (sll->len <= idx)                                                  \
		return NULL;                                                  \
	                                                                      \
	tmp = sll->head;                                                      \
	for (i = 0; i < idx; i++) {                                           \
		if (tmp == NULL)                                              \
			return NULL;                                          \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	return &tmp->val;                                                     \
}                                                                             \
                                                                              \
type *                                                                        \
sll_##name##_head(struct sll_##name *sll)                                     \
{                                                                             \
	return &sll->head->val;                                               \
}                                                                             \
                                                                              \
type *                                                                        \
sll_##name##_tail(struct sll_##name *sll)                                     \
{                                                                             \
	return &sll->tail->val;                                               \
}                                                                             \
                                                                              \
struct sll_##name##_semi { /* to enforce semicolon */ }

#define INIT_SLL(name, type)                                                  \
INIT_SLL_HEAD(name, type);                                                    \
INIT_SLL_FUNC(name, type)

#endif
