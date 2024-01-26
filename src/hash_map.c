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

#include "hash_map.h"
#include <stdlib.h>
#include <string.h>
#define INIT_LEN 16
#define FREE(ptr)   \
free(ptr);          \
ptr = NULL;

static int
sll_push_back(struct sll *sll, const int key, const int val)
{
    if (sll->head == NULL) {
        sll->head = sll->tail = malloc(sizeof(struct hash_map_node));
        sll->head->key = key;
        sll->head->val = val;
        sll->head->next = NULL;
    } else {
        sll->tail->next = malloc(sizeof(struct hash_map_node));
        sll->tail->next->key = key;
        sll->tail->next->val = val;
        sll->tail->next->next = NULL;
        sll->tail = sll->tail->next;
    }

    return 0;
}

static int
sll_remove(struct sll *sll, const int key, int *val)
{
    struct hash_map_node *tmp, *tmp_p = NULL;
    for (tmp = sll->head; tmp != NULL; tmp = tmp->next) {
        if (tmp->key == key) {
            struct hash_map_node *rmv = tmp;
            *val = rmv->val;
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
hash_map_resize(hash_map *map, size_t new_size)
{
    struct sll *old = map->sll;
    size_t old_size = map->sll_len;
    map->sll_len = new_size;
    map->sll = malloc(sizeof(struct sll) * map->sll_len);
    for (size_t i = 0; i < map->sll_len; i++)
        map->sll[i].head = map->sll[i].tail = NULL;
    map->len = 0;

    struct hash_map_node *node;
    for (size_t i = 0; i < old_size; i++)
        for (node = old[i].head; node != NULL; node = node->next)
            if (hash_map_insert(map, node->key, node->val))
                return -1;
    FREE(old);

    return 0;
}

hash_map
hash_map_new()
{
    hash_map map;
    map.sll = malloc(sizeof(struct sll) * INIT_LEN);
    for (size_t i = 0; i < INIT_LEN; i++)
        map.sll[i].head = map.sll[i].tail = NULL;
    map.sll_len = INIT_LEN;
    map.len = 0;
    memset(map.key, 0, sizeof(map.key)); /* DEBUG, shall not be used */

    return map;
}

int
hash_map_insert(hash_map *map, const int key, const int val)
{
    if (map->sll_len < map->len)
        return -1;
    if (map->sll_len == map->len)
        hash_map_resize(map, map->sll_len * 2);
    
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;
    if (sll_push_back(&map->sll[idx], key, val))
        return -1;

    map->len++;

    return 0;
}

int
hash_map_remove(hash_map *map, const int key, int *val)
{
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;
    if (sll_remove(&map->sll[idx], key, val))
        return -1;

    map->len--;

    if (map->len > INIT_LEN * 2 && map->sll_len / 3 >= map->len)
        if (hash_map_resize(map, map->sll_len / 2))
            return -1;

    return 0;
}

int
hash_map_search(hash_map *map, const int key, int *val)
{
    size_t idx = siphash24(&key, sizeof(key), map->key) % map->sll_len;
    struct hash_map_node *tmp;
    for (tmp = map->sll[idx].head; tmp != NULL; tmp = tmp->next) {
        if (tmp->key == key) {
            *val = tmp->val;
            return 0;
        }
    }

    return -1;
}

void
hash_map_free(hash_map map)
{
    FREE(map.sll);
}
