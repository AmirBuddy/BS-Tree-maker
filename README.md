# Construct BST from Traversals
This program constructs a binary search tree from its inorder and postorder/preorder traversal sequences. It demonstrates a clean recursive algorithm to build the tree structure on the fly. For the bonus, it will pretty print the tree as wll.

# Algorithm
The key functions are:
- ```build()```: Recursively constructs the BST given inorder and postorder/preorder queues
- ```getNodes()```: Reads traversal sequence from input into a queue
- ```buildTree()```: Wraps ```build()``` to handle postorder vs preorder
- ```horizontal_printer()``` and ```vertical_printer()```: Print tree in horizontal and vertical formats

```build()``` uses the following logic:
- Base cases: empty queues or single node
- Split inorder around root to get left and right halves
- Split post/pre accordingly to get left and right subtrees
- Recursively build left and right subtrees
- Connect subtrees to root

Traversal type is identified by comparing root to post/pre queue front.

# Algorithmic Cleverness
While using inorder and postorder/preorder to construct BSTs is a common technique, this implementation stands out for its elegant design:
- ###Queues as input:

# Usage
Provide inorder traversal, followed by postorder or preorder traversal:
```
Enter in-order traversal of the tree with space in between(x x x ...):
4 2 5 1 3 
Which one do you want to enter now:
1. post
2. pre
Your choice: 1
Enter the traversal:
4 5 2 3 1
```
Tree will be constructed and printed.
# License
This project is licensed under the MIT License
