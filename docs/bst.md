Binary Search Tree
==================

Binary search tree map.

| Operation | Average  | Worst |
|-----------|:--------:|:-----:|
| Insert    | O(log n) | O(n)  |
| Search    | O(log n) | O(n)  |
| Remove    | O(log n) | O(n)  |

`struct bst_<name> bst_<name>_new(int (*cmp)(key_t, key_t))`
------------------------------------------------------------

Creates an empty binary search tree.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

bst_int bst = bst_int_new(cmp);
```

`struct bst_<name> bst_<name>_from(const key_t key[], const val_t val[], const size_t len, int (*cmp)(key_t, key_t))`
---------------------------------------------------------------------------------------------------------------------

Creates binary search tree from arrays of keys and values.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

assert(bst.len == 3);
assert(bst.root->val == 2);
assert(bst.root->lch->val == 1);
assert(bst.root->rch->val == 3);
```

`struct bst_<name> bst_<name>_copy(const struct bst_<name> bst)`
----------------------------------------------------------------

Creates deeply copied binary search tree.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int old = bst_int_from(key, val, 3, cmp);
bst_int new = bst_int_copy(old);

assert(new.root->val == old.root->val);
assert(new.root->lch->val == old.root->lch->val);
assert(new.root->rch->val == old.root->rch->val);
```

`int bst_<name>_insert(struct bst_<name> *bst, const key_t key, const val_t val)`
---------------------------------------------------------------------------------

Inserts a key-value pair into binary search tree.  
Returns 0 on success, -1 when key is already exist or out of memory.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

bst_int_insert(&bst, 4, 4);

assert(bst.len == 4);
assert(bst.root->rch->rch->key == 4);
assert(bst.root->rch->rch->val == 4);
```

`int bst_<name>_search(struct bst_<name> *bst, const key_t key, val_t *val)`
----------------------------------------------------------------------------

Finds value corresponding to the key.  
Returns 0 on success, -1 on failure.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int v;
int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

bst_int_search(&bst, 1, &v);

assert(v == 1);
```

`int bst_<name>_remove(struct bst_<name> *bst, const key_t key, val_t *val)`
----------------------------------------------------------------------------

Finds value corresponding to the key and remove it from tree.  
Returns 0 on success, -1 on failure.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int v;
int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

bst_int_remove(&bst, 1, &v);

assert(v == 1);
assert(bst.len == 2);
```

`val_t *bst_<name>_getptr(struct bst_<name> *bst, const key_t key)`
-------------------------------------------------------------------

Returns pointer of the value corresponding to the key, NULL when key does not exist.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

assert(*bst_int_getptr(&bst, 1) == 1);
```

`val_t *bst_<name>_root(struct bst_<name> *bst)`
------------------------------------------------

Returns pointer of root value, NULL when tree is empty.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

assert(*bst_int_root(&bst) == 2);
```

`val_t *bst_<name>_max(struct bst_<name> *bst)`
-----------------------------------------------

Returns pointer of value that its key is the greatest in tree, NULL when tree is empty.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

assert(*bst_int_max(&bst) == 3);
```

`val_t *bst_<name>_min(struct bst_<name> *bst)`
-----------------------------------------------

Returns pointer of value that its key is the least in tree, NULL when tree is empty.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

assert(*bst_int_min(&bst) == 1);
```

`void bst_<name>_free(struct bst_<name> *bst)`
----------------------------------------------

Deallocate tree from memory. Prevents dangling pointer.

```c
INIT_BST(int, int, int);

int 
cmp(int x, int y)
{ 
	return x - y; 
}

int key[] = { 2, 1, 3 };
int val[] = { 2, 1, 3 };
bst_int bst = bst_int_from(key, val, 3, cmp);

bst_int_free(&bst);

assert(bst.root == NULL);
assert(bst.len == 0);
```
