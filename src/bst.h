#ifndef _BST_H
#define _BST_H

#include <stddef.h>

#define MAX_DEPTH (sizeof(size_t) * 8)

#define INIT_BST_TYPE(name, type)                                              \
struct bst_##name##_node {                                                     \
        type val;                                                              \
        struct bst_##name##_node *kid[2];                                      \
};                                                                             \
                                                                               \
struct bst_##name {                                                            \
        struct bst_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct bst_##name##_iter {                                                     \
        struct bst_##name##_node *cur, *arr[MAX_DEPTH];                        \
        size_t top;                                                            \
};                                                                             \
                                                                               \
struct bst_##name bst_##name##_new(void);                                      \
struct bst_##name bst_##name##_from(const type *, const size_t);               \
struct bst_##name bst_##name##_copy(const struct bst_##name *);                \
int bst_##name##_root(struct bst_##name *, type *);                            \
int bst_##name##_max(struct bst_##name *, type *);                             \
int bst_##name##_min(struct bst_##name *, type *);                             \
int bst_##name##_get(struct bst_##name *, type *);                             \
int bst_##name##_set(struct bst_##name *, const type);                         \
int bst_##name##_insert(struct bst_##name *, const type);                      \
int bst_##name##_remove(struct bst_##name *, type *);                          \
size_t bst_##name##_length(struct bst_##name *);                               \
size_t bst_##name##_sizeof(struct bst_##name *);                               \
void bst_##name##_free(struct bst_##name *);                                   \
                                                                               \
struct bst_##name##_iter bst_##name##_iter(struct bst_##name *);               \
int bst_##name##_next(struct bst_##name##_iter *, type *);

#define INIT_BST_FUNC(name, type, cmp, malloc, free)                           \
static void                                                                    \
bst_##name##_copy_node(struct bst_##name *cpy, struct bst_##name##_node *node) \
{                                                                              \
        bst_##name##_insert(cpy, node->val);                                   \
                                                                               \
        if (node->kid[0] != NULL)                                              \
                bst_##name##_copy_node(cpy, node->kid[0]);                     \
        if (node->kid[1] != NULL)                                              \
                bst_##name##_copy_node(cpy, node->kid[1]);                     \
}                                                                              \
                                                                               \
static struct bst_##name##_node *                                              \
bst_##name##_node(const type val)                                              \
{                                                                              \
        struct bst_##name##_node *new;                                         \
                                                                               \
        if ((new = malloc(sizeof(struct bst_##name##_node))) == NULL)          \
                return NULL;                                                   \
                                                                               \
        new->val = val;                                                        \
        new->kid[0] = NULL;                                                    \
        new->kid[1] = NULL;                                                    \
                                                                               \
        return new;                                                            \
}                                                                              \
                                                                               \
static struct bst_##name##_node *                                              \
bst_##name##_match(struct bst_##name *bst, const type val)                     \
{                                                                              \
        struct bst_##name##_node *cur;                                         \
        int res;                                                               \
                                                                               \
        for (cur = bst->root; cur != NULL; cur = cur->kid[res > 0])            \
                if ((res = cmp(val, cur->val)) == 0)                           \
                        return cur;                                            \
                                                                               \
        return NULL;                                                           \
}                                                                              \
                                                                               \
static void                                                                    \
bst_##name##_remove_leaf(struct bst_##name *bst,                               \
                         struct bst_##name##_node *par,                        \
                         struct bst_##name##_node *del)                        \
{                                                                              \
        if (bst->root == del)                                                  \
                bst->root = NULL;                                              \
        else if (par->kid[0] == del)                                           \
                par->kid[0] = NULL;                                            \
        else                                                                   \
                par->kid[1] = NULL;                                            \
                                                                               \
        free(del);                                                             \
}                                                                              \
                                                                               \
static void                                                                    \
bst_##name##_remove_only(struct bst_##name##_node *del)                        \
{                                                                              \
        if (del->kid[0] != NULL) {                                             \
                del->val = del->kid[0]->val;                                   \
                free(del->kid[0]);                                             \
                del->kid[0] = NULL;                                            \
        } else {                                                               \
                del->val = del->kid[1]->val;                                   \
                free(del->kid[1]);                                             \
                del->kid[1] = NULL;                                            \
        }                                                                      \
}                                                                              \
                                                                               \
static void                                                                    \
bst_##name##_remove_full(struct bst_##name##_node *del)                        \
{                                                                              \
        struct bst_##name##_node *suc, *par;                                   \
                                                                               \
        par = del;                                                             \
        for (suc = del->kid[1]; suc->kid[0] != NULL; suc = suc->kid[0])        \
                par = suc;                                                     \
                                                                               \
        del->val = suc->val;                                                   \
        free(suc);                                                             \
        par->kid[par == del] = NULL;                                           \
}                                                                              \
                                                                               \
static void                                                                    \
bst_##name##_free_node(struct bst_##name##_node *node)                         \
{                                                                              \
        if (node->kid[0] != NULL)                                              \
                bst_##name##_free_node(node->kid[0]);                          \
        if (node->kid[1] != NULL)                                              \
                bst_##name##_free_node(node->kid[1]);                          \
                                                                               \
        free(node);                                                            \
}                                                                              \
                                                                               \
struct bst_##name                                                              \
bst_##name##_new(void)                                                         \
{                                                                              \
        struct bst_##name bst;                                                 \
                                                                               \
        bst.root = NULL;                                                       \
        bst.len = 0;                                                           \
                                                                               \
        return bst;                                                            \
}                                                                              \
                                                                               \
struct bst_##name                                                              \
bst_##name##_copy(const struct bst_##name *bst)                                \
{                                                                              \
        struct bst_##name cpy;                                                 \
                                                                               \
        cpy = bst_##name##_new();                                              \
        bst_##name##_copy_node(&cpy, bst->root);                               \
                                                                               \
        return cpy;                                                            \
}                                                                              \
                                                                               \
struct bst_##name                                                              \
bst_##name##_from(const type *arr, const size_t len)                           \
{                                                                              \
        struct bst_##name bst;                                                 \
        size_t i;                                                              \
                                                                               \
        bst = bst_##name##_new();                                              \
                                                                               \
        for (i = 0; i < len; i++)                                              \
                if (bst_##name##_insert(&bst, arr[i]))                         \
                        break;                                                 \
                                                                               \
        return bst;                                                            \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_root(struct bst_##name *bst, type *val)                           \
{                                                                              \
        if (bst->root == NULL || bst->len == 0)                                \
                return -1;                                                     \
                                                                               \
        *val = bst->root->val;                                                 \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_max(struct bst_##name *bst, type *val)                            \
{                                                                              \
        struct bst_##name##_node *max;                                         \
                                                                               \
        if (bst->root == NULL || bst->len == 0)                                \
                return -1;                                                     \
        for (max = bst->root; max->kid[1] != NULL; max = max->kid[1])          \
                ;                                                              \
                                                                               \
        *val = max->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_min(struct bst_##name *bst, type *val)                            \
{                                                                              \
        struct bst_##name##_node *min;                                         \
                                                                               \
        if (bst->root == NULL || bst->len == 0)                                \
                return -1;                                                     \
        for (min = bst->root; min->kid[0] != NULL; min = min->kid[0])          \
                ;                                                              \
                                                                               \
        *val = min->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_get(struct bst_##name *bst, type *val)                            \
{                                                                              \
        struct bst_##name##_node *cur;                                         \
                                                                               \
        if ((cur = bst_##name##_match(bst, *val)) == NULL)                     \
                return -1;                                                     \
                                                                               \
        *val = cur->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_set(struct bst_##name *bst, const type val)                       \
{                                                                              \
        struct bst_##name##_node *cur;                                         \
                                                                               \
        if ((cur = bst_##name##_match(bst, val)) == NULL)                      \
                return -1;                                                     \
                                                                               \
        cur->val = val;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_insert(struct bst_##name *bst, const type val)                    \
{                                                                              \
        struct bst_##name##_node **cur, *new;                                  \
        int dir;                                                               \
                                                                               \
        if ((new = bst_##name##_node(val)) == NULL)                            \
                return -1;                                                     \
        if (bst->root == NULL || bst->len == 0) {                              \
                bst->root = new;                                               \
        } else {                                                               \
                for (cur = &bst->root; *cur != NULL; cur = &(*cur)->kid[dir])  \
                        dir = cmp(val, (*cur)->val) > 0;                       \
                                                                               \
                *cur = new;                                                    \
        }                                                                      \
                                                                               \
        bst->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_remove(struct bst_##name *bst, type *val)                         \
{                                                                              \
        struct bst_##name##_node *par, *del;                                   \
        int res;                                                               \
                                                                               \
        if (bst->root == NULL || bst->len == 0)                                \
                return -1;                                                     \
        for (del = bst->root; del != NULL; par = del, del = del->kid[res > 0]) \
                if ((res = cmp(*val, del->val)) == 0)                          \
                        break;                                                 \
        if (del->kid[0] != NULL && del->kid[1] != NULL)                        \
                bst_##name##_remove_full(del);                                 \
        else if (del->kid[0] == NULL && del->kid[1] == NULL)                   \
                bst_##name##_remove_leaf(bst, par, del);                       \
        else                                                                   \
                bst_##name##_remove_only(del);                                 \
                                                                               \
        bst->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
bst_##name##_length(struct bst_##name *bst)                                    \
{                                                                              \
        return bst->len;                                                       \
}                                                                              \
                                                                               \
size_t                                                                         \
bst_##name##_sizeof(struct bst_##name *bst)                                    \
{                                                                              \
        return bst->len * sizeof(struct bst_##name##_node) + sizeof(*bst);     \
}                                                                              \
                                                                               \
void                                                                           \
bst_##name##_free(struct bst_##name *bst)                                      \
{                                                                              \
        bst_##name##_free_node(bst->root);                                     \
        bst->root = NULL;                                                      \
        bst->len = 0;                                                          \
}                                                                              \
                                                                               \
struct bst_##name##_iter                                                       \
bst_##name##_iter(struct bst_##name *bst)                                      \
{                                                                              \
        struct bst_##name##_iter iter;                                         \
                                                                               \
        iter.cur = bst->root;                                                  \
        iter.top = 0;                                                          \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
bst_##name##_next(struct bst_##name##_iter *iter, type *val)                   \
{                                                                              \
        while (iter->cur != NULL) {                                            \
                iter->arr[iter->top++] = iter->cur;                            \
                iter->cur = iter->cur->kid[0];                                 \
        }                                                                      \
                                                                               \
        if (iter->top == 0)                                                    \
                return -1;                                                     \
                                                                               \
        iter->cur = iter->arr[--iter->top];                                    \
        *val = iter->cur->val;                                                 \
        iter->cur = iter->cur->kid[1];                                         \
                                                                               \
        return 0;                                                              \
}

#define FOR_EACH_BST(name, elem, iter) while (!bst_##name##_next(&iter, &elem))

#define INIT_BST_BOTH(name, type, cmp, malloc, free)                           \
INIT_BST_TYPE(name, type)                                                      \
INIT_BST_FUNC(name, type, cmp, malloc, free)

#endif
