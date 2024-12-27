/*
 * dslibc - data structure library for ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyrigrbt
 * and related and neighboring rigrbts to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <rbttp://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _RBT_H
#define _RBT_H

#include <stddef.h>
#include <stdio.h>

#define DIR(n) ((n) == (n)->par->kid[1]) /* panic if n is root */
#define COLOR(n) ((n) ? (n)->col : BLACK)
#define SIBLING(n) ((n)->par->kid[!DIR(n)])
#define UNCLE(n) SIBLING((n)->par)

#define INIT_RBT_TYPE(name, type)                                              \
enum rbt_##name##_color { RED, BLACK };                                        \
                                                                               \
struct rbt_##name##_node {                                                     \
        type val;                                                              \
        struct rbt_##name##_node *par, *kid[2];                                \
        enum rbt_##name##_color col;                                           \
};                                                                             \
                                                                               \
struct rbt_##name {                                                            \
        struct rbt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct rbt_##name##_iter {                                                     \
        struct rbt_##name##_node *cur;                                         \
};                                                                             \
                                                                               \
struct rbt_##name rbt_##name##_new(void);                                      \
struct rbt_##name rbt_##name##_from(const type *, const size_t);               \
struct rbt_##name rbt_##name##_copy(const struct rbt_##name *);                \
int rbt_##name##_root(struct rbt_##name *, type *);                            \
int rbt_##name##_max(struct rbt_##name *, type *);                             \
int rbt_##name##_min(struct rbt_##name *, type *);                             \
int rbt_##name##_get(struct rbt_##name *, type *);                             \
int rbt_##name##_set(struct rbt_##name *, const type);                         \
int rbt_##name##_insert(struct rbt_##name *, const type);                      \
int rbt_##name##_remove(struct rbt_##name *, type *);                          \
size_t rbt_##name##_len(struct rbt_##name *);                                  \
void rbt_##name##_free(struct rbt_##name *);                                   \
                                                                               \
struct rbt_##name##_iter rbt_##name##_iter(struct rbt_##name *);               \
int rbt_##name##_next(struct rbt_##name##_iter *, type *);                     \
                                                                               \
extern int _rbt_##name##_type

#define INIT_RBT_FUNC(name, type, cmp, malloc, free)                           \
static void                                                                    \
rbt_##name##_rotate(struct rbt_##name *rbt,                                    \
                    struct rbt_##name##_node *par,                             \
                    int dir)                                                   \
{                                                                              \
        struct rbt_##name##_node *kid;                                         \
                                                                               \
        kid = par->kid[!dir];                                                  \
        par->kid[!dir] = kid->kid[dir];                                        \
                                                                               \
        if (kid->kid[dir])                                                     \
                kid->kid[dir]->par = par;                                      \
                                                                               \
        kid->par = par->par;                                                   \
        if (par->par)                                                          \
                par->par->kid[DIR(par)] = kid;                                 \
        else                                                                   \
                rbt->root = kid;                                               \
                                                                               \
        kid->kid[dir] = par;                                                   \
        par->par = kid;                                                        \
}                                                                              \
                                                                               \
static struct rbt_##name##_node *                                              \
rbt_##name##_node(const type val,                                              \
                  struct rbt_##name##_node *par,                               \
                  enum rbt_##name##_color col)                                 \
{                                                                              \
        struct rbt_##name##_node *new;                                         \
                                                                               \
        if ((new = malloc(sizeof(struct rbt_##name##_node))) == NULL)          \
                return NULL;                                                   \
                                                                               \
        new->val = val;                                                        \
        new->par = par;                                                        \
        new->kid[0] = new->kid[1] = NULL;                                      \
        new->col = col;                                                        \
                                                                               \
        return new;                                                            \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_fix_insert(struct rbt_##name *rbt, struct rbt_##name##_node *cur) \
{                                                                              \
        while (COLOR(cur->par) == RED) {                                       \
                if (COLOR(UNCLE(cur)) == RED) {                                \
                        cur->par->col = BLACK;                                 \
                        UNCLE(cur)->col = BLACK;                               \
                        cur->par->par->col = RED;                              \
                        cur = cur->par->par;                                   \
                        continue;                                              \
                } else if (DIR(cur->par) != DIR(cur)) {                        \
                        cur = cur->par;                                        \
                        rbt_##name##_rotate(rbt, cur, DIR(cur));               \
                }                                                              \
                                                                               \
                cur->par->col = BLACK;                                         \
                cur->par->par->col = RED;                                      \
                rbt_##name##_rotate(rbt, cur->par->par, !DIR(cur));            \
        }                                                                      \
                                                                               \
        rbt->root->col = BLACK;                                                \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_fix_remove(struct rbt_##name *rbt, struct rbt_##name##_node *cur) \
{                                                                              \
        struct rbt_##name##_node *sib;                                         \
        int dir;                                                               \
                                                                               \
        while (cur && cur != rbt->root && COLOR(cur) == BLACK) {               \
                dir = DIR(cur);                                                \
                sib = SIBLING(cur);                                            \
                if (COLOR(sib) == RED) {                                       \
                        sib->col = BLACK;                                      \
                        cur->par->col = RED;                                   \
                        rbt_##name##_rotate(rbt, cur->par, dir);               \
                        sib = SIBLING(cur);                                    \
                }                                                              \
                if (COLOR(sib->kid[0]) == BLACK                                \
                    && COLOR(sib->kid[1]) == BLACK) {                          \
                        sib->col = RED;                                        \
                        cur = cur->par;                                        \
                        continue;                                              \
                } else if (COLOR(sib->kid[!dir]) == BLACK) {                   \
                        sib->kid[dir]->col = BLACK;                            \
                        sib->col = RED;                                        \
                        rbt_##name##_rotate(rbt, sib, !dir);                   \
                        sib = SIBLING(cur);                                    \
                }                                                              \
                                                                               \
                sib->col = COLOR(cur->par);                                    \
                cur->par->col = BLACK;                                         \
                sib->kid[!dir]->col = BLACK;                                   \
                rbt_##name##_rotate(rbt, cur->par, dir);                       \
                cur = rbt->root;                                               \
        }                                                                      \
                                                                               \
        if (cur)                                                               \
                cur->col = BLACK;                                              \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_trasplant(struct rbt_##name *rbt,                                 \
                       struct rbt_##name##_node *old,                          \
                       struct rbt_##name##_node *new)                          \
{                                                                              \
        if (old->par)                                                          \
                old->par->kid[DIR(old)] = new;                                 \
        else                                                                   \
                rbt->root = new;                                               \
        if (new)                                                               \
                new->par = old->par;                                           \
}                                                                              \
                                                                               \
static struct rbt_##name##_node *                                              \
rbt_##name##_edge(struct rbt_##name##_node *tmp, int dir)                      \
{                                                                              \
        if (tmp == NULL)                                                       \
                return NULL;                                                   \
        while (tmp->kid[dir])                                                  \
                tmp = tmp->kid[dir];                                           \
                                                                               \
        return tmp;                                                            \
}                                                                              \
                                                                               \
static struct rbt_##name##_node *                                              \
rbt_##name##_match(struct rbt_##name *rbt, const type val)                     \
{                                                                              \
        struct rbt_##name##_node *tmp;                                         \
        int dir;                                                               \
                                                                               \
        for (tmp = rbt->root; tmp; tmp = tmp->kid[dir > 0])                    \
                if ((dir = cmp(val, tmp->val)) == 0)                           \
                        return tmp;                                            \
                                                                               \
        return tmp;                                                            \
}                                                                              \
                                                                               \
struct rbt_##name                                                              \
rbt_##name##_new(void)                                                         \
{                                                                              \
        struct rbt_##name rbt;                                                 \
                                                                               \
        rbt.root = NULL;                                                       \
        rbt.len = 0;                                                           \
                                                                               \
        return rbt;                                                            \
}                                                                              \
                                                                               \
struct rbt_##name                                                              \
rbt_##name##_from(const type *arr, const size_t len)                           \
{                                                                              \
        struct rbt_##name rbt;                                                 \
        size_t i;                                                              \
                                                                               \
        rbt = rbt_##name##_new();                                              \
                                                                               \
        for (i = 0; i < len; i++)                                              \
                if (rbt_##name##_insert(&rbt, arr[i]))                         \
                        break;                                                 \
                                                                               \
        return rbt;                                                            \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_root(struct rbt_##name *rbt, type *val)                           \
{                                                                              \
        if (rbt->root == NULL)                                                 \
                return -1;                                                     \
                                                                               \
        *val = rbt->root->val;                                                 \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_max(struct rbt_##name *rbt, type *val)                            \
{                                                                              \
        struct rbt_##name##_node *max;                                         \
                                                                               \
        if ((max = rbt_##name##_edge(rbt->root, 1)) == NULL)                   \
                return -1;                                                     \
                                                                               \
        *val = max->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_min(struct rbt_##name *rbt, type *val)                            \
{                                                                              \
        struct rbt_##name##_node *min;                                         \
                                                                               \
        if ((min = rbt_##name##_edge(rbt->root, 0)) == NULL)                   \
                return -1;                                                     \
                                                                               \
        *val = min->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_get(struct rbt_##name *rbt, type *val)                            \
{                                                                              \
        struct rbt_##name##_node *tmp;                                         \
                                                                               \
        if ((tmp = rbt_##name##_match(rbt, *val)) == NULL)                     \
                return -1;                                                     \
                                                                               \
        *val = tmp->val;                                                       \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_set(struct rbt_##name *rbt, const type val)                       \
{                                                                              \
        struct rbt_##name##_node *tmp;                                         \
                                                                               \
        if ((tmp = rbt_##name##_match(rbt, val)) == NULL)                      \
                return -1;                                                     \
                                                                               \
        tmp->val = val;                                                        \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_insert(struct rbt_##name *rbt, const type val)                    \
{                                                                              \
        struct rbt_##name##_node *new, *tmp, *par;                             \
        int dir;                                                               \
                                                                               \
        for (par = NULL, tmp = rbt->root; tmp; par = tmp, tmp = tmp->kid[dir]) \
                dir = cmp(val, tmp->val) > 0;                                  \
        if ((new = rbt_##name##_node(val, par, RED)) == NULL)                  \
                return -1;                                                     \
        if (par)                                                               \
                par->kid[dir] = new;                                           \
        else                                                                   \
                rbt->root = new;                                               \
                                                                               \
        rbt_##name##_fix_insert(rbt, new);                                     \
        rbt->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_remove(struct rbt_##name *rbt, type *val)                         \
{                                                                              \
        struct rbt_##name##_node *del, *tmp, *kid;                             \
        enum rbt_##name##_color col;                                           \
                                                                               \
        if ((tmp = del = rbt_##name##_match(rbt, *val)) == NULL)               \
                return -1;                                                     \
                                                                               \
        col = COLOR(tmp);                                                      \
        if (del->kid[0] == NULL || del->kid[1] == NULL) {                      \
                kid = del->kid[del->kid[0] == NULL];                           \
                rbt_##name##_trasplant(rbt, del, kid);                         \
        } else {                                                               \
                tmp = rbt_##name##_edge(del->kid[1], 0);                       \
                col = COLOR(tmp);                                              \
                kid = tmp->kid[1];                                             \
                if (tmp->par == del) {                                         \
                        if (kid)                                               \
                                kid->par = tmp;                                \
                } else {                                                       \
                        rbt_##name##_trasplant(rbt, tmp, tmp->kid[1]);         \
                        tmp->kid[1] = del->kid[1];                             \
                        tmp->kid[1]->par = tmp;                                \
                }                                                              \
                                                                               \
                rbt_##name##_trasplant(rbt, del, tmp);                         \
                tmp->kid[0] = del->kid[0];                                     \
                tmp->kid[0]->par = tmp;                                        \
                tmp->col = COLOR(del);                                         \
        }                                                                      \
        if (col == BLACK)                                                      \
                rbt_##name##_fix_remove(rbt, kid);                             \
                                                                               \
        free(del);                                                             \
        rbt->len--;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
size_t                                                                         \
rbt_##name##_len(struct rbt_##name *rbt)                                       \
{                                                                              \
        return rbt->len;                                                       \
}                                                                              \
                                                                               \
void                                                                           \
rbt_##name##_free(struct rbt_##name *rbt)                                      \
{                                                                              \
        struct rbt_##name##_node *del, *cur;                                   \
                                                                               \
        for (cur = rbt->root; cur->par; ) {                                    \
                if (cur->kid[0]) {                                             \
                        cur = cur->kid[0];                                     \
                } else if (cur->kid[1]) {                                      \
                        cur = cur->kid[1];                                     \
                } else {                                                       \
                        del = cur;                                             \
                        cur = cur->par;                                        \
                        free(del);                                             \
                }                                                              \
        }                                                                      \
                                                                               \
        rbt->root = NULL;                                                      \
        rbt->len = 0;                                                          \
}                                                                              \
                                                                               \
struct rbt_##name##_iter                                                       \
rbt_##name##_iter(struct rbt_##name *rbt)                                      \
{                                                                              \
        struct rbt_##name##_iter iter;                                         \
                                                                               \
        iter.cur = rbt_##name##_edge(rbt->root, 0);                            \
                                                                               \
        return iter;                                                           \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_next(struct rbt_##name##_iter *iter, type *val)                   \
{                                                                              \
        if (iter->cur == NULL)                                                 \
                return -1;                                                     \
                                                                               \
        *val = iter->cur->val;                                                 \
                                                                               \
        if (iter->cur->kid[1]) {                                               \
                iter->cur = rbt_##name##_edge(iter->cur->kid[1], 0);           \
        } else {                                                               \
                while (iter->cur->par && DIR(iter->cur))                       \
                        iter->cur = iter->cur->par;                            \
                iter->cur = iter->cur->par;                                    \
        }                                                                      \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
extern int _rbt_##name##_func

#define INIT_RBT_BOTH(name, type, cmp, malloc, free)                           \
INIT_RBT_TYPE(name, type);                                                     \
INIT_RBT_FUNC(name, type, cmp, malloc, free)

#endif
