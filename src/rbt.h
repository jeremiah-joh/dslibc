#include <stddef.h>
#include <stdio.h>

#define IS_DIR(n, d) ((n) == (n)->par->kid[(d)])
#define SIBLING(n) ((n)->par->kid[IS_DIR(n, 0)])
#define UNCLE(n) (SIBLING((n)->par))

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
extern int _rbt_type_##name

#define INIT_RBT_FUNC(name, type, cmp, malloc, free)                           \
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
		cur->par->kid[IS_DIR(cur, 1)] = kid;                           \
	else                                                                   \
		rbt->root = kid;                                               \
	if (kid)                                                               \
		kid->par = cur->par;                                           \
	if (kid->kid[dir])                                                     \
		kid->kid[dir]->par = cur;                                      \
                                                                               \
	kid->kid[dir] = cur;                                                   \
	cur->par = kid;                                                        \
}                                                                              \
                                                                               \
static void                                                                    \
rbt_##name##_post_insert(struct rbt_##name *rbt, struct rbt_##name##_node *cur)\
{                                                                              \
	int dir;                                                               \
                                                                               \
	for (;;) {                                                             \
		if (cur->par == NULL || cur->par->col == BLACK) {              \
			return;                                                \
		} else if (UNCLE(cur) && UNCLE(cur)->col == RED) {             \
			cur->par->col = UNCLE(cur)->col = BLACK;               \
			cur->par->par->col = RED;                              \
			continue;                                              \
		} else if (IS_DIR(cur, 0) != IS_DIR(cur->par, 0)) {            \
			dir = IS_DIR(cur, 0) && IS_DIR(cur->par, 1);           \
			rbt_##name##_rotate(rbt, cur->par, dir);               \
			cur = cur->kid[dir];                                   \
		}                                                              \
		cur->par->col = BLACK;                                         \
		cur->par->par->col = RED;                                      \
		dir = IS_DIR(cur, 0) && IS_DIR(cur->par, 0);                   \
		rbt_##name##_rotate(rbt, cur->par->par, dir);                  \
		return;                                                        \
	}                                                                      \
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
extern int _rbt_func_##name

#define INIT_RBT_BOTH(name, type, cmp, malloc, free)                           \
INIT_RBT_TYPE(name, type);                                                     \
INIT_RBT_FUNC(name, type, cmp, malloc, free)
