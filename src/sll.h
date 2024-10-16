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
 * If not, see <http://creatisllommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _SLL_H
#define _SLL_H

#include <stddef.h>

#define INIT_SLL_TYPE(name, type)                                              \
struct sll_##name##_node {                                                     \
        type val;                                                              \
        struct sll_##name##_node *nxt;                                         \
};                                                                             \
                                                                               \
struct sll_##name {                                                            \
        struct sll_##name##_node *beg, *end;                                   \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct sll_##name##_iter {                                                     \
        struct sll_##name##_node *cur;                                         \
};                                                                             \
                                                                               \
struct sll_##name sll_##name##_new(void);                                      \
struct sll_##name sll_##name##_from(const type *, const size_t);               \
struct sll_##name sll_##name##_copy(const struct sll_##name *);                \
int sll_##name##_push(struct sll_##name *, const type);                        \
int sll_##name##_pop(struct sll_##name *, type *);                             \
int sll_##name##_get(struct sll_##name *, type *, const size_t);               \
int sll_##name##_set(struct sll_##name *, const type, const size_t);           \
int sll_##name##_append(struct sll_##name *, struct sll_##name *);             \
int sll_##name##_insert(struct sll_##name *, const type, const size_t);        \
int sll_##name##_remove(struct sll_##name *, type *, const size_t);            \
int sll_##name##_shrink(struct sll_##name *, const size_t);                    \
size_t sll_##name##_len(struct sll_##name *);                                  \
void sll_##name##_free(struct sll_##name *);                                   \
                                                                               \
struct sll_##name##_iter sll_##name##_iter(struct sll_##name *);               \
int sll_##name##_next(struct sll_##name##_iter *, type *);                     \
                                                                               \
extern int _sll_type_##name

#define INIT_SLL_FUNC(name, type, malloc, free)                                \
static struct sll_##name##_node *                                              \
sll_##name##_node(const type val)                                              \
{                                                                              \
        struct sll_##name##_node *new;                                         \
                                                                               \
        if ((new = malloc(sizeof(struct sll_##name##_node))) == NULL)          \
                return NULL;                                                   \
                                                                               \
        new->val = val;                                                        \
        new->nxt = NULL;                                                       \
                                                                               \
        return new;                                                            \
}                                                                              \
                                                                               \
static struct sll_##name##_node *                                              \
sll_##name##_ptr(struct sll_##name *sll, size_t idx)                           \
{                                                                              \
        struct sll_##name##_node *cur;                                         \
                                                                               \
        for (cur = sll->beg; cur && idx != 0; cur = cur->nxt, idx--)           \
                ;                                                              \
                                                                               \
        return cur;                                                            \
}                                                                              \
                                                                               \
static void                                                                    \
sll_##name##_del(struct sll_##name##_node *del)                                \
{                                                                              \
        struct sll_##name##_node *nxt, *cur;                                   \
                                                                               \
        for (cur = del; cur; cur = nxt) {                                      \
                nxt = cur->nxt;                                                \
                free(cur);                                                     \
        }                                                                      \
}                                                                              \
                                                                               \
struct sll_##name                                                              \
sll_##name##_new(void)                                                         \
{                                                                              \
        struct sll_##name sll;                                                 \
                                                                               \
        sll.beg = NULL;                                                        \
        sll.end = NULL;                                                        \
        sll.len = 0;                                                           \
                                                                               \
        return sll;                                                            \
}                                                                              \
                                                                               \
struct sll_##name                                                              \
sll_##name##_from(const type *arr, const size_t len)                           \
{                                                                              \
        struct sll_##name sll;                                                 \
        size_t i;                                                              \
                                                                               \
        sll = sll_##name##_new();                                              \
                                                                               \
        for (i = 0; i < len; i++)                                              \
                if (sll_##name##_push(&sll, arr[i]))                           \
                        break;                                                 \
                                                                               \
        return sll;                                                            \
}                                                                              \
                                                                               \
struct sll_##name                                                              \
sll_##name##_copy(const struct sll_##name *sll)                                \
{                                                                              \
        struct sll_##name cpy;                                                 \
        struct sll_##name##_node *cur;                                         \
                                                                               \
        cpy = sll_##name##_new();                                              \
                                                                               \
        for (cur = sll->beg; cur; cur = cur->nxt)                              \
                if (sll_##name##_push(&cpy, cur->val))                         \
                        break;                                                 \
                                                                               \
        return cpy;                                                            \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_push(struct sll_##name *sll, const type val)                      \
{                                                                              \
        struct sll_##name##_node *new;                                         \
                                                                               \
        if ((new = sll_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
        if (sll->beg == NULL || sll->end == NULL || sll->end == 0)             \
                sll->beg = sll->end = new;                                     \
        else                                                                   \
                sll->end = sll->end->nxt = new;                                \
                                                                               \
        sll->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_pop(struct sll_##name *sll, type *val)                            \
{                                                                              \
        struct sll_##name##_node *del;                                         \
                                                                               \
        if (sll->beg == NULL || sll->end == NULL || sll->end == 0)             \
                return -1;                                                     \
                                                                               \
        *val = sll->beg->val;                                                  \
        del = sll->beg;                                                        \
        sll->beg = sll->beg->nxt;                                              \
        free(del);                                                             \
        sll->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_get(struct sll_##name *sll, type *val, const size_t idx)          \
{                                                                              \
        struct sll_##name##_node *cur;                                         \
                                                                               \
        if (sll->len <= idx)                                                   \
                return -1;                                                     \
        if ((cur = sll_##name##_ptr(sll, idx)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        *val = cur->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_set(struct sll_##name *sll, const type val, const size_t idx)     \
{                                                                              \
        struct sll_##name##_node *cur;                                         \
                                                                               \
        if (sll->len <= idx)                                                   \
                return -1;                                                     \
        if ((cur = sll_##name##_ptr(sll, idx)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        cur->val = val;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_append(struct sll_##name *old, struct sll_##name *new)            \
{                                                                              \
        struct sll_##name##_node *cur;                                         \
                                                                               \
        for (cur = new->beg; cur; cur = cur->nxt)                              \
                if (sll_##name##_push(old, cur->val))                          \
                        return -1;                                             \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_insert(struct sll_##name *sll, const type val, const size_t idx)  \
{                                                                              \
        struct sll_##name##_node *cur, *new;                                   \
                                                                               \
        if (sll->len == idx)                                                   \
                return sll_##name##_push(sll, val);                            \
        if (sll->len < idx)                                                    \
                return -1;                                                     \
        if ((cur = sll_##name##_ptr(sll, idx - 1)) == NULL)                    \
                return -1;                                                     \
        if ((new = sll_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
                                                                               \
        new->nxt = cur->nxt;                                                   \
        cur->nxt = new;                                                        \
        sll->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_remove(struct sll_##name *sll, type *val, const size_t idx)       \
{                                                                              \
        struct sll_##name##_node *pre, *del;                                   \
                                                                               \
        if (sll->beg == NULL || sll->end == NULL || sll->len == 0)             \
                return -1;                                                     \
        if (sll->len - 1 == idx)                                               \
                return sll_##name##_pop(sll, val);                             \
        if ((pre = sll_##name##_ptr(sll, idx - 1)) == NULL)                    \
                return -1;                                                     \
                                                                               \
        *val = pre->nxt->val;                                                  \
        del = pre->nxt;                                                        \
        pre->nxt = del->nxt;                                                   \
        free(del);                                                             \
        sll->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_shrink(struct sll_##name *sll, const size_t idx)                  \
{                                                                              \
        struct sll_##name##_node *pre;                                         \
                                                                               \
        if (sll->beg == NULL || sll->end == NULL || sll->len == 0)             \
                return -1;                                                     \
        if ((pre = sll_##name##_ptr(sll, idx - 1)) == NULL)                    \
                return -1;                                                     \
                                                                               \
        sll_##name##_del(pre->nxt);                                            \
        sll->end = pre;                                                        \
        sll->len = idx;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
sll_##name##_len(struct sll_##name *sll)                                       \
{                                                                              \
        return sll->len;                                                       \
}                                                                              \
                                                                               \
void                                                                           \
sll_##name##_free(struct sll_##name *sll)                                      \
{                                                                              \
        sll_##name##_del(sll->beg);                                            \
        sll->beg = sll->end = NULL;                                            \
        sll->len = 0;                                                          \
}                                                                              \
                                                                               \
struct sll_##name##_iter                                                       \
sll_##name##_iter(struct sll_##name *sll)                                      \
{                                                                              \
        struct sll_##name##_iter iter;                                         \
                                                                               \
        iter.cur = sll->beg;                                                   \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
sll_##name##_next(struct sll_##name##_iter *iter, type *val)                   \
{                                                                              \
        if (iter->cur == NULL)                                                 \
                return -1;                                                     \
                                                                               \
        *val = iter->cur->val;                                                 \
        iter->cur = iter->cur->nxt;                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
extern int _sll_func_##name


#define INIT_SLL_BOTH(name, type, malloc, free)                                \
INIT_SLL_TYPE(name, type);                                                     \
INIT_SLL_FUNC(name, type, malloc, free)

#define FOR_EACH_SLL(name, elem, iter) while (!sll_##name##_next(&iter, &elem))

#endif
