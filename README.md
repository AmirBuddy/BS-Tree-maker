# Construct BST from Traversals
This program constructs a binary search tree from its inorder and postorder/preorder traversal sequences. It demonstrates a clean recursive algorithm to build the tree structure on the fly. For the bonus, it will pretty print the tree as wll.

# Algorithm
The key functions are:
- ```build()```: Recursively constructs the BST given inorder and postorder/preorder queues
- ```getNodes()```: Reads traversal sequence from input into a queue
- ```buildTree()```: Wraps ```build()``` to handle postorder vs preorder
- ```horizontal_printer()``` and ```vertical_printer()```: Print tree in horizontal and vertical formats
# License
This project is licensed under the MIT License
