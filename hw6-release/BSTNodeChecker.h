#include "BSTNode.h"

class BSTNodeChecker
{
public:
    /**
     * Checks if the tree rooted at node is a valid Binary Search Tree. If node
     *  is nullptr, it is considered a valid BST.
     *
     * @param node the root of the tree
     * @return true iff the tree rooted at node is a valid Binary Search Tree
     */
    bool is_bst(const BSTNode *node);

    /**
     * Checks if the tree rooted at node is a valid AVL Tree. If node is
     *  nullptr, it is considered a valid AVL Tree.
     *
     * @param node the root of the tree
     * @return true iff the tree rooted at node is a valid AVL Tree
     */
    bool is_avlt(const BSTNode *node);

    /**
     * Checks if the tree rooted at node is a valid Red-Black Tree. If node is
     *  nullptr, it is considered a valid Red-Black Tree.
     *
     * @param node the root of the tree
     * @return true iff the tree rooted at node is a valid Red-Black Tree
     */
    bool is_rbt(const BSTNode *node);

private:
    /**
     * Returns the black-height of the tree rooted at node, or -1 if the tree is
     *  not a valid Red-Black Tree. If node is nullptr, the black-height is 0.
     *
     * @param node the root of the tree
     * @return the black-height of the tree rooted at node, or -1 if the tree is
     *  not a valid Red-Black Tree
     */
    int blackheight(const BSTNode *node);

    /**
     * Checks if the tree rooted at node is black-height balanced.
     *
     * @param node the root of the tree
     * @return true iff the tree rooted at node is black-height balanced
     */
    bool is_blackheight_balanced(const BSTNode *node);

    /**
     * Checks if the tree rooted at node has no red-red violations.
     *
     * @param node the root of the tree
     * @return true iff the tree rooted at node has no red-red violations
     */
    bool has_no_rrvs(const BSTNode *node);
};
