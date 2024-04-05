/* See COPYING file for copyright and license details. */

#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VEC_TYPE(name, type)                                             \
struct vec_##name {                                                           \
	type *arr;                                                            \
	size_t cap, len;                                                      \
};                                                                            \
                                                                              \
struct vec_##name vec_##name##_new();                                         \
struct vec_##name vec_##name##_from(const type *, const size_t);              \
struct vec_##name vec_##name##_copy(const struct vec_##name);                 \
struct vec_##name vec_##name##_slice(const struct vec_##name,                 \
			             const size_t, const size_t);             \
int vec_##name##_push_back(struct vec_##name *, const type);                  \
int vec_##name##_push_front(struct vec_##name *, const type);                 \
int vec_##name##_pop_back(struct vec_##name *, type *);                       \
int vec_##name##_pop_front(struct vec_##name *, type *);                      \
int vec_##name##_append(struct vec_##name *, const struct vec_##name);        \
int vec_##name##_insert(struct vec_##name *, const type, const size_t);       \
size_t vec_##name##_search(struct vec_##name *, const type);                  \
size_t vec_##name##_remove(struct vec_##name *, const type);                  \
int vec_##name##_shrink(struct vec_##name *, const size_t);                   \
int vec_##name##_getnth(struct vec_##name *, type *, const size_t);           \
int vec_##name##_setnth(struct vec_##name *, const type, const size_t);       \
int vec_##name##_rmvnth(struct vec_##name *, type *, const size_t);           \
type *vec_##name##_getptr(struct vec_##name *, const size_t);                 \
type *vec_##name##_head(struct vec_##name *);                                 \
type *vec_##name##_tail(struct vec_##name *);                                 \
void vec_##name##_free(struct vec_##name *) /* to enforce semicolon */

#define INIT_VEC_FUNC(name, type)                                             \
static size_t                                                                 \
vec_new_cap_##name(const size_t len)                                          \
{                                                                             \
	size_t i;                                                             \
	for (i = 4; i < len; i <<= 1)                                         \
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
	size_t cap = vec_new_cap_##name(len);                                 \
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
struct vec_##name                                                             \
vec_##name##_slice(const struct vec_##name vec,                               \
                   const size_t head, const size_t tail)                      \
{                                                                             \
        struct vec_##name sli;                                                \
                                                                              \
	if (tail - 1 <= head)                                                 \
		return vec_##name##_new();                                    \
                                                                              \
	sli.cap = vec_new_cap_##name(tail - head);                            \
	sli.arr = malloc(sli.cap);                                            \
	sli.len = tail - head;                                                \
                                                                              \
	memcpy(sli.arr, vec.arr + head, sizeof(type) * sli.len);              \
                                                                              \
	return sli;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_push_back(struct vec_##name *vec, const type val)                \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
                                                                              \
	vec->cap = vec_new_cap_##name(vec->len + 1);                          \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	vec->arr[vec->len] = val;                                             \
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
	vec->cap = vec_new_cap_##name(vec->len + 1);                          \
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
	vec->cap = vec_new_cap_##name(vec->len - 1);                          \
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
	vec->cap = vec_new_cap_##name(vec->len - 1);                          \
	memmove(vec->arr, vec->arr + 1, sizeof(type) * vec->len);             \
	vec->len--;                                                           \
                                                                              \
	return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_append(struct vec_##name *des, const struct vec_##name src)      \
{                                                                             \
	if (des->arr == NULL && src.arr == NULL)                              \
		return -1;                                                    \
	if (src.arr == NULL)                                                  \
		return 0;                                                     \
	if (des->arr == NULL) {                                               \
		*des = src;                                                   \
		return 0;                                                     \
	}                                                                     \
	                                                                      \
	des->cap = vec_new_cap_##name(des->len + src.len);                    \
	if ((des->arr = realloc(des->arr, des->cap)) == NULL)                 \
		return -1;                                                    \
                                                                              \
	memcpy(des->arr + des->len, src.arr, sizeof(type) * src.len);         \
                                                                              \
	des->len += src.len;                                                  \
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
	vec->cap = vec_new_cap_##name(vec->len + 1);                          \
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
		if (memcmp(&vec->arr[i], &val, sizeof(type)) == 0)            \
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
	vec->cap = vec_new_cap_##name(vec->len - 1);                          \
	if ((vec->arr = realloc(vec->arr, vec->cap)) == NULL)                 \
		return vec->len;                                              \
                                                                              \
	vec->len--;                                                           \
                                                                              \
	return idx;                                                           \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_shrink(struct vec_##name *vec, const size_t len)                 \
{                                                                             \
	if (vec->arr == NULL)                                                 \
		return -1;                                                    \
	if (vec->len < len)                                                   \
		return -1;                                                    \
	if (vec->len == len)                                                  \
		return 0;                                                     \
	                                                                      \
	vec->len = len;                                                       \
	vec->cap = vec_new_cap_##name(len);                                   \
                                                                              \
	return (vec->arr = realloc(vec->arr, vec->cap)) ? 0 : -1;             \
}                                                                             \
                                                                              \
int                                                                           \
vec_##name##_getnth(struct vec_##name *vec, type *val, const size_t idx)      \
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
	vec->cap = vec_new_cap_##name(vec->len - 1);                          \
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
void                                                                          \
vec_##name##_free(struct vec_##name *vec)                                     \
{                                                                             \
	free(vec->arr);                                                       \
	vec->arr = NULL;                                                      \
	vec->cap = vec->len = 0;                                              \
}                                                                             \
                                                                              \
struct vec_##name##_semi { /* to enforce semicolon */ }

#define INIT_VEC(name, type)                                                  \
INIT_VEC_TYPE(name, type);                                                    \
INIT_VEC_FUNC(name, type)

#endif
