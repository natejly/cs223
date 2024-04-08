#include "BSTNode.h"
#include <iostream>
#include <deque>

class BSTNodePrinter
{
public:
    /**
     * This function is implemented for you, for your convenience.
     *
     * @param out the output stream to print to
     */
    BSTNodePrinter(std::ostream &out) : out(out) {}

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param node the root of the tree
     * @param level the level of node in the tree (root is at level 1)
     * @param indent_space the number of spaces to indent
     * @result prints the tree rooted at node to the output stream this->out,
     *  using the "pretty print" format. The root of the tree is printed at the
     *  top, and the children of each node are printed below their parent.
     */
    void print_pretty(const BSTNode *node, int level, int indent_space);

private:
    std::ostream &out;

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param node the node to decorate
     * @return the decorator to print with node using its to_string function.
     *  The decorator is either nothing, '*', 'r', or 'R' (computed as node is
     *  BLACK with multiplicity <=1, BLACK with multiplicity >1, RED with multiplicity =1, or RED with
     *  multiplicity >1).
     */
    std::string decorator_string(const BSTNode *node);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param node the node to get the value label for
     * @return node's data as a string, or empty_string if node is an empty tree.
     */
    std::string value_string(const BSTNode *node);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param node the node to print
     * @return a string that is the concatenation of the node's data and its
     *  "decorator", which is either "", "*", "r", or "R" (computed as the node
     *  is BLACK with multiplicity=1, BLACK with multiplicity>1, RED with multiplicity 1, or RED
     *  with multiplicity>1). This DOES NOT produce a recursive "pretty print" output.
     *  If node is empty, returns empty string.
     *
     * Runtime Complexity: O(1)
     */
    std::string node_string(const BSTNode *node);

    /**
     * This function is implemented for you, for your convenience.
     *
     * @param node the node to print
     * @param width the width of the field to print node in
     * @return node, centered in width
     */
    std::string centered(const BSTNode *node, int width);

    /**
     * Prints the branches of a tree. This is a helper function for print_pretty.
     *
     * @param branch_len the length of each branch to print
     * @param node_space_len the number of spaces between nodes
     * @param start_len the number of spaces before the first node should start
     * @param nodes_in_this_level the number of nodes in this level that must be
     *  printed out
     * @param nodes_queue a deque of nodes for this level's nodes
     */
    void print_branches(int branch_len,
                        int node_space_len,
                        int start_len,
                        int nodes_in_this_level,
                        const std::deque<const BSTNode *> &nodes_queue);

    /**
     * Prints the nodes for a level of the tree.
     *
     * @param branch_len the length of each branch to print
     * @param node_space_len the number of spaces between nodes
     * @param start_len the number of spaces before the first node should start
     * @param nodes_in_this_level the number of nodes in this level that must be
     *  printed out
     * @param nodes_queue a deque of nodes for this level's nodes
     */
    void print_nodes(int branch_len,
                     int node_space_len,
                     int start_len,
                     int nodes_in_this_level,
                     const std::deque<const BSTNode *> &nodes_queue);
    /**
     * Prints the leaves of a tree. Nearly identical to print_nodes except it does
     *  not print surrounding '_' to fill widths, instead surrounding each node
     *  with spaces.
     *
     * @param indent_space the number of spaces by which to indent this level
     * @param leaf_space the number of spaces between adjacent leaves of the
     *  tree
     * @param nodes_in_this_leve the number of nodes in this level that are being
     *  printed
     * @param nodes_queue a deque of nodes for this level's nodes
     */
    void print_leaves(int indent_space,
                      int leaf_space,
                      int nodes_in_this_level,
                      const std::deque<const BSTNode *> &nodes_queue);
};