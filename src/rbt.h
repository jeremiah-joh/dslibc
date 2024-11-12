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
 * If not, see <http://creatidllommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _RBT_H
#define _RBT_H

#include <stddef.h>

#define DIR(n) ((n) == (n)->par->kid[1])
#define SIBLING(n) ((n)->par->kid[!DIR(n)])
#define UNCLE(n) (SIBLING((n)->par))
#define COLOR(n) ((n) ? (n)->col : BLACK)

#define INIT_RBT_TYPE(name, type)                                              \
struct rbt_##name##_node {                                                     \
        type val;                                                              \
        struct rbt_##name##_node *par, *kid[2];                                \
        enum { RED, BLACK } col;                                               \
};                                                                             \
                                                                               \
struct rbt_##name {                                                            \
        struct rbt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct rbt_##name##_iter {                                                     \
        struct rbt_##name##_node *prv, *cur;                                   \
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
extern int _rbt_type_##name

#define INIT_RBT_FUNC(name, type, cmp, malloc, free)                           \
static struct rbt_##name##_node *                                              \
rbt_##name##_match(struct rbt_##name *rbt, const type val)                     \
{                                                                              \
        struct rbt_##name##_node *cur;                                         \
        int res;                                                               \
                                                                               \
        for (cur = rbt->root; cur; cur = cur->kid[res > 0])                    \
                if ((res = cmp(val, cur->val)) == 0)                           \
                        return cur;                                            \
                                                                               \
        return NULL;                                                           \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_rotate(struct rbt_##name *rbt,                                    \
                    struct rbt_##name##_node *cur,                             \
                    int dir)                                                   \
{                                                                              \
        struct rbt_##name##_node *kid;                                         \
                                                                               \
        kid = cur->kid[!dir];                                                  \
                                                                               \
        if (cur->par)                                                          \
                cur->par->kid[DIR(cur)] = kid;                                 \
        else                                                                   \
                rbt->root = kid;                                               \
        if (kid)                                                               \
                kid->par = cur->par;                                           \
        if (kid->kid[dir])                                                     \
                kid->kid[dir]->par = cur;                                      \
                                                                               \
        cur->kid[!dir] = kid->kid[dir];                                        \
        kid->kid[dir] = cur;                                                   \
        cur->par = kid;                                                        \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_post_insert(struct rbt_##name *rbt, struct rbt_##name##_node *cur)\
{                                                                              \
        int dir;                                                               \
                                                                               \
        while (cur->par && cur->par->par && COLOR(cur->par) == RED) {          \
                if (COLOR(UNCLE(cur)) == RED) {                                \
                        cur->par->col = UNCLE(cur)->col = BLACK;               \
                        cur->par->par->col = RED;                              \
                        cur = cur->par->par;                                   \
                        continue;                                              \
                } else if (DIR(cur) != DIR(cur->par)) {                        \
                        dir = !DIR(cur) && DIR(cur->par);                      \
                        rbt_##name##_rotate(rbt, cur->par, dir);               \
                        cur = cur->kid[dir];                                   \
                }                                                              \
                                                                               \
                cur->par->col = BLACK;                                         \
                cur->par->par->col = RED;                                      \
                dir = !DIR(cur) && !DIR(cur->par);                             \
                rbt_##name##_rotate(rbt, cur->par->par, dir);                  \
                break;                                                         \
        }                                                                      \
}                                                                              \
                                                                               \
static struct rbt_##name##_node *                                              \
rbt_##name##_remove_full(struct rbt_##name *rbt, struct rbt_##name##_node *del)\
{                                                                              \
	struct rbt_##name##_node *suc;                                         \
                                                                               \
	for (suc = del->kid[0]; suc->kid[1]; suc = suc->kid[1])                \
		;                                                              \
	if (del->par == NULL)                                                  \
		rbt->root->val = suc->val;                                     \
	else                                                                   \
		del->val = suc->val;                                           \
                                                                               \
	suc->par->kid[DIR(suc)] = NULL;                                        \
                                                                               \
	return suc;                                                            \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_remove_only(struct rbt_##name *rbt, struct rbt_##name##_node *del)\
{                                                                              \
	int dir;                                                               \
                                                                               \
	dir = del->kid[1] != NULL;                                             \
                                                                               \
	if (del->par == NULL) {                                                \
		rbt->root = del->kid[dir];                                     \
	} else {                                                               \
		del->par->kid[DIR(del)] = del->kid[dir];                       \
		del->kid[dir]->par = del->par;                                 \
	}                                                                      \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_remove_leaf(struct rbt_##name *rbt, struct rbt_##name##_node *del)\
{                                                                              \
	if (del->par == NULL)                                                  \
		rbt->root = NULL;                                              \
	else                                                                   \
		del->par->kid[DIR(del)] = NULL;                                \
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
        if (rbt->root == NULL)                                                 \
                return -1;                                                     \
        for (max = rbt->root; max->kid[1]; max = max->kid[1])                  \
                ;                                                              \
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
        if (rbt->root == NULL)                                                 \
                return -1;                                                     \
        for (min = rbt->root; min->kid[0]; min = min->kid[0])                  \
                ;                                                              \
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
        struct rbt_##name##_node **cur, *par;                                  \
        int dir;                                                               \
                                                                               \
        par = NULL;                                                            \
        for (cur = &rbt->root; *cur; par = *cur, cur = &(*cur)->kid[dir])      \
                dir = cmp(val, (*cur)->val) > 0;                               \
        if ((*cur = malloc(sizeof(struct rbt_##name##_node))) == NULL)         \
                return -1;                                                     \
                                                                               \
        (*cur)->val = val;                                                     \
        (*cur)->par = par;                                                     \
        (*cur)->kid[0] = (*cur)->kid[1] = NULL;                                \
        (*cur)->col = par ? RED : BLACK;                                       \
                                                                               \
        rbt_##name##_post_insert(rbt, *cur);                                   \
        rbt->len++;                                                            \
                                                                               \
        return 0;                                                              \
}                                                                              \
                                                                               \
int                                                                            \
rbt_##name##_remove(struct rbt_##name *rbt, type *val)                         \
{                                                                              \
	struct rbt_##name##_node *del;                                         \
                                                                               \
	if (((del = rbt_##name##_match(rbt, *val))) == NULL)                   \
		return -1;                                                     \
	if (del->kid[0] && del->kid[1])                                        \
		del = rbt_##name##_remove_full(rbt, del);                      \
	else if (del->kid[0] || del->kid[1])                                   \
		rbt_##name##_remove_only(rbt, del);                            \
	else                                                                   \
		rbt_##name##_remove_leaf(rbt, del);                            \
                                                                               \
      /*rbt_##name##_post_remove(rbt, del);*/                                  \
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
        struct rbt_##name##_node *del, *cur, *prv;                             \
                                                                               \
        for (cur = rbt->root, prv = NULL; cur; prv = cur) {                    \
                if (prv && prv->kid[1] != cur) {                               \
                        cur = cur->kid[1];                                     \
                } else {                                                       \
                        del = cur;                                             \
                        cur = (cur->kid[0]) ? cur->kid[0] : cur->par;          \
                        free(del);                                             \
                }                                                              \
        }                                                                      \
                                                                               \
        rbt->root = NULL;                                                      \
        rbt->len = 0;                                                          \
}                                                                              \
                                                                               \
extern int _rbt_func_##name

#define INIT_RBT_BOTH(name, type, cmp, malloc, free)                           \
INIT_RBT_TYPE(name, type);                                                     \
INIT_RBT_FUNC(name, type, cmp, malloc, free)

#endif
