#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      int sizeSubtree;
      bst_node *left;
      bst_node *right;

      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int size = 1)
        : val { _val },  left { l }, right {r}, sizeSubtree {size}
      { }
    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success){
      if(r == nullptr){
        success = true;
        return new bst_node(x, nullptr, nullptr);
      }

      if(r->val == x){
        success = false;
        return r;
      }
      
      if(x < r->val){
        r->left = _insert(r->left, x, success);
        if (success)
          r->sizeSubtree++;
        if (isImbalanced(r))
          balance(r);
        return r;
      }
      else {
        r->right = _insert(r->right, x, success);
        if (success)
          r->sizeSubtree++;
        if (isImbalanced(r))
          balance(r);
        return r;
      }
    }
    
    static int max(int first, int second){
      if (first > second)
        return first;
      else
        return second;
    }

    static int min(int first, int second){
      if (first < second)
        return first;
      else
        return second;
    }

    static bool isImbalanced(bst_node* root){
      int left = (root->left == nullptr) ? 0 : root->left->sizeSubtree;
      int right = (root->right == nullptr) ? 0 : root->right->sizeSubtree;
      int minSize = min(left, right);
      int maxSize = max(left, right);

      if (maxSize > (minSize * 2 + 1))
        return true;
      return false;
    }

    static void balance(bst_node*& root){
      vector<T> * inorder = new vector<T>;
      _to_inorder_vector(inorder,root);
      root = _from_vec(*inorder, 0, inorder->size() - 1);
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      root = _insert(root, x, success);
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }

      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->right = _remove(r->right, r->val, sanity);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        else
          r->sizeSubtree--;

        if (isImbalanced(r))
          balance(r);
        return r;
      }
      if(x < r->val){
        r->left = _remove(r->left, x, success);
        if (success)
          r->sizeSubtree--;

        if (isImbalanced(r))
          balance(r);
      }
      else {
        r->right = _remove(r->right, x, success);
        if (success)
          r->sizeSubtree--;

        if (isImbalanced(r))
          balance(r);
      }
      
     
      return r;

    }

  public:

    bool remove(T & x){
      bool r = false;
      if (root != nullptr && root->val == x)
        r = true;

      bool success;
      root = _remove(root, x, success);

      return success;
    }


  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

    static void _to_inorder_vector(vector<T>*& res, bst_node* head){
      if (head == nullptr)
        return;

      _to_inorder_vector(res, head->left);
      res->push_back(head->val);
      _to_inorder_vector(res, head->right);
    }

    static bst_node* _get_ith(bst_node* root, const int& i){
      if (root == nullptr){
        cout << "_get_ith failed..." << endl;
        return nullptr;
      }

      int pos = (root->left != nullptr) ? 1 + root->left->sizeSubtree : 1;

      if (pos == i){
        return root;
      }
      else if (pos > i){ //Traverse left
        return _get_ith(root->left, i);
      }
      else{ //Traverse left
        return _get_ith(root->right, i - pos);
      }
    }

    static int _position_of(bst_node* root, const T& val){
      if (root == nullptr)
        return -1;

      if (root->val == val){
        int pos = (root->left != nullptr) ? 1 + root->left->sizeSubtree : 1;

        return pos;
      }
      else if (root->val > val){
        return _position_of(root->left, val);
      }
      else{
        int pos = (root->left != nullptr) ? 1 + root->left->sizeSubtree : 1;

        return pos + _position_of(root->right, val);
      }
    }

    static bool _num_geq(bst_node* root, const T& val, int& num){
      if (root == nullptr){
        return false;
      }

      if (root->val == val){
        int numGreater = (root->right != nullptr) ? root->right->sizeSubtree : 0;
        num += numGreater + 1;
        return true;
      }
      else if (root->val > val){ //Search left, add sum of right nodes plus 1 for node
        int numGreater = (root->right != nullptr) ? 1 + root->right->sizeSubtree : 1;
        num += numGreater;

        return _num_geq(root->left, val, num);
      }
      else{
        return _num_geq(root->right, val, num);
      }
    }

    static bool _num_leq(bst_node* root, const T& val, int& num){
      if (root == nullptr){
        return false;
      }

      if (root->val == val){
        int numLess = (root->left != nullptr) ? root->left->sizeSubtree : 0;
        num += numLess + 1;
        return true;
      }
      else if (root->val > val){
        return _num_leq(root->left, val, num);
      }
      else{
        int numLess = (root->left != nullptr) ? 1 + root->left->sizeSubtree : 1;
        num += numLess;

        return _num_leq(root->right, val, num);
      }
    }
    

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/

    /* TODO
     * Function:  to_vector
     * Description:  allocates a vector of type T and populates
     *               it with the elements of the tree in sorted
     *               order.  A pointer to the vector is returned.
     *
     * runtime:  O(n) where n is the tree size.
     *
     */
    std::vector<T> * to_vector() {
      vector<T>* res = new vector<T>;

      _to_inorder_vector(res, root);

      return res;
    }


    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T &x) {
      //Logic:  size attribute will tell us the size of the subtree.  Because i ranges [i,n], we want to find node with size = i?
      //This might work when searching to the left, but not when searching to the right.  
      //Thus, when searching to the right, it is actually the size of the left + the right... (this needs to be a running total because we can go right multiple times)
      //Current node is the root->left + 1 ith node in the tree.
        //If the current is too large, we go to the left.
        //If the current is too small, we go to the right and use i = i - root->left + 1

      if (i < 1 || i  > root->sizeSubtree)
        return false;

      bst_node* res = _get_ith(root, i);
      x = res->val;

      return true;
    }


    /* 
     * get_ith_SLOW:  slow version of get_ith which gives the right answer, but
     *   does so by "walking the entire tree".
     * might be helpful for debugging?
     * Private helper below does most of the work
     */
    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }

  private:
    // recursive helper function that does most of the work
    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

  public:

    /* TODO
     * Function: position_of 
     * Description:  this is like the inverse of
     *       get_ith:  given a value x, determine the 
     *       position ("i") where x would appear in a
     *       sorted list of the elements and return
     *       the position as an integer.
     *       If x is not in the tree, -1 is returned.
     *       Examples:
     *           if x happens to be the minimum, 1 is returned
     *           if x happens to be the maximum, n is returned where
     *               n is the tree size.                  
     *                  
     *       Notice the following property:  for a bst t with n nodes,                  
     *           pick an integer pos:1 <= pos <= n.                  
     *           Now consider the following:
     *       
                    T x;
                    int pos, pos2;
                    // set pos to a value in {1..n}
                    t.get_ith(pos, x);  // must return true since pos is in {1..n}

                    // now let's find the position of x (just retrieved) 
                    pos2 = t.position_of(x);
                    if(pos != pos2) {
                        std::cout << "THERE MUST BE A BUG!\n";
                    }

                 See how position_of performs the inverse operation of get_ith?
     *       
     * Return:  -1 if x is not in the tree; otherwise, returns the position where x 
     *          would appear in the sorted sequence of the elements of the tree (a
     *          value in {1..n}          
     *
     * Runtime:  O(h) where h is the tree height
     */
    int position_of(const T & x) {
      return _position_of(root, x);
    }

    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
    int num_geq(const T & x) {
      int count = 0;

      _num_geq(root, x, count);

      return count;
    }

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *                (private helper does most of the work)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }

  private:
    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }
    
  public:

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T &x) {
      int count = 0;
      _num_leq(root, x, count);
      return count;
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *               (private helper _num_leq_SLOW does most of the work)
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }
  private:

    // helper for num_leq_SLOW
    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

  public:

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_range(const T & min, const T & max) {
      int numLess = 0, numGreater = 0;
      bool containsMin = _num_leq(root, min, numLess);
      bool containsMax = _num_geq(root, max, numGreater);
      numLess = (containsMin) ? numLess - 1 : numLess;
      numGreater = (containsMax) ? numGreater - 1 : numGreater;


      return root->sizeSubtree - (numLess + numGreater);
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *               (private helper _num_range_SLOW does most of the work)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:
    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }

    static void _extract_range(vector<T>* res, bst_node* root, const T & min, const T & max){
      if (root == nullptr)
        return;

      if (root->val > min)
        _extract_range(res, root->left, min, max);

      if (root->val >= min && root->val <= max)
        res->push_back(root->val);

      if (root->val < max)
        _extract_range(res, root->right, min, max);
    }

  public:

    /*
     * TODO
     * function:     extract_range
     * Description:  allocates a vector of element type T
     *               and populates it with the tree elements
     *               between min and max (inclusive) in order.  
     *               A pointer to the allocated and populated
     *               is returned.
     *
     * notes/comments:  even if the specified range is empty, a
     *                  vector is still allocated and returned;
     *                  that vector just happens to be empty.
     *                  (The function NEVER returns nullptr).
     *
     * runtime:  the runtime requirement is "output dependent".
     *           Let k be the number of elements in the specified range
     *           (and so the length of the resulting vector) and let h
     *           be the height of the tree.  The runtime must be:
     *
     *                  O(h + k)
     *
     *           So...while k can be as large as n, it can be as small
     *           as zero.  
     *
     */
    std::vector<T> * extract_range(const T & min, const T & max) {
      vector<T>* res = new vector<T>;
      _extract_range(res, root, min, max);

      return res;
    }

  /***************************************************
  *  PREORDER AND INORDER TREE TRAVERSALS BELOW      * 
  *                                                  * 
  ***************************************************/

  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

  /***************************************************
  *  END PREORDER AND INORDER TREE TRAVERSALS        * 
  *                                                  * 
  ***************************************************/

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) return nullptr;
      m = (low+hi)/2;
      root = new bst_node(a[m]);
      root->sizeSubtree = hi - low + 1;
      root->left  = _from_vec(a, low, m-1);
      root->right = _from_vec(a, m+1, hi);
      return root;

    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){

      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);
      return t;
    }

  private:

    /*
     * DO NOT MODIFY THE TWO FUNCTIONS BELOW!!!
     */
    static void _to_preorder_vec(bst_node *t, std::vector<T> &vec) {
      if(t==nullptr) return;
      vec.push_back(t->val);
      _to_preorder_vec(t->left, vec);
      _to_preorder_vec(t->right, vec);
    }
    std::vector<T> * to_preorder_vec() {
      std::vector<T> *vec = new std::vector<T>();
      _to_preorder_vec(root, *vec);
      return vec;
    }

  /*
   * Finally, the data members of the bst class
   */
  public:
    bst_node *root;


}; // end class bst

#endif
