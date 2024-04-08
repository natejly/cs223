#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cassert>

/**
 * Binary Search Tree Node. A BSTNode is a node in a binary search tree, which
 *  is a binary tree with the following properties:
 *  - The left subtree of a node contains only nodes with values less than
 *      the node's value
 *  - The right subtree of a node contains only nodes with values greater
 *      than the node's value
 *  - The left and right subtree are each also be a binary search tree
 *
 * A BSTNode also has the following (private) properties, some of which have an
 *  associated (public) getter function, but no setter function. These
 *  properties are:
 *  - data is the value of this node
 *  - count is the number of times the data has been inserted into the
 *      tree (minus the number of times it has been removed from the tree)
 *  - height is the height of the node within the tree, increasing
 *      from leaf (0) up to the root.
 *  - left, right are the (possibly NULL) pointers to the left and right
 *      children, respectively
 *  - parent is the (possibly NULL) pointer to the parent node
 *
 * If the BSTNode represents an empty tree, then its properties are:
 *  - data = [unspecified]
 *  - count = 0
 *  - height = -1
 *  - left, right = nullptr
 *  - parent = [unspecified]
 *
 * The BSTNode class also has the following public methods:
 *  - minimum_value() returns the node with the minimum value in the tree
 *  - maximum_value() returns the node with the maximum value in the tree
 *  - search(int value) returns the node with the given value in the tree
 *  - bst_insert(int value) inserts a value into the tree
 *  - avl_insert(int value) inserts a value into the tree
 *  - rbt_insert(int value) inserts a value into the tree
 *  - bst_remove(int value) removes a value from the tree
 *  - avl_remove(int value) removes a value from the tree
 *  - rbt_remove(int value) removes a value from the tree
 *  - node_count() returns the number of non-empty nodes in the tree
 *  - count_total() returns the total of all counts in the tree
 *  - is_empty() returns true iff the tree is empty
 */
class BSTNode
{
public:
    /***********
     * GETTERS *
     ***********/

    /**
     * Getter for this->mData
     */
    int data() const;

    /**
     * Getter for this->mCount
     */
    int count() const;

    /**
     * Getter for this->mHeight
     */
    int height() const;

    /**
     * Getter for this->mLeft
     */
    const BSTNode *left_child() const;

    /**
     * Getter for this->mRight
     */
    const BSTNode *right_child() const;

    /********************
     * CONSTRUCTORS AND *
     *    DESTRUCTOR    *
     ********************/

    /**
     * Default Constructor. It is implemented for you, for your convenience.
     *
     * @return a newly-created node representing an empty tree
     * @result creates a new empty tree with default values:
     *  - mData = [unspecified]
     *  - mCount = 0
     *  - mHeight = -1
     *  - mColor = BLACK
     *  - mLeft, mRight, parent = nullptr
     *
     * Runtime Complexity: O(1)
     */
    BSTNode();

    /**
     * This constructor is implemented for you, for your convenience.
     *
     * @param data (the value to store)
     * @return a newly-created tree node.
     * @result creates a new BSTNode with default values:
     *  - mData = value
     *  - mCount = 1
     *  - mHeight = 0
     *  - mColor = BLACK
     *  - mLeft, mRight = [empty tree]
     *  - parent = nullptr
     *
     * Runtime Complexity: O(1)
     */
    BSTNode(int data);

    /**
     * Copy constructor.
     *
     * @param other the node to copy
     * @return the root of a tree that is a copy of the tree rooted at other
     * @result creates a new node with the same properties as other by
     *  performing a pre-order deep copy of the tree rooted at other. The root
     *  of the new tree has parent nullptr (it is considered the ultimate root
     *  of its tree).
     *
     * Runtime Complexity: O(n)
     */
    BSTNode(const BSTNode &other);

    /**
     * Destructor.
     *
     * @param this the root of the tree to free
     * @result Performs a post-order delete to free all memory owned by this.
     *
     * Remember: `this` is automatically freed at the end of a destructor.
     *
     * Runtime Complexity: O(n)
     */
    ~BSTNode();

    /********************
     * PUBLIC FUNCTIONS *
     ********************/

    /**
     * Returns the minimum value in the tree rooted at this.
     *
     * @param this the root of the tree
     * @return a pointer to the node with the minimum value in the tree rooted
     *  at this
     * @assumes this is not an empty tree
     *
     * Runtime Complexity: O([height of tree rooted at this])
     */
    const BSTNode *minimum_value() const;

    /**
     * Returns the maximum value in the tree rooted at this
     *
     * @param this the root of the tree
     * @return: a pointer to the node with the maximum value in the tree rooted
     *  at this.
     * @assumes this is not an empty tree
     *
     * Runtime Complexity: O([height of tree rooted at this])
     */
    const BSTNode *maximum_value() const;

    /**
     * Searches for value in this.
     *
     * @param this the root of the tree
     * @param value the value for which to search in the tree
     * @return a pointer to the node with value in the tree rooted at this, or
     *  an empty tree if value is not in this
     *
     * Runtime Complexity: O([height of tree rooted at this])
     */
    const BSTNode *search(int value) const;

    /**
     * Inserts value into this.
     *
     * @param this the root of the tree
     * @param value the value to insert
     * @return a pointer to the root of the tree into which value has just been
     *  inserted, with parent `nullptr`
     * @result inserts (a single occurrence of) value into the tree rooted at
     *  this. Uses the "naive BST" insertion algorithm.
     *
     * Runtime Complexity: O([height of tree rooted at this])
     */
    BSTNode *bst_insert(int value);

    /**
     * Inserts value into this.
     *
     * @param this the root of the tree
     * @param value the value to insert
     * @return a pointer to the root of the tree into which value has just been
     *  inserted, with parent `nullptr`. The returned tree is an AVL Tree.
     * @result inserts (a single occurrence of) value into the tree rooted at
     *  this. Uses the AVL Tree insertion algorithm.
     * @assumes this is the root of an AVL Tree
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *avl_insert(int value);

    /**
     * Inserts value into this.
     *
     * @param this the root of the tree
     * @param value the value to insert
     * @return a pointer to the root of the tree into which value has just been
     *  inserted, with parent `nullptr`. The returned tree is a Red-Black Tree.
     * @result inserts (a single occurrence of) value into the tree rooted at
     *  this. Uses the Red-Black Tree insertion algorithm.
     * @assumes this is the root of an Red-Black Tree
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *rbt_insert(int value);

    /**
     * Removes value from this.
     *
     * @param this the root of the tree
     * @param value the value to remove
     * @return a pointer to the root of the tree from which value has just been
     *  removed, whose parent pointer is `nullptr`. This method may return an
     *  empty tree.
     * @result removes (a single occurrence of) value from the tree rooted at
     *  this. Uses the "naive BST" removal algorithm. Does nothing if value is
     *  not in this.
     *
     * Runtime Complexity: O([height of tree rooted at this])
     */
    BSTNode *bst_remove(int value);

    /**
     * Removes value from this.
     *
     * @param this the root of the tree
     * @param value the value to remove
     * @return a pointer to the root of the tree from which value has just been
     *  removed, whose parent pointer is `nullptr`. This method may return an
     *  empty tree. The returned tree is an AVL Tree.
     * @result removes (a single occurrence of) value from the tree rooted at
     *  this. Uses the AVL Tree removal algorithm.
     * @assumes this is the root of an AVL Tree
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *avl_remove(int value);

    /**
     * This function is implemented for you, for your convenience.
     * Removes value from this.
     *
     * @param this the root of the tree
     * @param value the value to remove
     * @return a pointer to the root of the tree from which value has just been
     *  removed, whose parent pointer is `nullptr`. This method may return an
     *  empty tree. The returned tree is an Red-Black Tree.
     * @result removes (a single occurrence of) value from the tree rooted at
     *  this. Uses the Red-Black Tree removal algorithm.
     * @assumes this is the root of a Red-Black Tree
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *rbt_remove(int value);

    /**
     * @param this the root of the tree
     * @return the number of non-empty nodes in the tree rooted at this
     *
     * Runtime Complexity: O(n)
     */
    int node_count() const;

    /**
     * @param this the root of the tree
     * @return the total of all counts in the tree rooted at this
     *
     * Runtime Complexity: O(n)
     */
    int count_total() const;

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the root of a BST
     * @return true iff this is an empty tree
     *
     * Runtime Complexity: O(1)
     */
    bool is_empty() const;

private:
    /****************************
     * PRIVATE ENUM DEFINITIONS *
     *       DO NOT MODIFY      *
     ****************************/
    enum Color
    {
        BLACK,
        RED
    };

    enum Direction
    {
        LEFT,
        ROOT,
        RIGHT
    };

    enum Shape
    {
        SHAPE_NONE,
        LL,
        LR,
        RL,
        RR
    };

    /*******************
     * PRIVATE MEMBERS *
     *  DO NOT MODIFY  *
     *******************/

    int mData;
    int mCount;
    int mHeight;
    Color mColor;
    BSTNode *mLeft;
    BSTNode *mRight;
    BSTNode *parent;

    /****************************
     * PRIVATE TYPE DEFINITIONS *
     *      DO NOT MODIFY       *
     ****************************/

    /**
     * You should use this struct in your code to help manage the complexity of
     *  insertion into a Red-Black Tree.
     *
     * Struct representing the neighborhood of a node with a possible red-red
     *  violation, organized in one of the following shapes (? trees are
     *  possibly empty, and the red-red violation is between [p] and [x]):
     *
     * Shape LL:
     *      __g__
     *     /     \
     *   [p]     y?
     *   / \
     * [x]  ?
     *
     * Shape LR:
     *      __g__
     *     /     \
     *   [p]     y?
     *   / \
     *  ?  [x]
     *
     * Shape RL:
     *      __g__
     *     /     \
     *    y?     [p]
     *           / \
     *         [x]  ?
     *
     * Shape RR:
     *      __g__
     *     /     \
     *    y?     [p]
     *           / \
     *          ?  [x]
     *
     */
    struct RRVNeighborhood
    {
        BSTNode *g;
        BSTNode *p;
        BSTNode *x;
        BSTNode *y;
        Shape shape;

        /**
         * This constructor is implemented for you, for your convenience.
         *
         * Input: Node g - the root of the neighborhood
         * Returns: A new neighborhood with given root g. If g is not BLACK or
         *  has height <= 1 or if there is no red-red-violation or if there is
         *  more than one red-red violation, the constructor produces a
         *  neighborhood with SHAPE_NONE and p, x, and y pointers that have
         *  undefined value.
         *
         * Runtime Complexity: O(1)
         */
        RRVNeighborhood(BSTNode *g);
    };

    /**
     * You should not use this struct in your functions. It is used only in
     *  rbt_remove, which is implemented for you.
     *
     * Struct representing the neighborhood of a node with a possible
     *  black-height violation, organized in one of the following shapes or
     *  their reflections (? trees are possibly empty or missing, red nodes
     *  have [], nodes of possibly either color have ()). The dir field is the
     *  direction of n relative to its parent, p. The neighborhood of n may not
     *  match any of these cases, in which case there is no black-height
     *  violation and therefore there is no special treatment required for
     *  removal from a Red-Black Tree; its deletion case is CASE_NONE and all
     *  pointers in the neighborhood except for n are nullptr.
     *
     * @param n the node that is about to be deleted
     * @param p the parent of n
     * @param s the sibling of n
     * @param c the child of n in the direction of the violation
     * @param d the child of n in the opposite direction of the violation
     *
     * Case CASE_1:
     *        n?
     *
     * Case CASE_2:
     *      __p__
     *     /     \
     *    n       s?
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_3:
     *      __p__
     *     /     \
     *    n      [s]
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_4:
     *      _[p]_
     *     /     \
     *    n       s?
     *   / \     / \
     *  ?   ?   c?  d?
     *
     * Case CASE_5:
     *      _(p)_
     *     /     \
     *    n       s
     *   / \     / \
     *  ?   ?  [c]  d?
     *
     * Case CASE_6:
     *      _(p)_
     *     /     \
     *    n       s
     *   / \     / \
     *  ?   ?   c? [d]
     *
     */
    struct BHVNeighborhood
    {
        /**
         * Struct to manage the complexity of deletion from a Red-Black Tree. You
         *  should not use this struct in your functions. It is used only by
         *  BHVNeighborhood.
         */
        enum Case
        {
            CASE_NONE,
            CASE_1,
            CASE_2,
            CASE_3,
            CASE_4,
            CASE_5,
            CASE_6
        };

        BSTNode *n;
        BSTNode *p;
        BSTNode *s;
        BSTNode *c;
        BSTNode *d;
        Case del_case;
        Direction dir;

        /**
         * This constructor is implemented for you, for your conveience.
         *
         * @param n the node that is about to be deleted
         * @param dir the direction of n from its parent
         * @return a new neighborhood with given Node n, which is in one of
         *  the 6 possible deletion cases described above, each of which may be
         *  in one of two directions. If n has no parent, the direction of the
         *  new neighborhood will be ROOT, otherwise the direction of the new
         *  neighborhood will match dir, the parameter to this constructor.
         *
         * Runtime Complexity: O(1)
         */
        BHVNeighborhood(BSTNode *p, Direction dir);

        /**
         * This function is implemented for you, for your convenience.
         *
         * @param this the neighborhood of the node that is about to be deleted
         *  from its tree.
         * @result Eliminates the black-height violation (if there is one) in
         *  the tree containing this by "bubbling up" the tree.
         *
         * Runtime Complexity: O(log n)
         */
        void fix_blackheight_imbalance();
    };

    /**********************************
     *       PRIVATE FUNCTIONS        *
     * YOU MAY ADD MORE AS NEEDED BUT *
     *      DO NOT MODIFY THESE       *
     **********************************/

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the node to get the child of
     * @param dir the direction to go
     * @return the child of node in the direction matching dir. Returns this if
     *  dir is ROOT.
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *child(Direction dir) const;

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the node to set the child of
     * @param dir the direction to go
     * @param child the node to replace as a child
     * @result sets the child of node in the direction matching dir to child,
     *  and sets child's parent to this. Does nothing if dir is ROOT.
     *
     * Runtime Complexity: O(1)
     */
    void set_child(Direction dir, BSTNode *child);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the node to check
     * @param dir the direction to check
     * @return true iff this has a non-empty child in the direction matching dir
     * @assumes dir is not ROOT
     */
    bool has_child(Direction dir) const;

    /**
     * Inserts value into this using the red-black tree insertion algorithm.
     *  Does not guarantee the returned node is BLACK.
     *
     * @param this the root of the tree
     * @param value the value to insert
     * @returns a pointer to the root of the tree into which value has just
     *  inserted
     * @result inserts (a single occurrence of) value into the tree rooted at
     *  this. Uses the Red-Black Tree insertion algorithm.
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *rbt_insert_helper(int value);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the root of the tree
     * @param value the value to remove
     * @param nb reference to a BHV Neighborhood; value is replaced with the
     *  neighborhood of the marked node (after this function, nb.n and nb.p's
     *  child to nb.dir are each an invalid pointer, pointing to the deleted
     *  node).
     * @return a pointer to the root of the tree from which value has been
     *  marked for removal, whose parent pointer is `nullptr`. This method may
     *  return an empty tree. This method may return a tree with a blackheight
     *  violation.
     * @result marks for removal (a single occurrence of) value from the tree
     *  rooted at this, but does not actually remove anything. Uses the
     *  Red-Black Tree removal algorithm.
     *
     * Runtime Complexity: O(log n)
     */
    BSTNode *rbt_remove_helper(int value, BHVNeighborhood &nb, BSTNode *&to_delete);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the root of the tree.
     * @param dir the direction in which to rotate
     * @return pointer to the root of rotated tree, whose parent pointer is
     *  undefined.
     * @result rotates tree rooted at this in the direction dir. If dir is
     *  ROOT, this function does nothing.
     * @assumes this has a non-empty subtree in the opposite direction of dir
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *dir_rotate(Direction dir);

    /**
     * @param this the root of the tree.
     * @return pointer to the root of rotated tree, whose parent pointer is the
     *  parent of this.
     * @result right rotate tree rooted at this
     * @assumes this has a non-empty left subtree
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *right_rotate();

    /**
     * @param this the root of the tree.
     * @return pointer to the root of rotated tree, whose parent pointer is the
     *  parent of this.
     * @result left rotate tree rooted at this
     * @assumes this has a non-empty right subtree
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *left_rotate();

    /**
     * @param this the root of an almost-balanced AVL Tree.
     * @return the balanced tree.
     * @result If unbalanced, balances the tree rooted at node.
     * @assumes the height difference between this's left and right children is
     *  no more than 2.
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *avl_balance();

    /**
     * @param this the root of an almost-balanced Red-Black tree.
     * @return A pointer to the root of the balanced tree
     * @result Eliminates the red-red violation (if there is one) in the
     *  neighborhood of this, meaning this and its children and one of its
     *  grandchildren (the grandchild that is the cause of a red-red violation,
     *  if there is one). The black-height of the returned tree is the same as
     *  the black-height of this and the returned node is the root of a
     *  Red-Black tree, with the possible exception that it is RED. If there is
     *  no violation, return this unchanged.
     * @assumes the only violation of Red-Black tree invariants in this appear
     *  in the neighborhood of this, and that violation is a single red-red
     *  violation, or that there are no violations at all in the tree rooted at
     *  this.
     *
     * Runtime Complexity: O(1)
     */
    BSTNode *rbt_eliminate_red_red_violation();

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the root of the tree
     * @return integer value signifying the height difference
     * @result calculates the difference in the height of the left and right
     *      subtree of this, computed as (right-height - left-height)
     *
     * Runtime Complexity: O(1)
     */
    int height_diff() const;

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this a node in a Binary Search Tree
     * @result Updates the tree rooted at this to be locally consistent, in the
     *  following way:
     *      - this.height = 1 + MAX(this.left.height, this.right.height)
     *      - this.left.parent = this
     *      - this.right.parent = this
     *  If this is empty, this.height is set to -1 and nothing is done to its
     *      children.
     *
     * Runtime Complexity: O(1)
     */
    void make_locally_consistent();

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param this the first node
     * @param other the second node
     * @result swaps the colors of this and other
     *
     * Runtime Complexity: O(1)
     */
    void swap_colors_with(BSTNode *b);

    /********************************
     * FRIEND FUNCTIONS AND CLASSES *
     *        DO NOT MODIFY         *
     ********************************/

    friend class BSTNodeChecker;
    friend class BSTNodePrinter;

    friend Direction opposite_direction(Direction dir);
};
