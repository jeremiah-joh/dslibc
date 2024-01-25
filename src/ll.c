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

#include "ll.h"
#include <stdlib.h>
#include <string.h>
#define FREE(ptr)   \
free(ptr);          \
ptr = NULL;

sll
sll_new()
{
    sll sll = { NULL, NULL, 0 };
    return sll;
}

int
sll_push_back(sll *sll, const int val)
{
    if ((sll->head == NULL || sll->tail == NULL) && sll->len > 0)
        return -1;

    if (sll->head == NULL) {
        sll->head = sll->tail = malloc(sizeof(struct sll_node));
        sll->head->val = val;
        sll->head->next = NULL;
    } else {
        sll->tail->next = malloc(sizeof(struct sll_node));
        sll->tail->next->val = val;
        sll->tail->next->next = NULL;
        sll->tail = sll->tail->next;
    }

    sll->len++;

    return 0;
}

int
sll_pop_back(sll *sll, int *val)
{
    if (sll->len == 0)
        return -1;
    
    *val = sll->tail->val;
    FREE(sll->tail);

    if (sll->len == 1) {
        sll->head = sll->tail = NULL;
    } else {
        struct sll_node *tmp = sll->head;
        for (size_t i = 0; i < sll->len - 2; i++)
            tmp = tmp->next;
        sll->tail = tmp;
        sll->tail->next = NULL;
    }

    sll->len--;

    return 0;
}

int
sll_insert(sll *sll, const int val, const size_t at)
{
    if (sll->len < at)
        return -1;
    else if (sll->len == at)
        sll_push_back(sll, val);
    else {
        struct sll_node *tmp = sll->head;
        for (size_t i = 0; i < at - 1; i++)
            tmp = tmp->next;
        struct sll_node *ori = tmp->next;
        tmp->next = malloc(sizeof(struct sll_node));
        tmp->next->val = val;
        tmp->next->next = ori;
    }

    return 0;
}

int
sll_remove(sll *sll, const int val)
{
    struct sll_node *tmp = sll->head;
    struct sll_node *tmp_p = NULL;
    while (tmp != NULL) {
        if (tmp->val == val) {
            tmp_p->next = tmp->next;
            FREE(tmp);
            return 0;
        }

        tmp_p = tmp;
        tmp = tmp->next;
    }

    return -1;
}

int
sll_rmvnth(sll *sll, const size_t at, int *val)
{
    if (sll->len <= at)
        return -1;
    
    struct sll_node *tmp = sll->head;
    for (size_t i = 0; i < at - 1; i++)
        tmp = tmp->next;
    struct sll_node *rmv = tmp->next;
    *val = rmv->val;
    tmp->next = rmv->next;
    FREE(rmv);

    return 0;
}

int
sll_getnth(sll *sll, const size_t at, int *val)
{
    if (sll->len <= at)
        return -1;

    struct sll_node *tmp = sll->head;
    for (size_t i = 0; i < at; i++)
        tmp = tmp->next;
    *val = tmp->val;

    return 0;
}

int
sll_setnth(sll *sll, const size_t at, const int val)
{
    if (sll->len <= at)
        return -1;

    struct sll_node *tmp = sll->head;
    for (size_t i = 0; i < at; i++)
        tmp = tmp->next;
    tmp->val = val;

    return 0;
}

int
sll_search(sll *sll, const int val, size_t *at)
{
    struct sll_node *tmp = sll->head;
    for (*at = 0; tmp != NULL; (*at)++) {
        if (tmp->val == val)
            return 0;
        tmp = tmp->next;
    }

    *at = 0;
    return -1;
}

int
sll_append(sll *l_sll, const sll *r_sll)
{
    if (r_sll->len == 0)
        return 0;
    if (l_sll->len == 0) {
        memcpy(l_sll, r_sll, sizeof(sll));
        return 0;
    }

    l_sll->tail->next = r_sll->head;
    l_sll->len += r_sll->len;

    return 0;
}

static void
sll_node_free(struct sll_node *node)
{
    if (node != NULL)
        sll_node_free(node->next);
    FREE(node);
}

void
sll_free(sll sll)
{
    sll_node_free(sll.head);
}

sll_iter
sll_iter_new(sll sll)
{
    sll_iter iter = { sll, NULL };
    return iter;
}

int
sll_iter_next(sll_iter *iter, int *val)
{
    if (iter->cur == NULL)
        iter->cur = iter->sll.head;
    else
        iter->cur = iter->cur->next;

    *val = iter->cur->val;

    return 0;
}

int
sll_iter_for_each(sll_iter *iter, int (*fn)(int item))
{
    if (iter->cur == NULL)
        iter->cur = iter->sll.head;

    while (iter->cur != NULL) {
        iter->cur->val = (*fn)(iter->cur->val);
        iter->cur = iter->cur->next;
    }

    return 0;
}

int
sll_iter_map(sll_iter *iter, int (*fn)(int item), sll *sll)
{
    if (iter->cur == NULL)
        iter->cur = iter->sll.head;

    while (iter->cur != NULL) {
        sll_push_back(sll, (*fn)(iter->cur->val));
        iter->cur = iter->cur->next;
    }

    return 0;
}

dll
dll_new()
{
    dll dll = { NULL, NULL, 0 };
    return dll;
}

int
dll_push_back(dll *dll, const int val)
{
    if ((dll->head == NULL || dll->tail == NULL) && dll->len > 0)
        return -1;

    if (dll->head == NULL) {
        dll->head = dll->tail = malloc(sizeof(struct dll_node));
        dll->head->val = val;
        dll->head->next = NULL;
        dll->head->prev = NULL;
    } else {
        dll->tail->next = malloc(sizeof(struct dll_node));
        dll->tail->next->val = val;
        dll->tail->next->next = NULL;
        dll->tail->next->prev = dll->tail;
        dll->tail = dll->tail->next;
    }

    dll->len++;

    return 0;
}

int
dll_pop_back(dll *dll, int *val)
{
    if (dll->len == 0)
        return -1;

    *val = dll->tail->val;
    struct dll_node *prev = dll->tail->prev;
    FREE(dll->tail);
    dll->tail = prev;
    dll->tail->next = NULL;
    dll->len--;

    if (dll->len == 0)
        dll->head = dll->tail = NULL;

    return 0;
}

int
dll_push_front(dll *dll, const int val)
{
    if ((dll->head == NULL || dll->tail == NULL) && dll->len > 0)
        return -1;

    if (dll->head == NULL) {
        dll->head = dll->tail = malloc(sizeof(struct dll_node));
        dll->head->val = val;
        dll->head->next = NULL;
        dll->head->prev = NULL;
    } else {
        dll->head->prev = malloc(sizeof(struct dll_node));
        dll->head->prev->val = val;
        dll->head->prev->prev = NULL;
        dll->head->prev->next = dll->head;
        dll->head = dll->head->prev;
    }

    dll->len++;
    
    return 0;
}

int
dll_pop_front(dll *dll, int *val)
{
    if (dll->len == 0)
        return -1;

    *val = dll->head->val;
    struct dll_node *next = dll->head->next;
    FREE(dll->head);
    dll->head = next;
    dll->head->prev = NULL;
    dll->len--;

    if (dll->len == 0)
        dll->head = dll->tail = NULL;

    return 0;
}

int
dll_insert(dll *dll, const int val, const size_t at)
{
    if (dll->len <= at)
        return -1;
    if (at == 0) {
        dll_push_front(dll, val);
        return 0;
    }

    struct dll_node *tmp;
    if (at < dll->len / 2) {
        tmp = dll->head;
        for (size_t i = 0; i < at - 1; i++)
            tmp = tmp->next;
    } else {
        tmp = dll->tail;
        for (size_t i = dll->len - 1; i >= at; i--)
            tmp = tmp->prev;
    }
    
    struct dll_node *next = tmp->next;
    tmp->next = malloc(sizeof(struct dll_node));
    tmp->next->val = val;
    tmp->next->next = next;

    dll->len++;

    return 0;
}

int
dll_remove(dll *dll, const int val)
{
    for (struct dll_node *tmp = dll->head; tmp != NULL; tmp = tmp->next) {
        if (tmp->val == val) {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            FREE(tmp);
            return 0;
        }
    }

    return -1;
}

int
dll_rmvnth(dll *dll, const size_t at, int *val)
{
    if (dll->len <= at)
        return -1;
    if (dll->len - 1 == at) {
        dll_pop_back(dll, val);
        return 0;
    }

    struct dll_node *tmp;
    if (at < dll->len / 2) {
        tmp = dll->head;
        for (size_t i = 0; i < at; i++)
            tmp = tmp->next;
    } else {
        tmp = dll->tail;
        for (size_t i = dll->len - 1; i > at; i--)
            tmp = tmp->prev;
    }

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    *val = tmp->val;
    FREE(tmp);

    dll->len--;
    
    return 0;
}

int
dll_getnth(dll *dll, const size_t at, int *val)
{
    if (dll->len <= at)
        return -1;

    if (at == 0) {
        *val = dll->head->val;
        return 0;
    }
    if (at == dll->len - 1) {
        *val = dll->tail->val;
        return 0;
    }

    struct dll_node *tmp;
    if (at < dll->len / 2) {
        tmp = dll->head;
        for (size_t i = 0; i < at; i++)
            tmp = tmp->next;
    } else {
        tmp = dll->tail;
        for (size_t i = dll->len - 1; i > at; i--)
            tmp = tmp->prev;
    }

    *val = tmp->val;

    return 0;
}

int
dll_setnth(dll *dll, const size_t at, const int val)
{
    if (dll->len <= at)
        return -1;

    if (at == 0) {
        dll->head->val = val;
        return 0;
    }
    if (at == dll->len - 1) {
        dll->tail->val = val;
        return 0;
    }

    struct dll_node *tmp;
    if (at < dll->len / 2) {
        tmp = dll->head;
        for (size_t i = 0; i < at; i++)
            tmp = tmp->next;
    } else {
        tmp = dll->tail;
        for (size_t i = dll->len - 1; i > at; i--)
            tmp = tmp->prev;
    }

    tmp->val = val;

    return 0;
}

int
dll_search_from_front(dll *dll, const int val, size_t *at)
{
    struct dll_node *tmp = dll->head;
    for (*at = 0; tmp != NULL; (*at)++) {
        if (tmp->val == val)
            return 0;
        tmp = tmp->next;
    }
    
    *at = 0;
    return -1;
}

int
dll_search_from_back(dll *dll, const int val, size_t *at)
{
    struct dll_node *tmp = dll->tail;
    for (*at = dll->len - 1; tmp != NULL; (*at)--) {
        if (tmp->val == val)
            return 0;
        tmp = tmp->prev;
    }
    
    *at = 0;
    return -1;
}

int
dll_append(dll *l_dll, const dll *r_dll)
{
    if (r_dll->len == 0)
        return 0;
    if (l_dll->len == 0) {
        memcpy(l_dll, r_dll, sizeof(dll));
        return 0;
    }

    l_dll->tail->next = r_dll->head;
    l_dll->len += r_dll->len;

    return 0;
}

static void
dll_node_free(struct dll_node *node)
{
    if (node != NULL)
        dll_node_free(node->next);
    FREE(node);
}

void
dll_free(dll dll)
{
    dll_node_free(dll.head);
}

dll_iter
dll_iter_new(dll dll)
{
    dll_iter iter = { dll, NULL };
    return iter;
}

int
dll_iter_next(dll_iter *iter, int *val)
{
    if (iter->cur == NULL)
        iter->cur = iter->dll.head;
    else
        iter->cur = iter->cur->next;

    *val = iter->cur->val;

    return 0;
}

int
dll_iter_for_each(dll_iter *iter, int (*fn)(int item))
{
    if (iter->cur == NULL)
        iter->cur = iter->dll.head;

    while (iter->cur != NULL) {
        iter->cur->val = (*fn)(iter->cur->val);
        iter->cur = iter->cur->next;
    }

    return 0;
}

int
dll_iter_map(dll_iter *iter, int (*fn)(int item), dll *dll)
{
    if (iter->cur == NULL)
        iter->cur = iter->dll.head;

    while (iter->cur != NULL) {
        dll_push_back(dll, (*fn)(iter->cur->val));
        iter->cur = iter->cur->next;
    }

    return 0;
}
