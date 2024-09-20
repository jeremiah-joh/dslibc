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
 * If not, see <http://creatidllommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _DLL_H
#define _DLL_H

#include <stddef.h>

#define INIT_DLL_TYPE(name, type)                                              \
struct dll_##name##_node {                                                     \
        type val;                                                              \
        struct dll_##name##_node *nxt, *prv;                                   \
};                                                                             \
                                                                               \
struct dll_##name {                                                            \
        struct dll_##name##_node *beg, *end;                                   \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct dll_##name##_iter {                                                     \
        struct dll_##name *dll;                                                \
        struct dll_##name##_node *cur;                                         \
};                                                                             \
                                                                               \
struct dll_##name dll_##name##_new(void);                                      \
struct dll_##name dll_##name##_from(const type *, const size_t);               \
struct dll_##name dll_##name##_copy(const struct dll_##name *);                \
int dll_##name##_push_back(struct dll_##name *, const type);                   \
int dll_##name##_pop_back(struct dll_##name *, type *);                        \
int dll_##name##_push_front(struct dll_##name *, const type);                  \
int dll_##name##_pop_front(struct dll_##name *, type *);                       \
int dll_##name##_get(struct dll_##name *, type *, const size_t);               \
int dll_##name##_set(struct dll_##name *, const type, const size_t);           \
int dll_##name##_append(struct dll_##name *, struct dll_##name *);             \
int dll_##name##_insert(struct dll_##name *, const type, const size_t);        \
int dll_##name##_remove(struct dll_##name *, type *, const size_t);            \
int dll_##name##_shrink(struct dll_##name *, const size_t);                    \
size_t dll_##name##_length(struct dll_##name *);                               \
size_t dll_##name##_sizeof(struct dll_##name *);                               \
void dll_##name##_free(struct dll_##name *);                                   \
                                                                               \
struct dll_##name##_iter dll_##name##_iter(struct dll_##name *);               \
int dll_##name##_next(struct dll_##name##_iter *, type *);

#define INIT_DLL_FUNC(name, type, malloc, free)                                \
static struct dll_##name##_node *                                              \
dll_##name##_node(const type val)                                              \
{                                                                              \
        struct dll_##name##_node *new;                                         \
                                                                               \
        if ((new = malloc(sizeof(struct dll_##name##_node))) == NULL)          \
                return NULL;                                                   \
                                                                               \
        new->val = val;                                                        \
        new->nxt = NULL;                                                       \
        new->prv = NULL;                                                       \
                                                                               \
        return new;                                                            \
}                                                                              \
                                                                               \
static struct dll_##name##_node *                                              \
dll_##name##_ptr(struct dll_##name *dll, size_t idx)                           \
{                                                                              \
        struct dll_##name##_node *cur;                                         \
                                                                               \
        if (dll->len <= idx)                                                   \
                return NULL;                                                   \
        if (idx < dll->len / 2) {                                              \
                for (cur = dll->beg; idx; idx--)                               \
                        cur = cur->nxt;                                        \
        } else {                                                               \
                for (cur = dll->end; idx < dll->len - 1; idx++)                \
                        cur = cur->prv;                                        \
        }                                                                      \
                                                                               \
        return cur;                                                            \
}                                                                              \
                                                                               \
static void                                                                    \
dll_##name##_del(struct dll_##name##_node *del)                                \
{                                                                              \
        struct dll_##name##_node *nxt, *cur;                                   \
                                                                               \
        for (cur = del; cur != NULL; cur = nxt) {                              \
                nxt = cur->nxt;                                                \
                free(cur);                                                     \
        }                                                                      \
}                                                                              \
                                                                               \
struct dll_##name                                                              \
dll_##name##_new(void)                                                         \
{                                                                              \
        struct dll_##name dll;                                                 \
                                                                               \
        dll.beg = dll.end = NULL;                                              \
        dll.len = 0;                                                           \
                                                                               \
        return dll;                                                            \
}                                                                              \
                                                                               \
struct dll_##name                                                              \
dll_##name##_from(const type *arr, const size_t len)                           \
{                                                                              \
        struct dll_##name dll;                                                 \
        size_t i;                                                              \
                                                                               \
        dll = dll_##name##_new();                                              \
                                                                               \
        for (i = 0; i < len; i++)                                              \
                if (dll_##name##_push_back(&dll, arr[i]))                      \
                        break;                                                 \
                                                                               \
        return dll;                                                            \
}                                                                              \
                                                                               \
struct dll_##name                                                              \
dll_##name##_copy(const struct dll_##name *dll)                                \
{                                                                              \
        struct dll_##name cpy;                                                 \
        struct dll_##name##_node *cur;                                         \
                                                                               \
        cpy = dll_##name##_new();                                              \
                                                                               \
        for (cur = dll->beg; cur != NULL; cur = cur->nxt)                      \
                if (dll_##name##_push_back(&cpy, cur->val))                    \
                        break;                                                 \
                                                                               \
        return cpy;                                                            \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_push_back(struct dll_##name *dll, const type val)                 \
{                                                                              \
        struct dll_##name##_node *new;                                         \
                                                                               \
        if ((new = dll_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0) {           \
                dll->beg = dll->end = new;                                     \
        } else {                                                               \
                dll->end->nxt = new;                                           \
                new->prv = dll->end;                                           \
                dll->end = new;                                                \
        }                                                                      \
                                                                               \
        dll->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_pop_back(struct dll_##name *dll, type *val)                       \
{                                                                              \
        struct dll_##name##_node *del;                                         \
                                                                               \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0)             \
                return -1;                                                     \
                                                                               \
        *val = dll->end->val;                                                  \
        del = dll->end;                                                        \
        dll->end = dll->end->prv;                                              \
        free(del);                                                             \
        dll->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_push_front(struct dll_##name *dll, const type val)                \
{                                                                              \
        struct dll_##name##_node *new;                                         \
                                                                               \
        if ((new = dll_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0) {           \
                dll->beg = dll->end = new;                                     \
        } else {                                                               \
                dll->beg->prv = new;                                           \
                new->nxt = dll->beg;                                           \
                dll->beg = new;                                                \
        }                                                                      \
                                                                               \
        dll->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_pop_front(struct dll_##name *dll, type *val)                      \
{                                                                              \
        struct dll_##name##_node *del;                                         \
                                                                               \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0)             \
                return -1;                                                     \
                                                                               \
        *val = dll->beg->val;                                                  \
        del = dll->beg;                                                        \
        dll->beg = dll->beg->nxt;                                              \
        free(del);                                                             \
        dll->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_get(struct dll_##name *dll, type *val, const size_t idx)          \
{                                                                              \
        struct dll_##name##_node *cur;                                         \
                                                                               \
        if ((cur = dll_##name##_ptr(dll, idx)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        *val = cur->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_set(struct dll_##name *dll, const type val, const size_t idx)     \
{                                                                              \
        struct dll_##name##_node *cur;                                         \
                                                                               \
        if ((cur = dll_##name##_ptr(dll, idx)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        cur->val = val;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_append(struct dll_##name *old, struct dll_##name *new)            \
{                                                                              \
        struct dll_##name##_node *cur;                                         \
                                                                               \
        for (cur = new->beg; cur != NULL; cur = cur->nxt)                      \
                if (dll_##name##_push_back(old, cur->val))                     \
                        return -1;                                             \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_insert(struct dll_##name *dll, const type val, const size_t idx)  \
{                                                                              \
        struct dll_##name##_node *cur, *new;                                   \
                                                                               \
        if (dll->len < idx)                                                    \
                return -1;                                                     \
        if ((cur = dll_##name##_ptr(dll, idx - 1)) == NULL)                    \
                return -1;                                                     \
        if ((new = dll_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
                                                                               \
        new->nxt = cur->nxt;                                                   \
        new->nxt->prv = new;                                                   \
        new->prv = cur;                                                        \
        cur->nxt = new;                                                        \
        dll->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_remove(struct dll_##name *dll, type *val, const size_t idx)       \
{                                                                              \
        struct dll_##name##_node *del;                                         \
                                                                               \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0)             \
                return -1;                                                     \
        if ((del = dll_##name##_ptr(dll, idx)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        *val = del->val;                                                       \
        del->prv->nxt = del->nxt;                                              \
        del->nxt->prv = del->prv;                                              \
        free(del);                                                             \
        dll->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_shrink(struct dll_##name *dll, const size_t len)                  \
{                                                                              \
        struct dll_##name##_node *del;                                         \
                                                                               \
        if (dll->beg == NULL || dll->end == NULL || dll->len == 0)             \
                return -1;                                                     \
        if ((del = dll_##name##_ptr(dll, len)) == NULL)                        \
                return -1;                                                     \
                                                                               \
        dll_##name##_del(del);                                                 \
        dll->len = len;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
dll_##name##_length(struct dll_##name *dll)                                    \
{                                                                              \
        return dll->len;                                                       \
}                                                                              \
                                                                               \
size_t                                                                         \
dll_##name##_sizeof(struct dll_##name *dll)                                    \
{                                                                              \
        return dll->len * sizeof(struct dll_##name##_node) + sizeof(*dll);     \
}                                                                              \
                                                                               \
void                                                                           \
dll_##name##_free(struct dll_##name *dll)                                      \
{                                                                              \
        dll_##name##_del(dll->beg);                                            \
        dll->beg = dll->end = NULL;                                            \
        dll->len = 0;                                                          \
}                                                                              \
                                                                               \
struct dll_##name##_iter                                                       \
dll_##name##_iter(struct dll_##name *dll)                                      \
{                                                                              \
        struct dll_##name##_iter iter;                                         \
                                                                               \
        iter.dll = dll;                                                        \
        iter.cur = dll->beg;                                                   \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
dll_##name##_next(struct dll_##name##_iter *iter, type *val)                   \
{                                                                              \
        if (iter->cur == NULL)                                                 \
                return -1;                                                     \
                                                                               \
        *val = iter->cur->val;                                                 \
        iter->cur = iter->cur->nxt;                                            \
                                                                               \
        return 0;                                                              \
}

#define INIT_DLL_BOTH(name, type, malloc, free)                                \
INIT_DLL_TYPE(name, type)                                                      \
INIT_DLL_FUNC(name, type, malloc, free)

#endif
