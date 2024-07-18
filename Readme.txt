Augmented Binary Search Tree
This project implements an augmented binary search tree (BST) in C++ with automatic balancing. It includes various advanced functionalities such as finding nodes based on different criteria and creating a tree from an in-order vector.

Features
Automatic Balancing: The tree is automatically balanced to ensure optimal performance.
Node Counting Functions:
num_geq: Find the number of nodes greater than or equal to a specified value.
num_leq: Find the number of nodes less than or equal to a specified value.
Node Retrieval Functions:
get_ith: Retrieve the i-th smallest node in the tree.
get_range: Retrieve all nodes within a specified range.
Tree Construction:
Create a tree from an in-order vector.
Getting Started
Prerequisites
C++ compiler (e.g., g++)
Basic knowledge of using terminal and make commands
Building and Running the Program

Clone the repository:
git clone https://github.com/kbanushi/Augmented-BST.git

Build the program:
make

Run the program:
./bst

Usage
The program includes various functions for interacting with the augmented binary search tree. Below are some example usages:

Creating a Tree from an In-Order Vector:

std::vector<int> inorder = {1, 2, 3, 4, 5};
AugmentedBST tree(inorder);

Finding the Number of Nodes Greater Than or Equal to a Value:
int count_geq = tree.num_geq(3);

Finding the Number of Nodes Less Than or Equal to a Value:
int count_leq = tree.num_leq(3);

Retrieving the i-th Smallest Node:
Node* ith_node = tree.get_ith(2);

Retrieving All Nodes Within a Range:
std::vector<Node*> range_nodes = tree.get_range(2, 4);
