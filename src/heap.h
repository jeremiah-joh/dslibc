/*
 * dslibc - collection of useful data structures written in ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creatiheapommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define PAR(i) (((i) - 1) >> 1)

#define INIT_HEAP_TYPE(name, type)                                            \
struct heap_##name {                                                          \
        type *arr;                                                            \
        size_t cap, len, nxt;                                                 \
};                                                                            \
                                                                              \
struct heap_##name heap_##name##_new();                                       \
struct heap_##name heap_##name##_from(const type *, const size_t);            \
struct heap_##name heap_##name##_copy(const struct heap_##name);              \
int heap_##name##_push(struct heap_##name *, const type);                     \
int heap_##name##_pop(struct heap_##name *, type *);                          \
type *heap_##name##_root(struct heap_##name *);                               \
type *heap_##name##_next(struct heap_##name *);                               \
void heap_##name##_free(struct heap_##name *) /* to enforce semicolon */

#define INIT_HEAP_FUNC(name, type, cmp, ord)                                  \
static size_t                                                                 \
heap_##name##_cap(const size_t len)                                           \
{                                                                             \
        size_t cap;                                                           \
                                                                              \
        for (cap = 4; cap < len; cap <<= 1)                                   \
                ;                                                             \
                                                                              \
        return cap;                                                           \
}                                                                             \
                                                                              \
static int                                                                    \
heap_##name##_resize(struct heap_##name *heap, const size_t len)              \
{                                                                             \
        heap->cap = heap_##name##_cap(len);                                   \
                                                                              \
        return (heap->arr = realloc(heap->arr, sizeof(type) * heap->cap))     \
                ? 0 : -1;                                                     \
}                                                                             \
                                                                              \
static void                                                                   \
heap_##name##_heapify(struct heap_##name *heap)                               \
{                                                                             \
        size_t i;                                                             \
        type tmp;                                                             \
                                                                              \
        for (i = heap->len - 1; i; i = PAR(i)) {                              \
                if (cmp(heap->arr[i], heap->arr[PAR(i)]) ord 0) {             \
                        tmp = heap->arr[i];                                   \
                        heap->arr[i] = heap->arr[PAR(i)];                     \
                        heap->arr[PAR(i)] = tmp;                              \
                }                                                             \
        }                                                                     \
}                                                                             \
                                                                              \
struct heap_##name                                                            \
heap_##name##_new()                                                           \
{                                                                             \
        struct heap_##name heap;                                              \
                                                                              \
        heap.arr = malloc(0);                                                 \
        heap.cap = heap.len = heap.nxt = 0;                                   \
                                                                              \
        return heap;                                                          \
}                                                                             \
                                                                              \
struct heap_##name                                                            \
heap_##name##_from(const type val[], const size_t len)                        \
{                                                                             \
        size_t i;                                                             \
        struct heap_##name heap;                                              \
                                                                              \
        heap = heap_##name##_new();                                           \
                                                                              \
        for (i = 0; i < len; i++)                                             \
                if (heap_##name##_push(&heap, val[i]))                        \
                        return heap;                                          \
                                                                              \
        return heap;                                                          \
}                                                                             \
                                                                              \
struct heap_##name                                                            \
heap_##name##_copy(const struct heap_##name heap)                             \
{                                                                             \
        struct heap_##name copy;                                              \
                                                                              \
        copy.arr = malloc(sizeof(type) * heap.cap);                           \
        copy.cap = heap.cap;                                                  \
        copy.len = heap.len;                                                  \
        copy.nxt = heap.nxt;                                                  \
                                                                              \
        memcpy(copy.arr, heap.arr, sizeof(type) * heap.cap);                  \
                                                                              \
        return copy;                                                          \
}                                                                             \
                                                                              \
int                                                                           \
heap_##name##_push(struct heap_##name *heap, type val)                        \
{                                                                             \
        if (heap->len == heap->cap)                                           \
                if (heap_##name##_resize(heap, heap->len + 1))                \
                        return -1;                                            \
                                                                              \
        heap->arr[heap->len] = val;                                           \
        heap->len++;                                                          \
                                                                              \
        heap_##name##_heapify(heap);                                          \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
heap_##name##_pop(struct heap_##name *heap, type *val)                        \
{                                                                             \
        if (heap->len < heap->cap / 2)                                        \
                if (heap_##name##_resize(heap, heap->len))                    \
                        return -1;                                            \
                                                                              \
        *val = heap->arr[0];                                                  \
        heap->arr[0] = heap->arr[heap->len - 1];                              \
        heap->len--;                                                          \
                                                                              \
        heap_##name##_heapify(heap);                                          \
                                                                              \
        return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
heap_##name##_root(struct heap_##name *heap)                                  \
{                                                                             \
        return &heap->arr[0];                                                 \
}                                                                             \
                                                                              \
type *                                                                        \
heap_##name##_next(struct heap_##name *heap)                                  \
{                                                                             \
        if (heap->nxt < heap->len)                                            \
                return &heap->arr[heap->nxt++];                               \
                                                                              \
        heap->nxt = 0;                                                        \
                                                                              \
        return NULL;                                                          \
}                                                                             \
                                                                              \
void                                                                          \
heap_##name##_free(struct heap_##name *heap)                                  \
{                                                                             \
        free(heap->arr);                                                      \
        heap->arr = NULL;                                                     \
        heap->cap = heap->len = heap->nxt = 0;                                \
}                                                                             \
                                                                              \
struct heap_##name##_semi { /* to enforce semicolon */ }

#define FOR_EACH(name, p, heap)                                               \
for (heap.nxt = 0; ((p) = heap_##name##_next(&heap)); )

#define INIT_MIN_HEAP_FUNC(name, type, cmp) INIT_HEAP_FUNC(name, type, cmp, <);
#define INIT_MAX_HEAP_FUNC(name, type, cmp) INIT_HEAP_FUNC(name, type, cmp, >);

#define INIT_MIN_HEAP(name, type, cmp)                                        \
INIT_HEAP_TYPE(name, type);                                                   \
INIT_MIN_HEAP_FUNC(name, type, cmp)

#define INIT_MAX_HEAP(name, type, cmp)                                        \
INIT_HEAP_TYPE(name, type);                                                   \
INIT_MAX_HEAP_FUNC(name, type, cmp)

#endif
