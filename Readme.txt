


Name: Krenar Banushi

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

YES




Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

The BST node was changed to allow for an int called sizeSubtree.  This is used to keep track of the size of a sub tree starting at bst_node.
To book keep the sizeSubtree, I made changes to the insert and delete functions to increment and decrement the node's sizeSubtree as we bubble back out from where the node was inserted/removed.

To accommadate for BST balancing, I check nodes while bubbling back to root to see if they are considered imbalanced by the definition, and if so we rebalance them by putting the nodes in a vector using an in order traversal, then split that up back into a balanced tree.






-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  


_insert and _delete






-----------------------------------------------
For each function from the previous question, how did you ensure that the (asymptotic) runtime 
remained the same?


The modifications I made were either constant time operations, or only took place when the project conditions were met, i.e., to increase the size of the subree we can do that in constant time, but to rebalance the subtree we would do that in linear time of how many nodes are in the subtree.  This only happens when a subtree is imbalanced after an insertion or deletion, and would only occupy a fraction of the entire tree, so that could be amortized if the nodes being inserted are semi random.





-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  ____5_______  


-----------------------------------------------
get_ith level of completion:  ______5_____  

    How did you ensure O(h) runtime?

    ANSWER: Yes
-----------------------------------------------
position_of level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: Yes
-----------------------------------------------
num_geq level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: Yes

-----------------------------------------------
num_leq level of completion:  ______5______

    How did you ensure O(h) runtime?

    ANSWER: Yes

-----------------------------------------------
num_range level of completion:  ____5________

    How did you ensure O(h) runtime?

    ANSWER: Yes

-----------------------------------------------
extract_range level of completion:  _____5_______

    How did you ensure O(h+k) runtime?

    ANSWER: Yes

Implementation of size-balanced criteria according to 
the given guidelines:

    Level of completion: _____5______











