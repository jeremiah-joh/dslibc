# Data Structure Library for C
A collection of useful data structures written in ANSI C.

## Data structures
| File name | Data structure name | Insert | Remove | Search | State |
|:---------:|---------------------|--------|--------|--------|-------|
| vec.h | Vector (Double-Ended Queue) | O(n) | O(n) | O(1) | O |
| ll.h | (Doubly, Singly) Linked List | O(1) | O(n) | O(n) | O |
| bst.h | Binary Search Tree | O(log n) ~ O(n) | O(log n) ~ O(n) | O(log n) ~ O(n) | O |
| avl.h | AVL tree | O(log n) | O(log n) | O(log n) | X |
| rb.h | Red-Black tree | O(log n) | O(log n) | O(log n) | X |
| splay.h | Splay tree | O(log n) ~ O(n) | O(log n) ~ O(n) | O(log n) ~ O(n) | O |
| ht.h | Hash table | O(1) ~ O(n) | O(1) ~ O(n) | O(1) ~ O(n) | O |

note: all logs are base 2 logs
