#include "BSTNodePrinter.h"

using namespace std;

#define NODE_W (4)

void BSTNodePrinter::print_pretty(const BSTNode *node, int level, int indent_space)
{
    int h = node->mHeight;
    int nodes_in_this_level = 1;

    int leaf_space = 2 * level;

    int tree_w = (NODE_W + leaf_space) * (int)pow(2, h) - leaf_space;

    int center_of_first_node = tree_w / 2;
    int distance_to_first_arm = center_of_first_node / 2;

    int start_len = distance_to_first_arm + 1;
    int branch_len = center_of_first_node - start_len - (NODE_W / 2);
    int node_space_len = 2 * start_len + (NODE_W / 2);

    deque<const BSTNode *> nodes_queue;
    nodes_queue.push_back(node);
    for (int r = h; r > 0; r--)
    {
        if (r < h)
        {
            print_branches(branch_len,
                           node_space_len,
                           start_len,
                           nodes_in_this_level,
                           nodes_queue);
        }

        start_len = distance_to_first_arm + 1;
        branch_len = center_of_first_node - start_len - (NODE_W / 2);
        node_space_len = 2 * start_len + (NODE_W / 2);
        print_nodes(branch_len,
                    node_space_len,
                    start_len,
                    nodes_in_this_level,
                    nodes_queue);

        for (int i = 0; i < nodes_in_this_level; i++)
        {
            const BSTNode *curr_node = nodes_queue.front();
            nodes_queue.pop_front();
            if (curr_node && !curr_node->is_empty())
            {
                nodes_queue.push_back(curr_node->left_child());
                nodes_queue.push_back(curr_node->right_child());
            }
            else
            {
                nodes_queue.push_back(nullptr);
                nodes_queue.push_back(nullptr);
            }
        }
        nodes_in_this_level *= 2;

        center_of_first_node /= 2;
        distance_to_first_arm /= 2;
    }
    print_branches(branch_len,
                   node_space_len,
                   start_len,
                   nodes_in_this_level,
                   nodes_queue);
    print_leaves(indent_space, leaf_space, nodes_in_this_level, nodes_queue);
}

std::string BSTNodePrinter::decorator_string(const BSTNode *node)
{
    std::string dec = "";
    if (node && node->mHeight >= 0)
    {
        if (node->mColor == BSTNode::Color::RED)
        {
            if (node->mCount > 1)
            {
                dec = "R";
            }
            else
            {
                dec = "r";
            }
        }
        else
        {
            if (node->mCount > 1)
            {
                dec = "*";
            }
        }
    }
    return dec;
}

std::string BSTNodePrinter::value_string(const BSTNode *node)
{
    std::string value = "";
    if (node && node->mHeight >= 0)
    {
        value = std::to_string(node->mData);
    }
    return value;
}

std::string BSTNodePrinter::node_string(const BSTNode *node)
{
    // This function is implemented for you

    return value_string(node) + decorator_string(node);
}

std::string BSTNodePrinter::centered(const BSTNode *node, int width)
{
    string label = node_string(node);
    char pre_fill = (node && node->has_child(BSTNode::Direction::LEFT)) ? '_' : ' ';
    char post_fill = (node && node->has_child(BSTNode::Direction::RIGHT)) ? '_' : ' ';

    int lpad = (width - label.length()) / 2;
    int rpad = width - label.length() - lpad;
    stringstream s;
    s << setfill(pre_fill) << setw(lpad) << "" << label << setfill(post_fill) << setw(rpad) << "";
    return s.str();
}

void BSTNodePrinter::print_branches(int branch_len,
                                    int node_space_len,
                                    int start_len,
                                    int nodes_in_this_level,
                                    const std::deque<const BSTNode *> &nodes_queue)
{
    deque<const BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level / 2; i++)
    {
        bool has_left = (*iter) && !(*iter)->is_empty();
        iter++;
        bool has_right = (*iter) && !(*iter)->is_empty();
        iter++;
        out << setw((i == 0) ? (start_len - 1) : (node_space_len - 2))
            << "" << ((has_left) ? "/" : " ");
        out << setw(2 * branch_len + NODE_W) << "" << ((has_right) ? "\\" : " ");
    }
    out << endl;
}

void BSTNodePrinter::print_nodes(int branch_len,
                                 int node_space_len,
                                 int start_len,
                                 int nodes_in_this_level,
                                 const std::deque<const BSTNode *> &nodes_queue)
{
    deque<const BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        const BSTNode *node = *iter;

        bool has_left = node && node->has_child(BSTNode::Direction::LEFT);
        bool has_right = node && node->has_child(BSTNode::Direction::RIGHT);
        out << setw(((i == 0) ? start_len : (node_space_len)))
            << "";
        out << setfill(has_left ? '_' : ' ')
            << setw(branch_len) << ""
            << setw(NODE_W) << centered(node, out.width());
        out << setfill(has_right ? '_' : ' ')
            << setw(branch_len) << "" << setfill(' ');
    }
    out << endl;
}

void BSTNodePrinter::print_leaves(int indent_space,
                                  int leaf_space,
                                  int nodes_in_this_level,
                                  const std::deque<const BSTNode *> &nodes_queue)
{
    deque<const BSTNode *>::const_iterator iter = nodes_queue.begin();
    for (int i = 0; i < nodes_in_this_level; i++, iter++)
    {
        out << setw((i == 0) ? (indent_space) : (leaf_space)) << "" << setw(NODE_W) << centered((*iter), out.width());
    }
    out << endl;
}
