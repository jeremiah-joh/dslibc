/*
 * Copyright (C) 2024 Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * This file is part of dslibc.
 *
 * dslibc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dslibc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _LL_H
#define _LL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

#define INIT_SLL(name, type)                                                  \
                                                                              \
struct sll_##name##_node {                                                    \
    type val;                                                                 \
    struct sll_##name##_node *next;                                           \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct sll_##name##_node *head;                                           \
    struct sll_##name##_node *tail;                                           \
    size_t len;                                                               \
} sll_##name;                                                                 \
                                                                              \
typedef struct {                                                              \
    sll_##name sll;                                                           \
    struct sll_##name##_node *cur;                                            \
} sll_##name##_iter;                                                          \
                                                                              \
sll_##name                                                                    \
sll_##name##_new()                                                            \
{                                                                             \
    sll_##name sll_##name = { NULL, NULL, 0 };                                \
    return sll_##name;                                                        \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_push_back(sll_##name *sll, const type val)                       \
{                                                                             \
    if ((sll->head == NULL || sll->tail == NULL) && sll->len > 0)             \
        return -1;                                                            \
                                                                              \
    if (sll->head == NULL) {                                                  \
        sll->head = sll->tail = malloc(sizeof(struct sll_##name##_node));     \
        sll->head->val = val;                                                 \
        sll->head->next = NULL;                                               \
    } else {                                                                  \
        sll->tail->next = malloc(sizeof(struct sll_##name##_node));           \
        sll->tail->next->val = val;                                           \
        sll->tail->next->next = NULL;                                         \
        sll->tail = sll->tail->next;                                          \
    }                                                                         \
                                                                              \
    sll->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_pop_back(sll_##name *sll, type *val)                             \
{                                                                             \
    if (sll->len == 0)                                                        \
        return -1;                                                            \
                                                                              \
    *val = sll->tail->val;                                                    \
    FREE(sll->tail);                                                          \
                                                                              \
    if (sll->len == 1) {                                                      \
        sll->head = sll->tail = NULL;                                         \
    } else {                                                                  \
        struct sll_##name##_node *tmp = sll->head;                            \
        for (size_t i = 0; i < sll->len - 2; i++)                             \
            tmp = tmp->next;                                                  \
        sll->tail = tmp;                                                      \
        sll->tail->next = NULL;                                               \
    }                                                                         \
                                                                              \
    sll->len--;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_insert(sll_##name *sll, const type val, const size_t at)         \
{                                                                             \
    if (sll->len < at)                                                        \
        return -1;                                                            \
    else if (sll->len == at)                                                  \
        sll_##name##_push_back(sll, val);                                     \
    else {                                                                    \
        struct sll_##name##_node *tmp = sll->head;                            \
        for (size_t i = 0; i < at - 1; i++)                                   \
            tmp = tmp->next;                                                  \
        struct sll_##name##_node *ori = tmp->next;                            \
        tmp->next = malloc(sizeof(struct sll_##name##_node));                 \
        tmp->next->val = val;                                                 \
        tmp->next->next = ori;                                                \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_remove(sll_##name *sll, const type val)                          \
{                                                                             \
    struct sll_##name##_node *tmp = sll->head;                                \
    struct sll_##name##_node *tmp_p = NULL;                                   \
    while (tmp != NULL) {                                                     \
        if (tmp->val == val) {                                                \
            tmp_p->next = tmp->next;                                          \
            FREE(tmp);                                                        \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        tmp_p = tmp;                                                          \
        tmp = tmp->next;                                                      \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_rmvnth(sll_##name *sll, const size_t at, type *val)              \
{                                                                             \
    if (sll->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    struct sll_##name##_node *tmp = sll->head;                                \
    for (size_t i = 0; i < at - 1; i++)                                       \
        tmp = tmp->next;                                                      \
    struct sll_##name##_node *rmv = tmp->next;                                \
    *val = rmv->val;                                                          \
    tmp->next = rmv->next;                                                    \
    FREE(rmv);                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_getnth(sll_##name *sll, const size_t at, type *val)              \
{                                                                             \
    if (sll->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    struct sll_##name##_node *tmp = sll->head;                                \
    for (size_t i = 0; i < at; i++)                                           \
        tmp = tmp->next;                                                      \
    *val = tmp->val;                                                          \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_setnth(sll_##name *sll, const size_t at, const type val)         \
{                                                                             \
    if (sll->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    struct sll_##name##_node *tmp = sll->head;                                \
    for (size_t i = 0; i < at; i++)                                           \
        tmp = tmp->next;                                                      \
    tmp->val = val;                                                           \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_search(sll_##name *sll, const type val, size_t *at)              \
{                                                                             \
    struct sll_##name##_node *tmp = sll->head;                                \
    for (*at = 0; tmp != NULL; (*at)++) {                                     \
        if (tmp->val == val)                                                  \
            return 0;                                                         \
        tmp = tmp->next;                                                      \
    }                                                                         \
                                                                              \
    *at = 0;                                                                  \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_append(sll_##name *l_sll, const sll_##name *r_sll)               \
{                                                                             \
    if (r_sll->len == 0)                                                      \
        return 0;                                                             \
    if (l_sll->len == 0) {                                                    \
        memcpy(l_sll, r_sll, sizeof(sll_##name));                             \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    l_sll->tail->next = r_sll->head;                                          \
    l_sll->len += r_sll->len;                                                 \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static void                                                                   \
sll_##name##_node_free(struct sll_##name##_node *node)                        \
{                                                                             \
    if (node != NULL)                                                         \
        sll_##name##_node_free(node->next);                                   \
    FREE(node);                                                               \
}                                                                             \
                                                                              \
void                                                                          \
sll_##name##_free(sll_##name sll)                                             \
{                                                                             \
    sll_##name##_node_free(sll.head);                                         \
}                                                                             \
                                                                              \
sll_##name##_iter                                                             \
sll_##name##_iter_new(sll_##name sll)                                         \
{                                                                             \
    sll_##name##_iter iter = { sll, NULL };                                   \
    return iter;                                                              \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_iter_next(sll_##name##_iter *iter, type *val)                    \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->sll.head;                                           \
    else                                                                      \
        iter->cur = iter->cur->next;                                          \
                                                                              \
    *val = iter->cur->val;                                                    \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_iter_for_each(sll_##name##_iter *iter, type (*fn)(type item))    \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->sll.head;                                           \
                                                                              \
    while (iter->cur != NULL) {                                               \
        iter->cur->val = (*fn)(iter->cur->val);                               \
        iter->cur = iter->cur->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
sll_##name##_iter_map(sll_##name##_iter *iter,                                \
                      type (*fn)(type item), sll_##name *sll)                 \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->sll.head;                                           \
                                                                              \
    while (iter->cur != NULL) {                                               \
        sll_##name##_push_back(sll, (*fn)(iter->cur->val));                   \
        iter->cur = iter->cur->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}

#define INIT_DLL(name, type)                                                  \
                                                                              \
struct dll_##name##_node {                                                    \
    type val;                                                                 \
    struct dll_##name##_node *next;                                           \
    struct dll_##name##_node *prev;                                           \
};                                                                            \
                                                                              \
typedef struct {                                                              \
    struct dll_##name##_node *head;                                           \
    struct dll_##name##_node *tail;                                           \
    size_t len;                                                               \
} dll_##name;                                                                 \
                                                                              \
typedef struct {                                                              \
    dll_##name dll;                                                           \
    struct dll_##name##_node *cur;                                            \
} dll_##name##_iter;                                                          \
                                                                              \
dll_##name                                                                    \
dll_##name##_new()                                                            \
{                                                                             \
    dll_##name dll_##name = { NULL, NULL, 0 };                                \
    return dll;                                                               \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_back(dll_##name *dll, const type val)                       \
{                                                                             \
    if ((dll->head == NULL || dll->tail == NULL) && dll->len > 0)             \
        return -1;                                                            \
                                                                              \
    if (dll->head == NULL) {                                                  \
        dll->head = dll->tail = malloc(sizeof(struct dll_##name##_node));     \
        dll->head->val = val;                                                 \
        dll->head->next = NULL;                                               \
        dll->head->prev = NULL;                                               \
    } else {                                                                  \
        dll->tail->next = malloc(sizeof(struct dll_##name##_node));           \
        dll->tail->next->val = val;                                           \
        dll->tail->next->next = NULL;                                         \
        dll->tail->next->prev = dll->tail;                                    \
        dll->tail = dll->tail->next;                                          \
    }                                                                         \
                                                                              \
    dll->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_pop_back(dll_##name *dll, type *val)                             \
{                                                                             \
    if (dll->len == 0)                                                        \
        return -1;                                                            \
                                                                              \
    *val = dll->tail->val;                                                    \
    struct dll_##name##_node *prev = dll->tail->prev;                         \
    FREE(dll->tail);                                                          \
    dll->tail = prev;                                                         \
    dll->tail->next = NULL;                                                   \
    dll->len--;                                                               \
                                                                              \
    if (dll->len == 0)                                                        \
        dll->head = dll->tail = NULL;                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_push_front(dll_##name *dll, const type val)                      \
{                                                                             \
    if ((dll->head == NULL || dll->tail == NULL) && dll->len > 0)             \
        return -1;                                                            \
                                                                              \
    if (dll->head == NULL) {                                                  \
        dll->head = dll->tail = malloc(sizeof(struct dll_##name##_node));     \
        dll->head->val = val;                                                 \
        dll->head->next = NULL;                                               \
        dll->head->prev = NULL;                                               \
    } else {                                                                  \
        dll->head->prev = malloc(sizeof(struct dll_##name##_node));           \
        dll->head->prev->val = val;                                           \
        dll->head->prev->prev = NULL;                                         \
        dll->head->prev->next = dll->head;                                    \
        dll->head = dll->head->prev;                                          \
    }                                                                         \
                                                                              \
    dll->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_pop_front(dll_##name *dll, type *val)                            \
{                                                                             \
    if (dll->len == 0)                                                        \
        return -1;                                                            \
                                                                              \
    *val = dll->head->val;                                                    \
    struct dll_##name##_node *next = dll->head->next;                         \
    FREE(dll->head);                                                          \
    dll->head = next;                                                         \
    dll->head->prev = NULL;                                                   \
    dll->len--;                                                               \
                                                                              \
    if (dll->len == 0)                                                        \
        dll->head = dll->tail = NULL;                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_insert(dll_##name *dll, const type val, const size_t at)         \
{                                                                             \
    if (dll->len <= at)                                                       \
        return -1;                                                            \
    if (at == 0) {                                                            \
        dll_##name##_push_front(dll, val);                                    \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    struct dll_##name##_node *tmp;                                            \
    if (at < dll->len / 2) {                                                  \
        tmp = dll->head;                                                      \
        for (size_t i = 0; i < at - 1; i++)                                   \
            tmp = tmp->next;                                                  \
    } else {                                                                  \
        tmp = dll->tail;                                                      \
        for (size_t i = dll->len - 1; i >= at; i--)                           \
            tmp = tmp->prev;                                                  \
    }                                                                         \
                                                                              \
    struct dll_##name##_node *next = tmp->next;                               \
    tmp->next = malloc(sizeof(struct dll_##name##_node));                     \
    tmp->next->val = val;                                                     \
    tmp->next->next = next;                                                   \
                                                                              \
    dll->len++;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_remove(dll_##name *dll, const type val)                          \
{                                                                             \
    struct dll_##name##_node *tmp                                             \
    for ( = dll->head; tmp != NULL; tmp = tmp->next) {                        \
        if (tmp->val == val) {                                                \
            tmp->prev->next = tmp->next;                                      \
            tmp->next->prev = tmp->prev;                                      \
            FREE(tmp);                                                        \
            return 0;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_rmvnth(dll_##name *dll, const size_t at, type *val)              \
{                                                                             \
    if (dll->len <= at)                                                       \
        return -1;                                                            \
    if (dll->len - 1 == at) {                                                 \
        dll_##name##_pop_back(dll, val);                                      \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    struct dll_##name##_node *tmp;                                            \
    if (at < dll->len / 2) {                                                  \
        tmp = dll->head;                                                      \
        for (size_t i = 0; i < at; i++)                                       \
            tmp = tmp->next;                                                  \
    } else {                                                                  \
        tmp = dll->tail;                                                      \
        for (size_t i = dll->len - 1; i > at; i--)                            \
            tmp = tmp->prev;                                                  \
    }                                                                         \
                                                                              \
    tmp->prev->next = tmp->next;                                              \
    tmp->next->prev = tmp->prev;                                              \
    *val = tmp->val;                                                          \
    FREE(tmp);                                                                \
                                                                              \
    dll->len--;                                                               \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_getnth(dll_##name *dll, const size_t at, type *val)              \
{                                                                             \
    if (dll->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    if (at == 0) {                                                            \
        *val = dll->head->val;                                                \
        return 0;                                                             \
    }                                                                         \
    if (at == dll->len - 1) {                                                 \
        *val = dll->tail->val;                                                \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    struct dll_##name##_node *tmp;                                            \
    if (at < dll->len / 2) {                                                  \
        tmp = dll->head;                                                      \
        for (size_t i = 0; i < at; i++)                                       \
            tmp = tmp->next;                                                  \
    } else {                                                                  \
        tmp = dll->tail;                                                      \
        for (size_t i = dll->len - 1; i > at; i--)                            \
            tmp = tmp->prev;                                                  \
    }                                                                         \
                                                                              \
    *val = tmp->val;                                                          \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_setnth(dll_##name *dll, const size_t at, const type val)         \
{                                                                             \
    if (dll->len <= at)                                                       \
        return -1;                                                            \
                                                                              \
    if (at == 0) {                                                            \
        dll->head->val = val;                                                 \
        return 0;                                                             \
    }                                                                         \
    if (at == dll->len - 1) {                                                 \
        dll->tail->val = val;                                                 \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    struct dll_##name##_node *tmp;                                            \
    if (at < dll->len / 2) {                                                  \
        tmp = dll->head;                                                      \
        for (size_t i = 0; i < at; i++)                                       \
            tmp = tmp->next;                                                  \
    } else {                                                                  \
        tmp = dll->tail;                                                      \
        for (size_t i = dll->len - 1; i > at; i--)                            \
            tmp = tmp->prev;                                                  \
    }                                                                         \
                                                                              \
    tmp->val = val;                                                           \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_search_from_front(dll_##name *dll, const type val, size_t *at)   \
{                                                                             \
    struct dll_##name##_node *tmp = dll->head;                                \
    for (*at = 0; tmp != NULL; (*at)++) {                                     \
        if (tmp->val == val)                                                  \
            return 0;                                                         \
        tmp = tmp->next;                                                      \
    }                                                                         \
                                                                              \
    *at = 0;                                                                  \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_search_from_back(dll_##name *dll, const type val, size_t *at)    \
{                                                                             \
    struct dll_##name##_node *tmp = dll->tail;                                \
    for (*at = dll->len - 1; tmp != NULL; (*at)--) {                          \
        if (tmp->val == val)                                                  \
            return 0;                                                         \
        tmp = tmp->prev;                                                      \
    }                                                                         \
                                                                              \
    *at = 0;                                                                  \
    return -1;                                                                \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_append(dll_##name *l_dll, const dll_##name *r_dll)               \
{                                                                             \
    if (r_dll->len == 0)                                                      \
        return 0;                                                             \
    if (l_dll->len == 0) {                                                    \
        memcpy(l_dll, r_dll, sizeof(dll));                                    \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    l_dll->tail->next = r_dll->head;                                          \
    l_dll->len += r_dll->len;                                                 \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static void                                                                   \
dll_##name##_node_free(struct dll_node *node)                                 \
{                                                                             \
    if (node != NULL)                                                         \
        dll_##name##_node_free(node->next);                                   \
    FREE(node);                                                               \
}                                                                             \
                                                                              \
void                                                                          \
dll_##name##_free(dll_##name dll)                                             \
{                                                                             \
    dll_##name##_node_free(dll.head);                                         \
}                                                                             \
                                                                              \
dll_##name##_iter                                                             \
dll_##name##_iter_new(dll_##name dll)                                         \
{                                                                             \
    dll_##name##_iter iter = { dll, NULL };                                   \
    return iter;                                                              \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_iter_next(dll_iter *iter, type *val)                             \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->dll.head;                                           \
    else                                                                      \
        iter->cur = iter->cur->next;                                          \
                                                                              \
    *val = iter->cur->val;                                                    \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_iter_for_each(dll_iter *iter, type (*fn)(type item))             \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->dll.head;                                           \
                                                                              \
    while (iter->cur != NULL) {                                               \
        iter->cur->val = (*fn)(iter->cur->val);                               \
        iter->cur = iter->cur->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
int                                                                           \
dll_##name##_iter_map(dll_iter *iter, type (*fn)(type item), dll_##name *dll) \
{                                                                             \
    if (iter->cur == NULL)                                                    \
        iter->cur = iter->dll.head;                                           \
                                                                              \
    while (iter->cur != NULL) {                                               \
        dll_##name##_push_back(dll, (*fn)(iter->cur->val));                   \
        iter->cur = iter->cur->next;                                          \
    }                                                                         \
                                                                              \
    return 0;                                                                 \
}

#endif
