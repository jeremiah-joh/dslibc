# Data Structure Library for C
A collection of useful data structures written in C.

## Data structures
| file name | data structure name | insert | remove | search | state |
|:---------:|---------------------|--------|--------|--------|-------|
| vec.h | Vector(Double-Ended Queue) | O(n) | O(n) | O(1) | O |
| ll.h | (Double, Singly) Linked List | O(n) | O(n) | O(n) | O |
| bst\_map.h, bst\_set.h | Binary Search Tree | O(log n) ~ O(n) | O(log n) ~ O(n) | O(log n) ~ O(n) | O |
| avl\_map.h, avl\_set.h | AVL tree | O(log n) | O(log n) | O(log n) | X |
| rb\_map.h, rb\_set.h | Red-Black tree | O(log n) | O(log n) | O(log n) | X |
| splay\_map.h, splay\_set.h | Splay tree | O(log n) ~ O(n) | O(log n) ~ O(n) | O(log n) ~ O(n) | X |
| hash\_map.h, hash\_set.h | Hash table | O(1) ~ O(n) | O(1) ~ O(n) | O(1) ~ O(n) | O |

note: all logs are base 2 logs
