#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INIT_HT_TYPE(name, key_t, val_t)                                      \
struct ht_##name {                                                            \
	struct ht_##name##_node *arr;                                         \
	size_t cap, len;                                                      \
	size_t (*hash)(key_t);                                                \
};                                                                            \
                                                                              \
struct ht_##name##_node {                                                     \
	key_t key;                                                            \
	val_t val;                                                            \
	enum state { NONE, SOME } state;                                      \
};                                                                            \
                                                                              \
struct ht_##name ht_##name##_new(size_t (*hash)(key_t));                      \
struct ht_##name ht_##name##_copy(const struct ht_##name);                    \
struct ht_##name ht_##name##_from(const key_t [], const val_t [],             \
                                  const size_t, size_t (*hash)(key_t));       \
int ht_##name##_insert(struct ht_##name *, const key_t, const val_t);         \
int ht_##name##_search(struct ht_##name *, const key_t, val_t *);             \
int ht_##name##_remove(struct ht_##name *, const key_t, val_t *);             \
val_t *ht_##name##_getptr(struct ht_##name *, const key_t);                   \
void ht_##name##_free(struct ht_##name *) /* to enforce semicolon */

#define INIT_HT_FUNC(name, key_t, val_t)                                      \
static size_t                                                                 \
ht_new_cap_##name(const size_t len)                                           \
{                                                                             \
	size_t i;                                                             \
	for (i = 4; i < len; i <<= 1)                                         \
		;                                                             \
	                                                                      \
	return i * sizeof(struct ht_##name##_node);                           \
}                                                                             \
                                                                              \
static int                                                                    \
ht_try_resize_##name(struct ht_##name *ht, const size_t len)                  \
{                                                                             \
	size_t i;                                                             \
	struct ht_##name new;                                                 \
	struct ht_##name##_node tmp;                                          \
                                                                              \
	if (ht->cap == ht_new_cap_##name(len))                                \
		return 0;                                                     \
                                                                              \
	new = ht_##name##_new(ht->hash);                                      \
	for (i = 0; i < ht->cap / sizeof(struct ht_##name##_node); i++) {     \
		if (ht->arr[i].state == NONE)                                 \
			continue;                                             \
		tmp = ht->arr[i];                                             \
		if (ht_##name##_insert(&new, tmp.key, tmp.val)) {             \
			free(new.arr);                                        \
			return -1;                                            \
		}                                                             \
	}                                                                     \
	*ht = new;                                                            \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_new(size_t (*hash)(key_t))                                        \
{                                                                             \
	struct ht_##name ht = { malloc(0), 0, 0, hash };                      \
	return ht;                                                            \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_copy(const struct ht_##name ht)                                   \
{                                                                             \
	struct ht_##name cp = { malloc(ht.cap), ht.cap, ht.len, ht.hash };    \
	memcpy(cp.arr, ht.arr, ht.cap);                                       \
                                                                              \
	return cp;                                                            \
}                                                                             \
                                                                              \
struct ht_##name                                                              \
ht_##name##_from(const key_t key[], const val_t val[],                        \
                 const size_t len, size_t (*hash)(key_t))                     \
{                                                                             \
	size_t cap = ht_new_cap_##name(len), i;                               \
	struct ht_##name ht = {                                               \
		calloc(1, cap),                                               \
		cap, len, hash                                                \
	};                                                                    \
                                                                              \
	for (i = 0; i < len; i++)                                             \
		ht_##name##_insert(&ht, key[i], val[i]);                      \
                                                                              \
	return ht;                                                            \
}                                                                             \
                                                                              \
int                                                                           \
ht_##name##_insert(struct ht_##name *ht, const key_t key, const val_t val)    \
{                                                                             \
	size_t i, j, k;                                                       \
                                                                              \
	if (ht->arr == NULL )                                                 \
		return -1;                                                    \
	if (ht_try_resize_##name(ht, ht->len + 1))                            \
		return -1;                                                    \
                                                                              \
	i = ht->hash(key);                                                    \
	for (j = 0; j < ht->cap; j++) {                                       \
		k = (i + j * j) % ht->cap;                                    \
		if (memcmp(&ht->arr[k].key, &key, sizeof(key_t)) == 0)        \
			return -1;                                            \
		if (ht->arr[k].state == NONE) {                               \
			ht->arr[k] = (struct ht_##name##_node){key,val,SOME}; \
			ht->len++;                                            \
			return 0;                                             \
		}                                                             \
	}                                                                     \
                                                                              \
	return -1; /* UNREACHABLE */                                          \
}

#define INIT_HT(name, key_t, val_t)                                           \
INIT_HT_TYPE(name, key_t, val_t);                                             \
INIT_HT_FUNC(name, key_t, val_t)
