#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VEC_HEAD(name, type)                                             \
struct vec_##name {                                                           \
	type *arr;                                                            \
	size_t cap, len;                                                      \
} /* to enforce semicolone */

#define INIT_VEC_FUNC(name, type)                                             \
static size_t                                                                 \
new_cap_##name(const size_t len)                                              \
{                                                                             \
	size_t i;                                                             \
	for (i = 4; i < len; i += i / 2)                                      \
		;                                                             \
                                                                              \
	return i * sizeof(type);                                              \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_new()                                                            \
{                                                                             \
	struct vec_##name vec = { malloc(0), 0, 0 };                          \
	return vec;                                                           \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_from(const type *arr, const size_t len)                          \
{                                                                             \
	size_t cap = new_cap_##name(len);                                     \
	struct vec_##name vec = { malloc(cap), cap, len };                    \
                                                                              \
	memcpy(vec.arr, arr, sizeof(*arr) * len);                             \
                                                                              \
	return vec;                                                           \
}                                                                             \
                                                                              \
struct vec_##name                                                             \
vec_##name##_copy(const struct vec_##name vec)                                \
{                                                                             \
	struct vec_##name cpy = { malloc(vec.cap), vec.cap, vec.len };        \
	memcpy(cpy.arr, vec.arr, vec.cap);                                    \
                                                                              \
	return cpy;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(struct vec_##name *vec, const type val)                \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
                                                                              \
	vec->cap = new_cap_##name(vec->len + 1);                              \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	vec->arr[vec->len - 1] = val;                                         \
	vec->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_front(struct vec_##name *vec, const type val)               \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	                                                                      \
	vec->cap = new_cap_##name(vec->len + 1);                              \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	memmove(vec->arr + 1, vec->arr, sizeof(type) * vec->len);             \
	vec->arr[0] = val;                                                    \
	vec->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_back(struct vec_##name *vec, type *val)                      \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	                                                                      \
	*val = vec->arr[vec->len - 1];                                        \
	vec->cap = new_cap_##name(vec->len - 1);                              \
	vec->len--;                                                           \
                                                                              \
	return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_pop_front(struct vec_##name *vec, type *val)                     \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	                                                                      \
	*val = vec->arr[0];                                                   \
	vec->cap = new_cap_##name(vec->len - 1);                              \
	memmove(vec->arr, vec->arr + 1, sizeof(type) * vec->len);             \
	vec->len--;                                                           \
                                                                              \
	return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_append(struct vec_##name *des, struct vec_##name *src)           \
{                                                                             \
	if (des->arr == NULL && src->arr == NULL)                             \
		return -1;                                                    \
	if (src->arr == NULL)                                                 \
		return 0;                                                     \
	if (des->arr == NULL) {                                               \
		des = src;                                                    \
		return 0;                                                     \
	}                                                                     \
	                                                                      \
	des->cap = new_cap_##name(des->len += src->len);                      \
	if ((des->arr = realloc(des->arr, des->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	memcpy(des->arr + des->len, src->arr, sizeof(type) * src->len);       \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_insert(struct vec_##name *vec, const type val, const size_t idx) \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	if (vec->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	vec->cap = new_cap_##name(vec->len + 1);                              \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return -1;                                                    \
	                                                                      \
	memmove(vec->arr + idx,                                               \
	        vec->arr + idx + 1,                                           \
		sizeof(type) * (vec->len - idx));                             \
	vec->arr[idx] = val;                                                  \
                                                                              \
	vec->len++;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_search(struct vec_##name *vec, const type val)                   \
{                                                                             \
	size_t i;                                                             \
                                                                              \
	for (i = 0; i < vec->len; i++)                                        \
		if (vec->arr[i] == val)                                       \
			break;                                                \
                                                                              \
	return i;                                                             \
}                                                                             \
                                                                              \
size_t                                                                        \
vec_##name##_remove(struct vec_##name *vec, const type val)                   \
{                                                                             \
	size_t idx;                                                           \
                                                                              \
	if (vec->arr == NULL)                                                 \
		return vec->len;                                              \
	if ((idx = vec_##name##_search(vec, val)) == vec->len)                \
		return vec->len;                                              \
	                                                                      \
	memmove(vec->arr + idx,                                               \
	        vec->arr + idx + 1,                                           \
	        sizeof(type) * (vec->len - idx));                             \
	                                                                      \
	vec->cap = new_cap_##name(vec->len - 1);                              \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return vec->len;                                              \
                                                                              \
	vec->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(const struct vec_##name *vec, type *val, const size_t idx)\
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	if (vec->len <= idx)                                                  \
		return -1;                                                    \
                                                                              \
	*val = vec->arr[idx];                                                 \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_setnth(struct vec_##name *vec, const type val, const size_t idx) \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	if (vec->len <= idx)                                                  \
		return -1;                                                    \
                                                                              \
	vec->arr[idx] = val;                                                  \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_rmvnth(struct vec_##name *vec, type *val, const size_t idx)      \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	if (vec->len <= idx)                                                  \
		return -1;                                                    \
	                                                                      \
	*val = vec->arr[idx];                                                 \
	memmove(vec->arr + idx,                                               \
	        vec->arr + idx + 1,                                           \
		sizeof(type) * (vec->len - idx));                             \
	                                                                      \
	vec->cap = new_cap_##name(vec->len - 1);                              \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	vec->len--;                                                           \
                                                                              \
	return 0;                                                             \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_getptr(struct vec_##name *vec, const size_t idx)                 \
{                                                                             \
	return (idx < vec->len) ? &vec->arr[idx] : NULL;                      \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_head(struct vec_##name *vec)                                     \
{                                                                             \
	return (vec->arr) ? &vec->arr[0] : NULL;                              \
}                                                                             \
                                                                              \
type *                                                                        \
vec_##name##_tail(struct vec_##name *vec)                                     \
{                                                                             \
	return (vec->arr) ? &vec->arr[vec->len - 1] : NULL;                   \
}                                                                             \
                                                                              \
struct vec_##name##_semi { /* to enforce semicolone */ }

#define INIT_VEC(name, type)                                                  \
INIT_VEC_HEAD(name, type);                                                    \
INIT_VEC_FUNC(name, type)

#endif
