typedef static int type;

#ifndef _LL_H
#define _LL_H

#include <stddef.h>
#include <stdlib.h>

#define INIT_SLL(name, type)

typedef struct {
    struct sll_node *head, *tail;
    size_t len;
} sll;

struct sll_node {
    type data;
    struct sll_node *next;
};

static int 
sll_push_back(sll *sll, const type val)
{
    if (sll->head == NULL) {
        sll->head = sll->tail = malloc(sizeof(struct sll_node));
        if (sll->head == NULL)
            return -1;

        sll->head->data = val;
        sll->head->next = NULL;
    } else {
        sll->tail = sll->tail->next = malloc(sizeof(struct sll_node));
        if (sll->tail == NULL)
            return -1;

        sll->tail->data = val;
        sll->tail->next = NULL;
    }
    
    sll->len++;

    return 0;
}

static sll 
sll_new()
{
    sll ll = { NULL, NULL, 0 };
    return ll;
}

static void 
sll_free(sll *sll)
{
    struct sll_node *tmp;
    for (tmp = sll->head; tmp != NULL; tmp = tmp->next)
        free(tmp);
    sll->head = sll->tail = NULL;
    sll->len = 0;
}

static sll   
sll_from_arr(const type *arr, const size_t len)
{
    sll ll;
    size_t i;
    for (ll = sll_new(), i = 0; i < len; i++)
        if (sll_push_back(&ll, arr[i]))
            break;

    return ll;
}

static sll
sll_from_sll(const sll sll)
{
    sll ll;
    struct sll_node *tmp;
    for (ll = sll_new(), tmp = sll->head; tmp != NULL; tmp = tmp->next)
        sll_push_back(&ll, tmp->data);

    return ll;
}

static sll 
sll_slice(const sll sll, const size_t head, const size_t tail)
{
    sll sli;
    size_t i;
    struct sll_node *tmp;
    for (tmp = sll.head, i = 0; i < head; tmp = tmp->next, i++)
        if (tmp == NULL)
            return sll_new();

    sli = sll_new();
    for (; tmp != NULL && i < tail; tmp = tmp->next, i++)
        if (sll_push_back(&sli, tmp->data))
            return -1;

    return sli;
}

static int 
sll_push_front(sll *sll, const type val)
{
    if (sll->head == NULL) {
        sll->head = sll->tail = malloc(sizeof(struct sll_node));
        if (sll->head == NULL)
            return -1;

        sll->head->data = val;
        sll->head->next = NULL;
    } else {
        sll->head->next = sll->head;
        sll->head = malloc(sizeof(struct sll_node));
        if (sll->head == NULL)
            return -1;

        sll->head->data = val;
    }

    sll->len++;

    return 0;
}

static int 
sll_pop_back(sll *sll, type *val);

static int 
sll_pop_front(sll *sll, type *val);

static int 
sll_insert(sll *sll, const type val);

static size_t 
sll_search(const sll *sll, const type val);

static size_t 
sll_remove(sll *sll, const type val);

static int 
sll_getnth(const sll *sll, type *val, const size_t at);

static int 
sll_setnth(sll *sll, const type val, const size_t at);

static int 
sll_rmvnth(sll *sll, type *val, const size_t at);

static type *
sll_nth(sll *sll, const size_t at);

static type *
sll_front(sll *sll, const size_t at);

static type *
sll_back(sll *sll, const size_t at);

static size_t 
sll_length(const sll *sll)
{
    return sll->len;
}

#define INIT_DLL(name, type)

typedef struct {
    struct dll_node *head, *tail;
    size_t len;
} dll;

struct dll_node {
    type data;
    struct dll_node *next, *prev;
};

static dll 
dll_new()
{
    dll ll = { NULL, NULL, 0 };
    return ll;
}

static dll 
dll_slice(const dll *dll, const size_t head, const size_t tail);

static void 
dll_free(dll *dll);

static int 
dll_push_back(dll *dll, const type val);

static int 
dll_push_front(dll *dll, const type val);

static int 
dll_pop_back(dll *dll, type *val);

static int 
dll_pop_front(dll *dll, type *val);

static int 
dll_insert(dll *dll, const type val);

static size_t 
dll_search(const dll *dll, const type val);

static size_t 
dll_remove(dll *dll, const type val);

static int 
dll_getnth(const dll *dll, type *val, const size_t at);

static int 
dll_setnth(dll *dll, const type val, const size_t at);

static int 
dll_rmvnth(dll *dll, type *val, const size_t at);

static type *
dll_nth(dll *dll, const size_t at);

static type *
dll_front(dll *dll, const size_t at);

static type *
dll_back(dll *dll, const size_t at);

static size_t 
dll_length(const dll *dll)
{
    return dll->len;
}

#endif
