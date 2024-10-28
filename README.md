Data Structure Library for C
============================

A collection of useful data structures written in ANSI C.

| data structure     | header  | state |
|--------------------|---------|-------|
| Vector             | vec.h   |   O   |
| Singly Linked List | sll.h   |   O   |
| Doubly Linked List | dll.h   |   O   |
| Binary Search Tree | bst.h   |   O   |
| AVL Tree           | avl.h   |   X   |
| B Tree             | bt.h    |   X   |
| Red-Black Tree     | rbt.h   |   X   |
| Splay Tree         | spt.h   |   X   |
| Heap               | heap.h  |   O   |
| Hash Table         | ht.h    |   O   |

Installation
------------

Following commands will install these header files under `/usr/local/include`.

	$ git clone https://github.com/jeremiah-joh/dslibc.git
	$ cd dslibc
	# make install

Usage
-----

You could use this library with or without installation. If you don't want to
install, then just put one of these header files into your project directory.

Then, include the header file and use it. There is an [API document](doc).

License
-------

dslibc by Woohyun Joh is marked with CC0 1.0
