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
};                                                                            \
                                                                              \
struct dll_##name dll_##name##_new();                                         \
struct dll_##name dll_##name##_from(const type *, const size_t);              \
struct dll_##name dll_##name##_copy(const struct dll_##name);                 \
struct dll_##name dll_##name##_slice(const struct dll_##name,                 \
                                     const size_t, const size_t);             \
int dll_##name##_push_back(struct dll_##name *, const type);                  \
int dll_##name##_push_front(struct dll_##name *, const type);                 \
int dll_##name##_pop_back(struct dll_##name *, type *);                       \
int dll_##name##_pop_front(struct dll_##name *, type *);                      \
int dll_##name##_append(struct dll_##name *, const struct dll_##name);        \
int dll_##name##_insert(struct dll_##name *, const type, const size_t);       \
int dll_##name##_shrink(struct dll_##name *, const size_t);                   \
int dll_##name##_getnth(struct dll_##name *, type *, const size_t);           \
int dll_##name##_setnth(struct dll_##name *, const type, const size_t);       \
int dll_##name##_rmvnth(struct dll_##name *, type *, const size_t);           \
int dll_##name##_retain(struct dll_##name *, int (*)(type));                  \
type *dll_##name##_ptr(struct dll_##name *, const size_t);                    \
type *dll_##name##_head(struct dll_##name *);                                 \
type *dll_##name##_tail(struct dll_##name *);                                 \
void dll_##name##_foreach(struct dll_##name *, void (*)(type *));             \
void dll_##name##_free(struct dll_##name *) /* to enforce semicolon */

#define INIT_DLL_FUNC(name, type)                                             \
static struct dll_##name##_node *                                             \
dll_##name##_new_node(const type val,                                         \
                      struct dll_##name##_node *prv,                          \
                      struct dll_##name##_node *nxt)                          \
{                                                                             \
        struct dll_##name##_node *new;                                        \
        if ((new = malloc(sizeof(struct dll_##name##_node))) == NULL)         \
                return NULL;                                                  \
                                                                              \
        new->nxt = nxt;                                                       \
        new->prv = prv;                                                       \
        new->val = val;                                                       \
                                                                              \
        if (prv)                                                              \
                prv->nxt = new;                                               \
        if (nxt)                                                              \
                nxt->prv = new;                                               \
                                                                              \
        return new;                                                           \
}                                                                             \
                                                                              \
static struct dll_##name##_node *                                             \
dll_##name##_nth(const struct dll_##name *dll, const size_t idx)              \
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
        struct dll_##name dll;                                                \
                                                                              \
        dll = dll_##name##_new();                                             \
                                                                              \
        for (i = 0; i < len; i++)                                             \
                if (dll_##name##_push_back(&dll, arr[i]))                     \
                        break;                                                \
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
        cpy = dll_##name##_new();                                             \
                                                                              \
        for (tmp = dll.head; tmp != NULL; tmp = tmp->nxt)                     \
                if (dll_##name##_push_back(&cpy, tmp->val))                   \
                        break;                                                \
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
        sli = dll_##name##_new();                                             \
                                                                              \
        if (tail - 1 <= head)                                                 \
                return sli;                                                   \
                                                                              \
        tmp = dll_##name##_nth(&dll, head);                                   \
        for (i = head; i < tail; i++) {                                       \
                if (dll_##name##_push_back(&sli, tmp->val))                   \
                        break;                                                \
                                                                              \
                tmp = tmp->nxt;                                               \
        }                                                                     \
                                                                              \
        return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_back(struct dll_##name *dll, const type val)                \
{                                                                             \
        if (dll->head == NULL || dll->tail == NULL || dll->len == 0) {        \
                dll->head = dll_##name##_new_node(val, NULL, NULL);           \
                dll->tail = dll->head;                                        \
        } else {                                                              \
                dll->tail->nxt = dll_##name##_new_node(val, dll->tail, NULL); \
                dll->tail = dll->tail->nxt;                                   \
        }                                                                     \
                                                                              \
        dll->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_front(struct dll_##name *dll, const type val)               \
{                                                                             \
        if (dll->head == NULL || dll->tail == NULL || dll->len == 0) {        \
                dll->head = dll_##name##_new_node(val, NULL, NULL);           \
                dll->tail = dll->head;                                        \
        } else {                                                              \
                dll->head->prv = dll_##name##_new_node(val, NULL, dll->head); \
                dll->head = dll->head->prv;                                   \
        }                                                                     \
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
        struct dll_##name##_node *tmp;                                        \
                                                                              \
        if (src.head == NULL || src.tail == NULL || src.len == 0)             \
                return 0;                                                     \
        if (des->head == NULL || des->tail == NULL || des->len == 0) {        \
                *des = src;                                                   \
                return 0;                                                     \
        }                                                                     \
                                                                              \
        for (tmp = src.head; tmp != NULL; tmp = tmp->nxt)                     \
                if (dll_##name##_push_back(des, tmp->val))                    \
                        return -1;                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_insert(struct dll_##name *dll, const type val, const size_t idx) \
{                                                                             \
        struct dll_##name##_node *tmp;                                        \
                                                                              \
        if (dll->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        tmp = dll_##name##_nth(dll, idx);                                     \
        dll_##name##_new_node(val, tmp->prv, tmp);                            \
                                                                              \
        dll->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_shrink(struct dll_##name *dll, const size_t len)                 \
{                                                                             \
        type buf;                                                             \
                                                                              \
        if (dll->len < len)                                                   \
                return -1;                                                    \
                                                                              \
        while (dll->len > len)                                                \
                if (dll_##name##_pop_back(dll, &buf))                         \
                        return -1;                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_getnth(struct dll_##name *dll, type *val, const size_t idx)      \
{                                                                             \
        struct dll_##name##_node *tmp;                                        \
                                                                              \
        if (dll->head == NULL)                                                \
                return -1;                                                    \
        if (dll->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        tmp = dll_##name##_nth(dll, idx);                                     \
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
        if (dll->head == NULL || dll->tail == NULL || dll->len == 0)          \
                return -1;                                                    \
        if (dll->len <= idx)                                                  \
                return -1;                                                    \
                                                                              \
        tmp = dll_##name##_nth(dll, idx);                                     \
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
        if (dll->head == NULL || dll->tail == NULL || dll->len == 0)          \
                return -1;                                                    \
        if ((tmp = dll_##name##_nth(dll, idx)) == NULL)                       \
                return -1;                                                    \
                                                                              \
        *val = tmp->val;                                                      \
                                                                              \
        tmp->prv->nxt = tmp->nxt;                                             \
        tmp->nxt->prv = tmp->prv;                                             \
                                                                              \
        free(tmp);                                                            \
        dll->len--;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_retain(struct dll_##name *dll, int (*fn)(type))                  \
{                                                                             \
        struct dll_##name##_node *tmp;                                        \
        struct dll_##name cpy;                                                \
                                                                              \
        cpy = dll_##name##_new();                                             \
                                                                              \
        for (tmp = dll->head; tmp; tmp = tmp->nxt) {                          \
                if (fn(tmp->val)) {                                           \
                        if (dll_##name##_push_back(&cpy, tmp->val)) {         \
                                dll_##name##_free(&cpy);                      \
                                return -1;                                    \
                        }                                                     \
                }                                                             \
        }                                                                     \
                                                                              \
	dll_##name##_free(dll);                                               \
	*dll = cpy;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
dll_##name##_ptr(struct dll_##name *dll, const size_t idx)                    \
{                                                                             \
        struct dll_##name##_node *tmp;                                        \
                                                                              \
        return (tmp = dll_##name##_nth(dll, idx)) ? &tmp->val : NULL;         \
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
dll_##name##_foreach(struct dll_##name *dll, void (*fn)(type *))              \
{                                                                             \
        struct dll_##name##_node *tmp;                                        \
                                                                              \
        for (tmp = dll->head; tmp; tmp = tmp->nxt)                            \
                fn(&tmp->val);                                                \
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
