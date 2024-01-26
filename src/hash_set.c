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

#include "hash_set.h"
#include <stdlib.h>
#include <string.h>
#define INIT_LEN 16
#define FREE(ptr)   \
do {                \
    free(ptr);      \
    ptr = NULL;     \
} while (0)

static int
sll_push_back(struct sll *sll, const int key)
{
    if (sll->head == NULL) {
        sll->head = sll->tail = malloc(sizeof(struct hash_set_node));
        sll->head->key = key;
        sll->head->next = NULL;
    } else {
        sll->tail->next = malloc(sizeof(struct hash_set_node));
        sll->tail->next->key = key;
        sll->tail->next->next = NULL;
        sll->tail = sll->tail->next;
    }

    return 0;
}

static int
sll_remove(struct sll *sll, const int key)
{
    struct hash_set_node *tmp, *tmp_p = NULL;
    for (tmp = sll->head; tmp != NULL; tmp = tmp->next) {
        if (tmp->key == key) {
            struct hash_set_node *rmv = tmp;
            if (tmp_p != NULL)
                tmp_p->next = rmv->next;
            else
                sll->head->next = rmv->next;
            FREE(rmv);
            
            return 0;
        }

        tmp_p = tmp;
    }

    return -1;
}

static int
hash_set_resize(hash_set *set, size_t new_size)
{
    struct sll *old = set->sll;
    size_t old_size = set->sll_len;
    set->sll_len = new_size;
    set->sll = malloc(sizeof(struct sll) * set->sll_len);
    for (size_t i = 0; i < set->sll_len; i++)
        set->sll[i].head = set->sll[i].tail = NULL;
    set->len = 0;

    struct hash_set_node *node;
    for (size_t i = 0; i < old_size; i++)
        for (node = old[i].head; node != NULL; node = node->next)
            if (hash_set_insert(set, node->key))
                return -1;
    FREE(old);

    return 0;
}

hash_set
hash_set_new()
{
    hash_set set;
    set.sll = malloc(sizeof(struct sll) * INIT_LEN);
    for (size_t i = 0; i < INIT_LEN; i++)
        set.sll[i].head = set.sll[i].tail = NULL;
    set.sll_len = INIT_LEN;
    set.len = 0;
    memset(set.key, 0, sizeof(set.key)); /* DEBUG, shall not be used */

    return set;
}

int
hash_set_insert(hash_set *set, const int key)
{
    if (set->sll_len < set->len)
        return -1;
    if (set->sll_len == set->len)
        hash_set_resize(set, set->sll_len * 2);
    
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;
    if (sll_push_back(&set->sll[idx], key))
        return -1;

    set->len++;

    return 0;
}

int
hash_set_remove(hash_set *set, const int key)
{
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;
    if (sll_remove(&set->sll[idx], key))
        return -1;

    set->len--;

    if (set->len > INIT_LEN * 2 && set->sll_len / 3 >= set->len)
        if (hash_set_resize(set, set->sll_len / 2))
            return -1;

    return 0;
}

int
hash_set_search(hash_set *set, const int key)
{
    size_t idx = siphash24(&key, sizeof(key), set->key) % set->sll_len;
    struct hash_set_node *tmp;
    for (tmp = set->sll[idx].head; tmp != NULL; tmp = tmp->next) {
        if (tmp->key == key) {
            return 1;
        }
    }

    return 0;
}

void
hash_set_free(hash_set set)
{
    FREE(set.sll);
}
