#ifndef _DLL_H
#define _DLL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_DLL_TYPE(name, type)                                             \
struct dll_##name##_node {                                                    \
	type val;                                                             \
	struct dll_##name##_node *nxt, *prv;                                  \
};                                                                            \
                                                                              \
struct dll_##name {                                                           \
	struct dll_##name##_node *head, *tail;                                \
	size_t len;                                                           \
} /* to enforce semicolon */

#define INIT_DLL_FUNC(name, type)                                             \
static struct dll_##name##_node *                                             \
dll_##name##_new_node(const type val, struct dll_##name##_node *prv)          \
{                                                                             \
	struct dll_##name##_node *new;                                        \
	if ((new = malloc(sizeof(struct dll_##name##_node))) == NULL)         \
		return NULL;                                                  \
	new->nxt = NULL;                                                      \
	new->prv = prv;                                                       \
	new->val = val;                                                       \
                                                                              \
	if (prv != NULL)                                                      \
		prv->nxt = new;                                               \
                                                                              \
	return new;                                                           \
}                                                                             \
                                                                              \
static struct dll_##name##_node *                                             \
dll_##name##_nth_node(const struct dll_##name *dll, const size_t idx)         \
{                                                                             \
	size_t i;                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	if (dll->len <= idx)                                                  \
		return NULL;                                                  \
                                                                              \
	if (idx < dll->len / 2) {                                             \
		tmp = dll->head;                                              \
		for (i = 0; i < idx; i++)                                     \
			tmp = tmp->nxt;                                       \
	} else {                                                              \
		tmp = dll->tail;                                              \
		for (i = 0; i < dll->len - idx - 1; i++)                      \
			tmp = tmp->prv;                                       \
	}                                                                     \
                                                                              \
	return tmp;                                                           \
}                                                                             \
                                                                              \
struct dll_##name                                                             \
dll_##name##_new()                                                            \
{                                                                             \
	struct dll_##name dll = { NULL, NULL, 0 };                            \
	return dll;                                                           \
}                                                                             \
                                                                              \
struct dll_##name                                                             \
dll_##name##_from(const type *arr, const size_t len)                          \
{                                                                             \
	size_t i;                                                             \
	struct dll_##name dll = { NULL, NULL, len };                          \
                                                                              \
	dll.head = dll.tail = dll_##name##_new_node(arr[0], NULL);            \
                                                                              \
	for (i = 1; i < len; i++) {                                           \
		dll.tail->nxt = dll_##name##_new_node(arr[i], dll.tail);      \
		dll.tail = dll.tail->nxt;                                     \
	}                                                                     \
                                                                              \
	return dll;                                                           \
}                                                                             \
                                                                              \
struct dll_##name                                                             \
dll_##name##_copy(const struct dll_##name dll)                                \
{                                                                             \
	struct dll_##name cpy;                                                \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	cpy.head = cpy.tail = dll_##name##_new_node(dll.head->val, NULL);     \
                                                                              \
	for (tmp = dll.head->nxt; tmp != NULL; tmp = tmp->nxt) {              \
		cpy.tail->nxt = dll_##name##_new_node(tmp->val, cpy.tail);    \
		cpy.tail = cpy.tail->nxt;                                     \
	}                                                                     \
                                                                              \
	cpy.len = dll.len;                                                    \
                                                                              \
	return cpy;                                                           \
}                                                                             \
                                                                              \
struct dll_##name                                                             \
dll_##name##_slice(const struct dll_##name dll,                               \
                   const size_t head, const size_t tail)                      \
{                                                                             \
	size_t i;                                                             \
	struct dll_##name sli;                                                \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	if (tail - 1 <= head)                                                 \
		return dll_##name##_new();                                    \
	                                                                      \
	tmp = dll_##name##_nth_node(&dll, head);                              \
	sli.head = sli.tail = dll_##name##_new_node(tmp->val, NULL);          \
                                                                              \
	for (i = 0; i < tail - head; i++) {                                   \
		tmp = tmp->nxt;                                               \
		sli.tail = sli.tail->nxt                                      \
			= dll_##name##_new_node(tmp->val, sli.tail);          \
	}                                                                     \
                                                                              \
	sli.len = dll.len;                                                    \
                                                                              \
	return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_back(struct dll_##name *dll, const type val)                \
{                                                                             \
	if (dll->head == NULL) {                                              \
		dll->head = dll->tail = dll_##name##_new_node(val, NULL);     \
		dll->len++;                                                   \
		return 0;                                                     \
	}                                                                     \
                                                                              \
	dll->tail = dll->tail->nxt = dll_##name##_new_node(val, dll->tail);   \
                                                                              \
	dll->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_front(struct dll_##name *dll, const type val)               \
{                                                                             \
	struct dll_##name##_node *new;                                        \
                                                                              \
	if (dll->head == NULL) {                                              \
		dll->head = dll->tail = dll_##name##_new_node(val, NULL);     \
		dll->len++;                                                   \
		return 0;                                                     \
	}                                                                     \
                                                                              \
	new = dll_##name##_new_node(val, NULL);                               \
	dll->head->prv = new;                                                 \
	new->nxt = dll->head;                                                 \
	dll->head = new;                                                      \
                                                                              \
	dll->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_pop_back(struct dll_##name *dll, type *val)                      \
{                                                                             \
	struct dll_##name##_node *prv;                                        \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
                                                                              \
	*val = dll->tail->val;                                                \
                                                                              \
	prv = dll->tail->prv;                                                 \
	free(dll->tail);                                                      \
	dll->tail = prv;                                                      \
                                                                              \
	dll->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_pop_front(struct dll_##name *dll, type *val)                     \
{                                                                             \
	struct dll_##name##_node *nxt;                                        \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
                                                                              \
	*val = dll->head->val;                                                \
                                                                              \
	nxt = dll->head->nxt;                                                 \
	free(dll->head);                                                      \
	dll->head = nxt;                                                      \
                                                                              \
	dll->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_append(struct dll_##name *des, const struct dll_##name src)      \
{                                                                             \
	struct dll_##name new;                                                \
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
	new = dll_##name##_copy(src);                                         \
	des->tail->nxt = new.head;                                            \
	new.head->prv = des->tail;                                            \
	des->tail = new.tail;                                                 \
	                                                                      \
	des->len += src.len;                                                  \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_insert(struct dll_##name *dll, const type val, const size_t idx) \
{                                                                             \
	struct dll_##name##_node *tmp, *new;                                  \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
	if (dll->len <= idx)                                                  \
		return -1;                                                    \
                                                                              \
	tmp = dll_##name##_nth_node(dll, idx);                                \
	new = dll_##name##_new_node(val, tmp->prv);                           \
	new->nxt = tmp;                                                       \
	tmp->prv = new;                                                       \
                                                                              \
	dll->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
size_t                                                                        \
dll_##name##_search(struct dll_##name *dll, const type val)                   \
{                                                                             \
	size_t i;                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
        tmp = dll->head;                                                      \
	for (i = 0; tmp != NULL; i++) {                                       \
		if (tmp->val == val)                                          \
			return i;                                             \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	return dll->len;                                                      \
}                                                                             \
                                                                              \
size_t                                                                        \
dll_##name##_remove(struct dll_##name *dll, const type val)                   \
{                                                                             \
	size_t i;                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
        tmp = dll->head;                                                      \
	for (i = 0; tmp->val != val; i++) {                                   \
		if (tmp == NULL)                                              \
			return dll->len;                                      \
                                                                              \
		tmp = tmp->nxt;                                               \
	}                                                                     \
                                                                              \
	tmp->prv->nxt = tmp->nxt;                                             \
	tmp->nxt->prv = tmp->prv;                                             \
                                                                              \
	free(tmp);                                                            \
                                                                              \
	dll->len--;                                                           \
                                                                              \
	if (dll->len == 0)                                                    \
		dll->head = dll->tail = NULL;                                 \
                                                                              \
	return i;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_getnth(const struct dll_##name *dll, type *val, const size_t idx)\
{                                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
	if (dll->len <= idx)                                                  \
		return -1;                                                    \
                                                                              \
	tmp = dll_##name##_nth_node(dll, idx);                                \
	*val = tmp->val;                                                      \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_setnth(struct dll_##name *dll, const type val, const size_t idx) \
{                                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
	if (dll->len <= idx)                                                  \
		return -1;                                                    \
                                                                              \
	tmp = dll_##name##_nth_node(dll, idx);                                \
	tmp->val = val;                                                       \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_rmvnth(struct dll_##name *dll, type *val, const size_t idx)      \
{                                                                             \
	struct dll_##name##_node *tmp;                                        \
                                                                              \
	if (dll->head == NULL)                                                \
		return -1;                                                    \
	if (dll->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	tmp = dll_##name##_nth_node(dll, idx);                                \
	*val = tmp->val;                                                      \
                                                                              \
	tmp->prv->nxt = tmp->nxt;                                             \
	tmp->nxt->prv = tmp->prv;                                             \
                                                                              \
	free(tmp);                                                            \
                                                                              \
	dll->len--;                                                           \
                                                                              \
	if (dll->len == 0)                                                    \
		dll->head = dll->tail = NULL;                                 \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
dll_##name##_getptr(struct dll_##name *dll, const size_t idx)                 \
{                                                                             \
	struct dll_##name##_node *tmp;                                        \
	return (tmp = dll_##name##_nth_node(dll, idx)) ? &tmp->val : NULL;    \
}                                                                             \
                                                                              \
type *                                                                        \
dll_##name##_head(struct dll_##name *dll)                                     \
{                                                                             \
	return &dll->head->val;                                               \
}                                                                             \
                                                                              \
type *                                                                        \
dll_##name##_tail(struct dll_##name *dll)                                     \
{                                                                             \
	return &dll->tail->val;                                               \
}                                                                             \
                                                                              \
void                                                                          \
dll_##name##_free(struct dll_##name *dll)                                     \
{                                                                             \
	struct dll_##name##_node *tmp, *nxt;                                  \
                                                                              \
	for (tmp = dll->head; tmp != NULL; tmp = nxt) {                       \
		nxt = tmp->nxt;                                               \
		free(tmp);                                                    \
	}                                                                     \
                                                                              \
	dll->head = dll->tail = NULL;                                         \
	dll->len = 0;                                                         \
}                                                                             \
                                                                              \
struct dll_##name##_semi { /* to enforce semicolon */ }

#define INIT_DLL(name, type)                                                  \
INIT_DLL_TYPE(name, type);                                                    \
INIT_DLL_FUNC(name, type)

#endif
