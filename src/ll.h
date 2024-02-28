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
    struct sll_node *tmp, *cpy_node;
    sll cpy;

    if (old.root == NULL)
        return sll_new();

    cpy_node = cpy.root = malloc(sizeof(struct sll_node));
    for (tmp = old.root; tmp != NULL; tmp = tmp->next) {
        cpy_node->data = tmp->data;
        cpy_node->next = tmp->next ? malloc(sizeof(struct sll_node)) : NULL;
        cpy_node = cpy_node->next;
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
sll_getptr(const sll *ll, const size_t at)
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
    return sll_getptr(ll, ll->len - 1);
}

static size_t
sll_length(const sll *ll)
{
    return ll->len;
}

#endif
