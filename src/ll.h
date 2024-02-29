#ifndef _LL_H
#define _LL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_SLL(name, type)                                                  \
                                                                              \
typedef struct {                                                              \
    struct sll_##name##_node *root;                                           \
    size_t len;                                                               \
} sll_##name;                                                                 \
                                                                              \
struct sll_##name##_node {                                                    \
    type data;                                                                \
    struct sll_##name##_node *next;                                           \
};                                                                            \
                                                                              \
static sll_##name                                                             \
sll_##name##_new()                                                            \
{                                                                             \
    sll_##name ll = { NULL, 0 };                                              \
    return ll;                                                                \
}                                                                             \
                                                                              \
static sll_##name                                                             \
sll_##name##_copy(const sll_##name old)                                       \
{                                                                             \
    struct sll_##name##_node *old_tmp, *cpy_tmp;                              \
    sll_##name cpy;                                                           \
                                                                              \
    if (old.root == NULL)                                                     \
        return sll_##name##_new();                                            \
                                                                              \
    cpy_tmp = cpy.root = malloc(sizeof(struct sll_##name##_node));            \
    for (old_tmp = old.root; old_tmp != NULL; old_tmp = old_tmp->next) {      \
        cpy_tmp->data = old_tmp->data;                                        \
        cpy_tmp->next                                                         \
            = old_tmp->next ? malloc(sizeof(struct sll_##name##_node)) : NULL;\
                                                                              \
        cpy_tmp = cpy_tmp->next;                                              \
    }                                                                         \
                                                                              \
    cpy.len = old.len;                                                        \
                                                                              \
    return cpy;                                                               \
}                                                                             \
                                                                              \
static void                                                                   \
sll_##name##_free(sll_##name *ll)                                             \
{                                                                             \
    struct sll_##name##_node *tmp, *next;                                     \
                                                                              \
    for (tmp = ll->root; tmp != NULL; tmp = next) {                           \
        next = tmp->next;                                                     \
        free(tmp);                                                            \
    }                                                                         \
                                                                              \
    ll->root = NULL;                                                          \
    ll->len = 0;                                                              \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_push(sll_##name *ll, const type data)                            \
{                                                                             \
    struct sll_##name##_node *tmp = malloc(sizeof(struct sll_##name##_node)); \
    tmp->data = data;                                                         \
    tmp->next = ll->root;                                                     \
                                                                              \
    ll->root = tmp;                                                           \
    ll->len++;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_pop(sll_##name *ll, type *data)                                  \
{                                                                             \
    struct sll_##name##_node *next;                                           \
                                                                              \
    if (ll->root == NULL)                                                     \
        return -1;                                                            \
                                                                              \
    *data = ll->root->data;                                                   \
                                                                              \
    next = ll->root->next;                                                    \
    free(ll->root);                                                           \
                                                                              \
    ll->root = next;                                                          \
    ll->len--;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_insert(sll_##name *ll, const type data, const size_t at)         \
{                                                                             \
    struct sll_##name##_node *tmp, *new;                                      \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; i < at - 1; tmp = tmp->next, i++)             \
        if (tmp == NULL)                                                      \
            return -1;                                                        \
                                                                              \
    new = malloc(sizeof(struct sll_##name##_node));                           \
    new->data = data;                                                         \
    new->next = tmp->next;                                                    \
    tmp->next = new;                                                          \
                                                                              \
    ll->len++;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static size_t                                                                 \
sll_##name##_search(const sll_##name *ll, const type data)                    \
{                                                                             \
    struct sll_##name##_node *tmp;                                            \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; tmp != NULL; tmp = tmp->next, i++)            \
        if (tmp->data == data)                                                \
            break;                                                            \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
static size_t                                                                 \
sll_##name##_remove(sll_##name *ll, const type data)                          \
{                                                                             \
    struct sll_##name##_node *tmp, *prv;                                      \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; tmp != NULL; tmp = tmp->next, i++) {          \
        if (tmp->data == data)                                                \
            break;                                                            \
                                                                              \
        prv = tmp;                                                            \
    }                                                                         \
                                                                              \
    if (tmp == NULL)                                                          \
        return i;                                                             \
                                                                              \
    prv->next = tmp->next;                                                    \
    free(tmp);                                                                \
    ll->len--;                                                                \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_getnth(const sll_##name *ll, type *data, const size_t at)        \
{                                                                             \
    struct sll_##name##_node *tmp;                                            \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)                 \
        if (tmp == NULL)                                                      \
            return -1;                                                        \
                                                                              \
    *data = tmp->data;                                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_setnth(const sll_##name *ll, const type data, const size_t at)   \
{                                                                             \
    struct sll_##name##_node *tmp;                                            \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)                 \
        if (tmp == NULL)                                                      \
            return -1;                                                        \
                                                                              \
    tmp->data = data;                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
sll_##name##_rmvnth(sll_##name *ll, type *data, const size_t at)              \
{                                                                             \
    struct sll_##name##_node *tmp, *prv;                                      \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++) {               \
        if (tmp == NULL)                                                      \
            return -1;                                                        \
                                                                              \
        prv = tmp;                                                            \
    }                                                                         \
                                                                              \
    *data = tmp->data;                                                        \
                                                                              \
    prv->next = tmp->next;                                                    \
    free(tmp);                                                                \
    ll->len--;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static type *                                                                 \
sll_##name##_nthptr(const sll_##name *ll, const size_t at)                    \
{                                                                             \
    struct sll_##name##_node *tmp;                                            \
    size_t i;                                                                 \
                                                                              \
    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)                 \
        if (tmp == NULL)                                                      \
            return NULL;                                                      \
                                                                              \
    return &tmp->data;                                                        \
}                                                                             \
                                                                              \
static type *                                                                 \
sll_##name##_first(const sll_##name *ll)                                      \
{                                                                             \
    return &ll->root->data;                                                   \
}                                                                             \
                                                                              \
static type *                                                                 \
sll_##name##_last(const sll_##name *ll)                                       \
{                                                                             \
    return sll_##name##_nthptr(ll, ll->len - 1);                              \
}                                                                             \
                                                                              \
static size_t                                                                 \
sll_##name##_length(const sll_##name *ll)                                     \
{                                                                             \
    return ll->len;                                                           \
}                                                                             \
                                                                              \
struct _sll_##name { /* to enforce semicolon */ }

#define INIT_DLL(name, type)                                                  \
                                                                              \
typedef struct {                                                              \
    struct dll_##name##_node *head, *tail;                                    \
    size_t len;                                                               \
} dll_##name;                                                                 \
                                                                              \
struct dll_##name##_node {                                                    \
    type data;                                                                \
    struct dll_##name##_node *prev, *next;                                    \
};                                                                            \
                                                                              \
static dll_##name                                                             \
dll_##name##_new()                                                            \
{                                                                             \
    dll_##name ll = { NULL, NULL, 0 };                                        \
    return ll;                                                                \
}                                                                             \
                                                                              \
static dll_##name                                                             \
dll_##name##_copy(const dll_##name old)                                       \
{                                                                             \
    struct dll_##name##_node *old_tmp, *cpy_tmp, *tmp_prv = NULL;             \
    dll_##name cpy;                                                           \
                                                                              \
    if (old.head == NULL)                                                     \
        return dll_##name##_new();                                            \
                                                                              \
    cpy_tmp = cpy.head = malloc(sizeof(struct dll_##name##_node));            \
    for (old_tmp = old.head; old_tmp != NULL; old_tmp = old_tmp->next) {      \
        cpy_tmp->data = old_tmp->data;                                        \
        cpy_tmp->next                                                         \
            = old_tmp->next ? malloc(sizeof(struct dll_##name##_node)) : NULL;\
        cpy_tmp->prev = tmp_prv;                                              \
                                                                              \
        tmp_prv = cpy_tmp;                                                    \
        cpy_tmp = cpy_tmp->next;                                              \
    }                                                                         \
                                                                              \
    cpy.tail = tmp_prv;                                                       \
    cpy.len = old.len;                                                        \
                                                                              \
    return cpy;                                                               \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_push_back(dll_##name *ll, const type data)                       \
{                                                                             \
    struct dll_##name##_node *prev = ll->tail;                                \
                                                                              \
    if (ll->head == NULL && ll->tail == NULL)                                 \
        ll->head = ll->tail = malloc(sizeof(struct dll_##name##_node));       \
    else                                                                      \
        ll->tail = ll->tail->next = malloc(sizeof(struct dll_##name##_node)); \
                                                                              \
    ll->tail->data = data;                                                    \
    ll->tail->next = NULL;                                                    \
    ll->tail->prev = prev;                                                    \
    ll->len++;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_push_front(dll_##name *ll, const type data)                      \
{                                                                             \
    if (ll->head == NULL && ll->tail == NULL)                                 \
        ll->head = ll->tail = malloc(sizeof(struct dll_##name##_node));       \
    else                                                                      \
        ll->head = ll->head->prev = malloc(sizeof(struct dll_##name##_node)); \
                                                                              \
    ll->head->data = data;                                                    \
    ll->head->next = ll->head;                                                \
    ll->head->prev = NULL;                                                    \
    ll->len++;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_pop_back(dll_##name *ll, type *data)                             \
{                                                                             \
    if (ll->len == 0 || ll->head == NULL || ll->tail == NULL)                 \
        return -1;                                                            \
                                                                              \
    *data = ll->tail->data;                                                   \
                                                                              \
    ll->tail = ll->tail->prev;                                                \
    free(ll->tail->next);                                                     \
    ll->len--;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_pop_front(dll_##name *ll, type *data)                            \
{                                                                             \
    if (ll->len == 0 || ll->head == NULL || ll->tail == NULL)                 \
        return -1;                                                            \
                                                                              \
    *data = ll->head->data;                                                   \
                                                                              \
    ll->head = ll->head->next;                                                \
    free(ll->head->prev);                                                     \
    ll->len--;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_insert(dll_##name *ll, const type data, const size_t at)         \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp, *new;                                      \
                                                                              \
    if (ll->len <= at)                                                        \
        return -1;                                                            \
                                                                              \
    if (at < ll->len / 2) {                                                   \
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)            \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    } else {                                                                  \
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)  \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    }                                                                         \
                                                                              \
    new = malloc(sizeof(struct dll_##name##_node));                           \
    new->data = data;                                                         \
    new->next = tmp->next;                                                    \
    new->prev = tmp->prev;                                                    \
                                                                              \
    tmp->prev->next = new;                                                    \
    tmp->next->prev = new;                                                    \
                                                                              \
    ll->len++;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static size_t                                                                 \
dll_##name##_search(dll_##name *ll, const type data)                          \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp;                                            \
                                                                              \
    for (i = 0, tmp = ll->head; tmp != NULL; i++, tmp = tmp->next)            \
        if (tmp->data == data)                                                \
            break;                                                            \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
static size_t                                                                 \
dll_##name##_remove(dll_##name *ll, const type data)                          \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp;                                            \
                                                                              \
    for (i = 0, tmp = ll->head; tmp != NULL; i++, tmp = tmp->next) {          \
        if (tmp->data == data) {                                              \
            tmp->prev->next = tmp->next;                                      \
            tmp->next->prev = tmp->prev;                                      \
            free(tmp);                                                        \
                                                                              \
            break;                                                            \
        }                                                                     \
    }                                                                         \
                                                                              \
    return i;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_getnth(const dll_##name *ll, type *data, const size_t at)        \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp;                                            \
                                                                              \
    if (ll->len <= at)                                                        \
        return -1;                                                            \
                                                                              \
    if (at < ll->len / 2) {                                                   \
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)            \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    } else {                                                                  \
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)  \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    }                                                                         \
                                                                              \
    *data = tmp->data;                                                        \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_setnth(const dll_##name *ll, const type data, const size_t at)   \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp;                                            \
                                                                              \
    if (ll->len <= at)                                                        \
        return -1;                                                            \
                                                                              \
    if (at < ll->len / 2) {                                                   \
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)            \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    } else {                                                                  \
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)  \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    }                                                                         \
                                                                              \
    tmp->data = data;                                                         \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static int                                                                    \
dll_##name##_rmvnth(dll_##name *ll, type *data, const size_t at)              \
{                                                                             \
    size_t i;                                                                 \
    struct dll_##name##_node *tmp;                                            \
                                                                              \
    if (ll->len <= at)                                                        \
        return -1;                                                            \
                                                                              \
    if (at < ll->len / 2) {                                                   \
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)            \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    } else {                                                                  \
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)  \
            if (tmp == NULL)                                                  \
                return -1;                                                    \
    }                                                                         \
                                                                              \
    *data = tmp->data;                                                        \
                                                                              \
    tmp->prev->next = tmp->next;                                              \
    tmp->next->prev = tmp->prev;                                              \
    free(tmp);                                                                \
                                                                              \
    ll->len--;                                                                \
                                                                              \
    return 0;                                                                 \
}                                                                             \
                                                                              \
static type *                                                                 \
dll_##name##_nthptr(dll_##name *ll, const size_t at)                          \
{                                                                             \
    struct dll_##name##_node *tmp;                                            \
    size_t i;                                                                 \
                                                                              \
    if (ll->len <= at)                                                        \
        return NULL;                                                          \
                                                                              \
    if (at < ll->len / 2) {                                                   \
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)            \
            if (tmp == NULL)                                                  \
                return NULL;                                                  \
    } else {                                                                  \
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)  \
            if (tmp == NULL)                                                  \
                return NULL;                                                  \
    }                                                                         \
                                                                              \
    return &tmp->data;                                                        \
}                                                                             \
                                                                              \
static type *                                                                 \
dll_##name##_first(dll_##name *ll)                                            \
{                                                                             \
    return &ll->head->data;                                                   \
}                                                                             \
                                                                              \
static type *                                                                 \
dll_##name##_last(dll_##name *ll)                                             \
{                                                                             \
    return &ll->tail->data;                                                   \
}                                                                             \
                                                                              \
static size_t                                                                 \
dll_##name##_length(const dll_##name *ll)                                     \
{                                                                             \
    return ll->len;                                                           \
}                                                                             \
                                                                              \
struct _dll_##name { /* to enforce semicolon */ }

#endif
