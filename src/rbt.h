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

enum rbt_color { RED, BLACK };

#define INIT_RBT_TYPE(name, type)                                              \
struct rbt_##name##_node {                                                     \
        type val;                                                              \
        struct rbt_##name##_node *par, *kid[2];                                \
        enum rbt_color col;                                                    \
};                                                                             \
                                                                               \
struct rbt_##name {                                                            \
        struct rbt_##name##_node *root;                                        \
        size_t len;                                                            \
};                                                                             \
                                                                               \
struct rbt_##name##_iter {                                                     \
        struct rbt_##name##_node *cur, *prv;                                   \
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
/*                                                                             \
static void                                                                    \
rbt_##name##_replace(struct rbt_##name *rbt,                                   \
                     struct rbt_##name##_node *old,                            \
		     struct rbt_##name##_node *new)                            \
{                                                                              \
	if (old->par)                                                          \
		old->par->kid[DIR(old)] = new;                                 \
	else                                                                   \
		rbt->root = new;                                               \
	if (new)                                                               \
		new->par = old->par;                                           \
}                                                                              \
*/                                                                             \
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
rbt_##name##_node(const type val, struct rbt_##name##_node *par)               \
{                                                                              \
	struct rbt_##name##_node *new;                                         \
                                                                               \
	if ((new = malloc(sizeof(struct rbt_##name##_node))) == NULL)          \
		return NULL;                                                   \
                                                                               \
	new->val = val;                                                        \
	new->par = par;                                                        \
	new->kid[0] = new->kid[1] = NULL;                                      \
	new->col = RED;                                                        \
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
		} else {                                                       \
			if (DIR(cur->par) != DIR(cur)) {                       \
				cur = cur->par;                                \
				rbt_##name##_rotate(rbt, cur, DIR(cur));       \
			}                                                      \
                	                                                       \
			cur->par->col = BLACK;                                 \
			cur->par->par->col = RED;                              \
			rbt_##name##_rotate(rbt, cur->par->par, !DIR(cur));    \
		}                                                              \
	}                                                                      \
                                                                               \
	rbt->root->col = BLACK;                                                \
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
int                                                                            \
rbt_##name##_insert(struct rbt_##name *rbt, const type val)                    \
{                                                                              \
	struct rbt_##name##_node *new, *tmp, *par;                             \
	int dir;                                                               \
                                                                               \
	for (par = NULL, tmp = rbt->root; tmp; par = tmp, tmp = tmp->kid[dir]) \
		dir = cmp(val, tmp->val) > 0;                                  \
	if ((new = rbt_##name##_node(val, par)) == NULL)                       \
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
extern int _rbt_func_##name

#define INIT_RBT_BOTH(name, type, cmp, malloc, free)                           \
INIT_RBT_TYPE(name, type);                                                     \
INIT_RBT_FUNC(name, type, cmp, malloc, free)

#endif
