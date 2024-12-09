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
 * If not, see <http://creatiheapommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <stddef.h>
#include <string.h>

#define PARENT(i) (((i) - 1) >> 1)

#define INIT_HEAP_TYPE(name, type)                                             \
struct heap_##name {                                                           \
        type *arr;                                                             \
        size_t cap, len;                                                       \
};                                                                             \
                                                                               \
struct heap_##name##_iter {                                                    \
        struct heap_##name *heap;                                              \
        size_t idx;                                                            \
};                                                                             \
                                                                               \
struct heap_##name heap_##name##_new(void);                                    \
struct heap_##name heap_##name##_from(const type *, const size_t);             \
struct heap_##name heap_##name##_copy(const struct heap_##name *);             \
int heap_##name##_push(struct heap_##name *, const type);                      \
int heap_##name##_pop(struct heap_##name *, type *);                           \
int heap_##name##_get(struct heap_##name *, type *);                           \
int heap_##name##_set(struct heap_##name *, const type);                       \
size_t heap_##name##_len(struct heap_##name *);                                \
void heap_##name##_free(struct heap_##name *);                                 \
                                                                               \
struct heap_##name##_iter heap_##name##_iter(struct heap_##name *);            \
int heap_##name##_next(struct heap_##name##_iter *, type *);                   \
                                                                               \
extern int _heap_type_##name

#define INIT_HEAP_FUNC(name, type, cmp, ord, malloc, realloc, free)            \
static int                                                                     \
heap_##name##_extend(struct heap_##name *heap, const size_t len)               \
{                                                                              \
        if (heap->len < heap->cap)                                             \
                return 0;                                                      \
        if (heap->cap == 0)                                                    \
                heap->cap = 1;                                                 \
        for (; heap->cap < len; heap->cap <<= 1)                               \
                ;                                                              \
        if ((heap->arr = realloc(heap->arr, heap->cap * sizeof(type))) == NULL)\
                return -1;                                                     \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
static void                                                                    \
heap_##name##_heapify(struct heap_##name *heap)                                \
{                                                                              \
        size_t i;                                                              \
        type tmp;                                                              \
                                                                               \
        for (i = heap->len - 1; i; i = PARENT(i)) {                            \
                if (cmp(heap->arr[i], heap->arr[PARENT(i)]) ord 0) {           \
                        tmp = heap->arr[i];                                    \
                        heap->arr[i] = heap->arr[PARENT(i)];                   \
                        heap->arr[PARENT(i)] = tmp;                            \
                }                                                              \
        }                                                                      \
}                                                                              \
                                                                               \
struct heap_##name                                                             \
heap_##name##_new(void)                                                        \
{                                                                              \
        struct heap_##name heap;                                               \
                                                                               \
        heap.arr = malloc(0);                                                  \
        heap.cap = heap.len = 0;                                               \
                                                                               \
        return heap;                                                           \
}                                                                              \
                                                                               \
struct heap_##name                                                             \
heap_##name##_from(const type *arr, const size_t len)                          \
{                                                                              \
        struct heap_##name heap;                                               \
        size_t i;                                                              \
                                                                               \
        heap = heap_##name##_new();                                            \
                                                                               \
        for (i = 0; i < len; i++)                                              \
                if (heap_##name##_push(&heap, arr[i]))                         \
                        break;                                                 \
                                                                               \
        return heap;                                                           \
}                                                                              \
                                                                               \
struct heap_##name                                                             \
heap_##name##_copy(const struct heap_##name *heap)                             \
{                                                                              \
        return heap_##name##_from(heap->arr, heap->len);                       \
}                                                                              \
                                                                               \
int                                                                            \
heap_##name##_push(struct heap_##name *heap, const type val)                   \
{                                                                              \
        if (heap->arr == NULL)                                                 \
                return -1;                                                     \
        if (heap_##name##_extend(heap, heap->len + 1))                         \
                return -1;                                                     \
                                                                               \
        heap->arr[heap->len++] = val;                                          \
        heap_##name##_heapify(heap);                                           \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
heap_##name##_pop(struct heap_##name *heap, type *val)                         \
{                                                                              \
        if (heap->arr == NULL || heap->cap == 0 || heap->len == 0)             \
                return -1;                                                     \
                                                                               \
        *val = heap->arr[0];                                                   \
        heap->arr[0] = heap->arr[heap->len - 1];                               \
        heap_##name##_heapify(heap);                                           \
        heap->len--;                                                           \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
heap_##name##_get(struct heap_##name *heap, type *val)                         \
{                                                                              \
        size_t i;                                                              \
                                                                               \
        if (heap->arr == NULL || heap->cap == 0 || heap->len == 0)             \
                return -1;                                                     \
                                                                               \
        for (i = 0; i < heap->len; i++) {                                      \
                if (cmp(*val, heap->arr[i]) != 0)                              \
                        continue;                                              \
                                                                               \
                *val = heap->arr[i];                                           \
                                                                               \
                return 0;                                                      \
        }                                                                      \
                                                                               \
        return -1;                                                             \
}                                                                              \
                                                                               \
int                                                                            \
heap_##name##_set(struct heap_##name *heap, const type val)                    \
{                                                                              \
        size_t i;                                                              \
                                                                               \
        if (heap->arr == NULL || heap->cap == 0 || heap->len == 0)             \
                return -1;                                                     \
                                                                               \
        for (i = 0; i < heap->len; i++) {                                      \
                if (cmp(val, heap->arr[i]) != 0)                               \
                        continue;                                              \
                                                                               \
                heap->arr[i] = val;                                            \
                                                                               \
                return 0;                                                      \
        }                                                                      \
                                                                               \
        return -1;                                                             \
}                                                                              \
                                                                               \
size_t                                                                         \
heap_##name##_len(struct heap_##name *heap)                                    \
{                                                                              \
        return heap->len;                                                      \
}                                                                              \
                                                                               \
void                                                                           \
heap_##name##_free(struct heap_##name *heap)                                   \
{                                                                              \
        free(heap->arr);                                                       \
        heap->arr = NULL;                                                      \
        heap->cap = heap->len = 0;                                             \
}                                                                              \
                                                                               \
struct heap_##name##_iter                                                      \
heap_##name##_iter(struct heap_##name *heap)                                   \
{                                                                              \
        struct heap_##name##_iter iter;                                        \
                                                                               \
        iter.heap = heap;                                                      \
        iter.idx = 0;                                                          \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
heap_##name##_next(struct heap_##name##_iter *iter, type *val)                 \
{                                                                              \
        if (iter->idx == iter->heap->len)                                      \
                return -1;                                                     \
                                                                               \
        *val = iter->heap->arr[iter->idx++];                                   \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
extern int _heap_func_##name

#define INIT_MAX_HEAP_FUNC(name, type, cmp, malloc, realloc, free)             \
INIT_HEAP_FUNC(name, type, cmp, >, malloc, realloc, free)

#define INIT_MIN_HEAP_FUNC(name, type, cmp, malloc, realloc, free)             \
INIT_HEAP_FUNC(name, type, cmp, <, malloc, realloc, free)

#define INIT_MAX_HEAP_BOTH(name, type, cmp, malloc, realloc, free)             \
INIT_HEAP_TYPE(name, type);                                                    \
INIT_MAX_HEAP_FUNC(name, type, cmp, malloc, realloc, free)

#define INIT_MIN_HEAP_BOTH(name, type, cmp, malloc, realloc, free)             \
INIT_HEAP_TYPE(name, type);                                                    \
INIT_MIN_HEAP_FUNC(name, type, cmp, malloc, realloc, free)

#define FOR_EACH_HEAP(name, elem, iter) while (!heap_##name##_next(&iter, &elem))

#endif
