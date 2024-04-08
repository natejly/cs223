#include "BSTNodeChecker.h"

bool BSTNodeChecker::is_bst(const BSTNode *node)
{
    bool ans = !node || node->is_empty();
    if (!ans)
    {
        bool lvalid = true, rvalid = true;
        if (!node->mLeft->is_empty())
        {
            lvalid = node->mLeft->mData < node->mData &&
                     is_bst(node->mLeft);
        }
        if (!node->mRight->is_empty())
        {
            rvalid = node->mRight->mData > node->mData &&
                     is_bst(node->mRight);
        }
        ans = lvalid && rvalid;
    }
    return ans;
    // return (!node || node->is_empty()) ||
    //        ((node->mLeft->is_empty() ||
    //          ((node->mLeft->mData < node->mData) &&
    //           is_bst(node->mLeft))) &&
    //         (node->mRight->is_empty() ||
    //          ((node->mRight->mData > node->mData) &&
    //           is_bst(node->mRight))));
}
bool BSTNodeChecker::is_avlt(const BSTNode *node)
{
    int diff = (node && !node->is_empty())
                   ? node->mRight->mHeight - node->mLeft->mHeight
                   : 0;
    // int diff = 0;
    // if (node && !node->is_empty())
    // {
    //     diff = node->mLeft->mHeight - node->mRight->mHeight;
    // }
    return is_bst(node) && (-1 <= diff && diff <= 1);
}

bool BSTNodeChecker::is_rbt(const BSTNode *node)
{
    return is_bst(node) && is_blackheight_balanced(node) && has_no_rrvs(node);
}

int BSTNodeChecker::blackheight(const BSTNode *node)
{
    int ans = 0;
    if (node && !node->is_empty())
    {
        int lbh = blackheight(node->mLeft);
        int rbh = blackheight(node->mRight);
        bool balanced = lbh >= 0 && rbh >= 0 && (lbh == rbh);
        ans = balanced
                  ? (lbh + (node->mColor == BSTNode::Color::BLACK))
                  : -1;
    }
    return ans;
}

bool BSTNodeChecker::is_blackheight_balanced(const BSTNode *node)
{
    return blackheight(node) >= 0;
}

bool BSTNodeChecker::has_no_rrvs(const BSTNode *node)
{
    bool no_rrvs = true;
    if (node && !node->is_empty())
    {
        if (node->mColor == BSTNode::Color::RED)
        {
            no_rrvs = ((node->mLeft->mColor == BSTNode::Color::BLACK) &&
                       (node->mRight->mColor == BSTNode::Color::BLACK));
        }
        no_rrvs &= (has_no_rrvs(node->mLeft) &&
                    has_no_rrvs(node->mRight));
    }
    return no_rrvs;
    // return (!node || node->is_empty()) ||
    //        ((node->color() == BSTNode::Color::BLACK) ||
    //         ((node->color() == BSTNode::Color::RED) &&
    //          (node->mLeft->color() == BSTNode::Color::BLACK) &&
    //          (node->mRight->color() == BSTNode::Color::BLACK))) &&
    //            (has_no_rrvs(node->mLeft) &&
    //             has_no_rrvs(node->mRight));
}
