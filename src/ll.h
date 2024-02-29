typedef int type;

#ifndef _LL_H
#define _LL_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
    struct sll_node *root;
    size_t len;
} sll;

struct sll_node {
    type data;
    struct sll_node *next;
};

static sll
sll_new()
{
    sll ll = { NULL, 0 };
    return ll;
}

static sll
sll_copy(const sll old)
{
    struct sll_node *old_tmp, *cpy_tmp;
    sll cpy;

    if (old.root == NULL)
        return sll_new();

    cpy_tmp = cpy.root = malloc(sizeof(struct sll_node));
    for (old_tmp = old.root; old_tmp != NULL; old_tmp = old_tmp->next) {
        cpy_tmp->data = old_tmp->data;
        cpy_tmp->next = old_tmp->next ? malloc(sizeof(struct sll_node)) : NULL;

        cpy_tmp = cpy_tmp->next;
    }

    cpy.len = old.len;

    return cpy;
}

static void
sll_free(sll *ll)
{
    struct sll_node *tmp, *next;

    for (tmp = ll->root; tmp != NULL; tmp = next) {
        next = tmp->next;
        free(tmp);
    }

    ll->root = NULL;
    ll->len = 0;
}

static int
sll_push(sll *ll, const type data)
{
    struct sll_node *tmp = malloc(sizeof(struct sll_node));
    tmp->data = data;
    tmp->next = ll->root;

    ll->root = tmp;
    ll->len++;

    return 0;
}

static int
sll_pop(sll *ll, type *data)
{
    struct sll_node *next;
    
    if (ll->root == NULL)
        return -1;

    *data = ll->root->data;

    next = ll->root->next;
    free(ll->root);

    ll->root = next;
    ll->len--;

    return 0;
}

static int
sll_insert(sll *ll, const type data, const size_t at)
{
    struct sll_node *tmp, *new; 
    size_t i;

    for (tmp = ll->root, i = 0; i < at - 1; tmp = tmp->next, i++)
        if (tmp == NULL)
            return -1;

    new = malloc(sizeof(struct sll_node));
    new->data = data;
    new->next = tmp->next;
    tmp->next = new;

    ll->len++;

    return 0;
}

static size_t
sll_search(const sll *ll, const type data)
{
    struct sll_node *tmp;
    size_t i;

    for (tmp = ll->root, i = 0; tmp != NULL; tmp = tmp->next, i++)
        if (tmp->data == data)
            break;

    return i;
}

static size_t
sll_remove(sll *ll, const type data)
{
    struct sll_node *tmp, *prv;
    size_t i;

    for (tmp = ll->root, i = 0; tmp != NULL; tmp = tmp->next, i++) {
        if (tmp->data == data)
            break;

        prv = tmp;
    }

    if (tmp == NULL)
        return i;

    prv->next = tmp->next;
    free(tmp);
    ll->len--;

    return i;
}

static int
sll_getnth(const sll *ll, type *data, const size_t at)
{
    struct sll_node *tmp;
    size_t i;

    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)
        if (tmp == NULL)
            return -1;

    *data = tmp->data;

    return 0;
}

static int
sll_setnth(const sll *ll, const type data, const size_t at)
{
    struct sll_node *tmp;
    size_t i;

    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)
        if (tmp == NULL)
            return -1;

    tmp->data = data;

    return 0;
}

static int
sll_rmvnth(sll *ll, type *data, const size_t at)
{
    struct sll_node *tmp, *prv;
    size_t i;

    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++) {
        if (tmp == NULL)
            return -1;

        prv = tmp;
    }

    *data = tmp->data;

    prv->next = tmp->next;
    free(tmp);
    ll->len--;

    return 0;
}

static type *
sll_nthptr(const sll *ll, const size_t at)
{
    struct sll_node *tmp;
    size_t i;

    for (tmp = ll->root, i = 0; i < at; tmp = tmp->next, i++)
        if (tmp == NULL)
            return NULL;

    return &tmp->data;
}

static type *
sll_first(const sll *ll)
{
    return &ll->root->data;
}

static type *
sll_last(const sll *ll)
{
    return sll_nthptr(ll, ll->len - 1);
}

static size_t
sll_length(const sll *ll)
{
    return ll->len;
}

#define INIT_DLL(name, type)

typedef struct {
    struct dll_node *head, *tail;
    size_t len;
} dll;

struct dll_node {
    type data;
    struct dll_node *prev, *next;
};

static dll
dll_new()
{
    dll ll = { NULL, NULL, 0 };
    return ll;
}

static dll
dll_copy(const dll old)
{
    struct dll_node *old_tmp, *cpy_tmp, *tmp_prv = NULL;
    dll cpy;

    if (old.head == NULL)
        return dll_new();

    cpy_tmp = cpy.head = malloc(sizeof(struct dll_node));
    for (old_tmp = old.head; old_tmp != NULL; old_tmp = old_tmp->next) {
        cpy_tmp->data = old_tmp->data;
        cpy_tmp->next = old_tmp->next ? malloc(sizeof(struct dll_node)) : NULL;
        cpy_tmp->prev = tmp_prv;

        tmp_prv = cpy_tmp;
        cpy_tmp = cpy_tmp->next;
    }

    cpy.tail = tmp_prv;
    cpy.len = old.len;

    return cpy;
}

static int
dll_push_back(dll *ll, const type data)
{
    struct dll_node *prev = ll->tail;

    if (ll->head == NULL && ll->tail == NULL)
        ll->head = ll->tail = malloc(sizeof(struct dll_node));
    else
        ll->tail = ll->tail->next = malloc(sizeof(struct dll_node));

    ll->tail->data = data;
    ll->tail->next = NULL;
    ll->tail->prev = prev;
    ll->len++;

    return 0;
}

static int
dll_push_front(dll *ll, const type data)
{
    if (ll->head == NULL && ll->tail == NULL)
        ll->head = ll->tail = malloc(sizeof(struct dll_node));
    else
        ll->head = ll->head->prev = malloc(sizeof(struct dll_node));

    ll->head->data = data;
    ll->head->next = ll->head;
    ll->head->prev = NULL;
    ll->len++;

    return 0;
}

static int
dll_pop_back(dll *ll, type *data)
{
    if (ll->len == 0 || ll->head == NULL || ll->tail == NULL)
        return -1;

    *data = ll->tail->data;
    
    ll->tail = ll->tail->prev;
    free(ll->tail->next);
    ll->len--;

    return 0;
}

static int
dll_pop_front(dll *ll, type *data)
{
    if (ll->len == 0 || ll->head == NULL || ll->tail == NULL)
        return -1;

    *data = ll->head->data;

    ll->head = ll->head->next;
    free(ll->head->prev);
    ll->len--;

    return 0;
}

static int
dll_insert(dll *ll, const type data, const size_t at)
{
    size_t i;
    struct dll_node *tmp, *new;

    if (ll->len <= at)
        return -1;

    if (at < ll->len / 2) {
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)
            if (tmp == NULL)
                return -1;
    } else {
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)
            if (tmp == NULL)
                return -1;
    }

    new = malloc(sizeof(struct dll_node));
    new->data = data;
    new->next = tmp->next;
    new->prev = tmp->prev;

    tmp->prev->next = new;
    tmp->next->prev = new;

    ll->len++;

    return 0;
}

static size_t
dll_search(dll *ll, const type data)
{
    size_t i;
    struct dll_node *tmp;

    for (i = 0, tmp = ll->head; tmp != NULL; i++, tmp = tmp->next)
        if (tmp->data == data)
            break;

    return i;
}

static size_t
dll_remove(dll *ll, const type data)
{
    size_t i;
    struct dll_node *tmp;

    for (i = 0, tmp = ll->head; tmp != NULL; i++, tmp = tmp->next) {
        if (tmp->data == data) {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp);

            break;
        }
    }

    return i;
}

static int
dll_getnth(const dll *ll, type *data, const size_t at)
{
    size_t i;
    struct dll_node *tmp;

    if (ll->len <= at)
        return -1;

    if (at < ll->len / 2) {
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)
            if (tmp == NULL)
                return -1;
    } else {
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)
            if (tmp == NULL)
                return -1;
    }

    *data = tmp->data;

    return 0;
}

static int
dll_setnth(const dll *ll, const type data, const size_t at)
{
    size_t i;
    struct dll_node *tmp;

    if (ll->len <= at)
        return -1;

    if (at < ll->len / 2) {
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)
            if (tmp == NULL)
                return -1;
    } else {
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)
            if (tmp == NULL)
                return -1;
    }

    tmp->data = data;

    return 0;
}

static int
dll_rmvnth(dll *ll, type *data, const size_t at)
{
    size_t i;
    struct dll_node *tmp;

    if (ll->len <= at)
        return -1;

    if (at < ll->len / 2) {
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)
            if (tmp == NULL)
                return -1;
    } else {
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)
            if (tmp == NULL)
                return -1;
    }

    *data = tmp->data;

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);

    ll->len--;

    return 0;
}

static type *
dll_nthptr(dll *ll, const size_t at)
{
    struct dll_node *tmp;
    size_t i;

    if (ll->len <= at)
        return NULL;

    if (at < ll->len / 2) {
        for (i = 0, tmp = ll->head; i != at; i++, tmp = tmp->next)
            if (tmp == NULL)
                return NULL;
    } else {
        for (i = ll->len - 1, tmp = ll->tail; i != at; i--, tmp = tmp->prev)
            if (tmp == NULL)
                return NULL;
    }

    return &tmp->data;
}

static type *
dll_first(dll *ll)
{
    return &ll->head->data;
}

static type *
dll_last(dll *ll)
{
    return &ll->tail->data;
}

static size_t
dll_length(const dll *ll)
{
    return ll->len;
}

#endif
