typedef int type;

#ifndef _LL_H
#define _LL_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
    struct sll_node *head, *tail;
    size_t len;
} sll;

struct sll_node {
    type data;
    struct sll_node *next;
};

static sll
sll_new()
{
    sll ll = { NULL, NULL, 0 };
    return ll;
}

static void
sll_free(sll *ll)
{
    struct sll_node *tmp, *next;
    for (tmp = ll->head; tmp != NULL; tmp = next) {
        next = tmp->next;
        free(tmp);
    }

    ll->head = ll->tail = NULL;
    ll->len = 0;
}

static int
sll_push_back(sll *ll, const type data)
{
    if (ll->head == NULL && ll->tail == NULL)
        ll->head = ll->tail = malloc(sizeof(struct sll_node));
    else
        ll->tail = ll->tail->next = malloc(sizeof(struct sll_node));

    if (ll->tail == NULL)
        return -1;

    ll->tail->data = data;
    ll->tail->next = NULL;
    ll->len++;

    return 0;
}

static int
sll_push_front(sll *ll, const type data)
{
    struct sll_node *tmp = malloc(sizeof(struct sll_node));
    if (tmp == NULL)
        return -1;

    tmp->next = ll->head;
    tmp->data = data;
    ll->len++;
    
    if (ll->head == NULL && ll->tail == NULL)
        ll->tail = tmp;
    ll->head = tmp;

    return 0;
}

#endif
