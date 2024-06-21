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

#ifndef _SLL_H
#define _SLL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_SLL_TYPE(name, type)                                             \
struct sll_##name##_node {                                                    \
        type val;                                                             \
        struct sll_##name##_node *nxt;                                        \
};                                                                            \
                                                                              \
struct sll_##name {                                                           \
        struct sll_##name##_node *head, *tail;                                \
        size_t len;                                                           \
};                                                                            \
                                                                              \
struct sll_##name sll_##name##_new();                                         \
struct sll_##name sll_##name##_map(struct sll_##name, type (*)(type));        \
struct sll_##name sll_##name##_from(const type *, const size_t);              \
struct sll_##name sll_##name##_copy(const struct sll_##name);                 \
struct sll_##name sll_##name##_slice(const struct sll_##name,                 \
                                     const size_t, const size_t);             \
int sll_##name##_push(struct sll_##name *, const type);                       \
int sll_##name##_pop(struct sll_##name *, type *);                            \
int sll_##name##_append(struct sll_##name *, const struct sll_##name);        \
int sll_##name##_insert(struct sll_##name *, const type, const size_t);       \
int sll_##name##_shrink(struct sll_##name *, const size_t);                   \
int sll_##name##_getnth(struct sll_##name *, type *, const size_t);           \
int sll_##name##_setnth(struct sll_##name *, const type, const size_t);       \
int sll_##name##_rmvnth(struct sll_##name *, type *, const size_t);           \
int sll_##name##_retain(struct sll_##name *, int (*)(type));                  \
type *sll_##name##_ptr(struct sll_##name *, const size_t);                    \
type *sll_##name##_head(struct sll_##name *);                                 \
type *sll_##name##_tail(struct sll_##name *);                                 \
void sll_##name##_foreach(struct sll_##name *, void (*)(type *));             \
void sll_##name##_free(struct sll_##name *) /* to enforce semicolon */

#define INIT_SLL_FUNC(name, type)                                             \
static struct sll_##name##_node *                                             \
sll_##name##_new_node(const type val)                                         \
{                                                                             \
        struct sll_##name##_node *new;                                        \
        if ((new = malloc(sizeof(struct sll_##name##_node))) == NULL)         \
                return NULL;                                                  \
                                                                              \
        new->val = val;                                                       \
        new->nxt = NULL;                                                      \
                                                                              \
        return new;                                                           \
}                                                                             \
                                                                              \
static struct sll_##name##_node *                                             \
sll_##name##_nth(const struct sll_##name *sll, const size_t idx)              \
{                                                                             \
        size_t i;                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        tmp = sll->head;                                                      \
        for (i = 0; i < idx; i++)                                             \
                tmp = tmp->nxt;                                               \
                                                                              \
        return tmp;                                                           \
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
sll_##name##_map(struct sll_##name sll, type (*fn)(type))                     \
{                                                                             \
        struct sll_##name map;                                                \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        map = sll_##name##_new();                                             \
                                                                              \
        for (tmp = sll.head; tmp; tmp = tmp->nxt)                             \
        	if (sll_##name##_push(&map, fn(tmp->val)))                    \
        		break;                                                \
                                                                              \
        return map;                                                           \
}                                                                             \
                                                                              \
struct sll_##name                                                             \
sll_##name##_from(const type *arr, const size_t len)                          \
{                                                                             \
        size_t i;                                                             \
        struct sll_##name sll;                                                \
                                                                              \
        sll = sll_##name##_new();                                             \
                                                                              \
        for (i = 0; i < len; i++)                                             \
                if (sll_##name##_push(&sll, arr[i]))                          \
                        break;                                                \
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
        cpy = sll_##name##_new();                                             \
                                                                              \
        for (tmp = sll.head; tmp != NULL; tmp = tmp->nxt)                     \
                if (sll_##name##_push(&cpy, tmp->val))                        \
                        break;                                                \
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
        sli = sll_##name##_new();                                             \
                                                                              \
        if (tail <= head)                                                     \
                return sli;                                                   \
        if ((tmp = sll_##name##_nth(&sll, head)) == NULL)                     \
                return sli;                                                   \
                                                                              \
        for (i = head; i < tail; i++) {                                       \
                if (sll_##name##_push(&sli, tmp->val))                        \
                        return sli;                                           \
                                                                              \
                tmp = tmp->nxt;                                               \
        }                                                                     \
                                                                              \
        return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_push(struct sll_##name *sll, const type val)                     \
{                                                                             \
        struct sll_##name##_node *new;                                        \
                                                                              \
        if ((new = sll_##name##_new_node(val)) == NULL)                       \
                return -1;                                                    \
        if (sll->head == NULL || sll->tail == NULL || sll->len == 0)          \
                sll->head = sll->tail = new;                                  \
        else                                                                  \
                sll->tail = sll->tail->nxt = new;                             \
                                                                              \
        sll->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_pop(struct sll_##name *sll, type *val)                           \
{                                                                             \
        if (sll->head == NULL || sll->tail == NULL || sll->len == 0)          \
                return -1;                                                    \
        if ((sll->tail = sll_##name##_nth(sll, sll->len - 2)) == NULL)        \
                return -1;                                                    \
                                                                              \
        *val = sll->tail->nxt->val;                                           \
        free(sll->tail->nxt);                                                 \
        sll->len--;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_append(struct sll_##name *des, const struct sll_##name src)      \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        if (src.head == NULL || src.tail == NULL || src.len == 0)             \
                return 0;                                                     \
        if (des->head == NULL || des->tail == NULL || des->len == 0) {        \
                *des = src;                                                   \
                return 0;                                                     \
        }                                                                     \
                                                                              \
        for (tmp = src.head; tmp != NULL; tmp = tmp->nxt)                     \
                if (sll_##name##_push(des, tmp->val))                         \
                        return -1;                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_insert(struct sll_##name *sll, const type val, const size_t idx) \
{                                                                             \
        struct sll_##name##_node *tmp, *nxt;                                  \
                                                                              \
        if (sll->head == NULL || sll->tail == NULL || sll->len == 0)          \
                if (idx == 0)                                                 \
                        return sll_##name##_push(sll, val);                   \
                                                                              \
        tmp = sll_##name##_nth(sll, idx - 1);                                 \
        nxt = tmp->nxt;                                                       \
        tmp->nxt = sll_##name##_new_node(val);                                \
        tmp->nxt->nxt = nxt;                                                  \
                                                                              \
        sll->len++;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_shrink(struct sll_##name *sll, const size_t len)                 \
{                                                                             \
        type buf;                                                             \
                                                                              \
        if (len > sll->len)                                                   \
                return -1;                                                    \
                                                                              \
        while (sll->len > len)                                                \
                if (sll_##name##_pop(sll, &buf))                              \
                        return -1;                                            \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_getnth(struct sll_##name *sll, type *val, const size_t idx)      \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        if ((tmp = sll_##name##_nth(sll, idx)) == NULL)                       \
                return -1;                                                    \
                                                                              \
        *val = tmp->val;                                                      \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_setnth(struct sll_##name *sll, const type val, const size_t idx) \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        if ((tmp = sll_##name##_nth(sll, idx)) == NULL)                       \
                return -1;                                                    \
                                                                              \
        tmp->val = val;                                                       \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_rmvnth(struct sll_##name *sll, type *val, const size_t idx)      \
{                                                                             \
        struct sll_##name##_node *tmp, *nxt;                                  \
                                                                              \
        if (idx == sll->len - 1)                                              \
                return sll_##name##_pop(sll, val);                            \
        if ((tmp = sll_##name##_nth(sll, idx - 1)) == NULL)                   \
                return -1;                                                    \
                                                                              \
        *val = tmp->nxt->val;                                                 \
                                                                              \
        nxt = tmp->nxt;                                                       \
        tmp->nxt = nxt->nxt;                                                  \
        free(nxt);                                                            \
        sll->len--;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_retain(struct sll_##name *sll, int (*fn)(type))                  \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
        struct sll_##name cpy;                                                \
                                                                              \
        cpy = sll_##name##_new();                                             \
                                                                              \
        for (tmp = sll->head; tmp; tmp = tmp->nxt) {                          \
                if (fn(tmp->val)) {                                           \
                        if (sll_##name##_push(&cpy, tmp->val)) {              \
                                sll_##name##_free(&cpy);                      \
                                return -1;                                    \
                        }                                                     \
                }                                                             \
        }                                                                     \
                                                                              \
        sll_##name##_free(sll);                                               \
        *sll = cpy;                                                           \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
sll_##name##_ptr(struct sll_##name *sll, const size_t idx)                    \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        return ((tmp = sll_##name##_nth(sll, idx))) ? &tmp->val : NULL;       \
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
void                                                                          \
sll_##name##_foreach(struct sll_##name *sll, void (*fn)(type *))              \
{                                                                             \
        struct sll_##name##_node *tmp;                                        \
                                                                              \
        for (tmp = sll->head; tmp; tmp = tmp->nxt)                            \
                fn(&tmp->val);                                                \
}                                                                             \
                                                                              \
void                                                                          \
sll_##name##_free(struct sll_##name *sll)                                     \
{                                                                             \
        struct sll_##name##_node *tmp, *nxt;                                  \
                                                                              \
        for (tmp = sll->head; tmp != NULL; tmp = nxt) {                       \
                nxt = tmp->nxt;                                               \
                free(tmp);                                                    \
        }                                                                     \
                                                                              \
        sll->head = sll->tail = NULL;                                         \
        sll->len = 0;                                                         \
}                                                                             \
                                                                              \
struct sll_##name##_semi { /* to enforce semicolon */ }

#define INIT_SLL(name, type)                                                  \
INIT_SLL_TYPE(name, type);                                                    \
INIT_SLL_FUNC(name, type)

#endif
