#include "kd-tree.hpp"
#include <bits/stdc++.h>
#include "valarray"
#include <queue>

/****************************************************************
 * Build k-d Tree
 */

KD_Node *KD_Tree::build(std::vector<KD_Point> pts, int level)
{

    if ((int)pts.size() == 0)
    {
        return nullptr;
    }

    if (pts.size() == 1)
    {
        return new KD_Node(pts[0]);
    }
    else
    {
        int axis = level > 0 ? (int)pts[0].size() % level : level;
        sort(pts.begin(), pts.end(), [axis](KD_Point pt1, KD_Point pt2) -> bool
             { return pt1[axis] < pt2[axis]; });

        int medianIdx = (int)pts.size() / 2 == 0 ? ((int)pts.size() / 2) - 1 : (((int)pts.size() + 1) / 2) - 1;

        auto median = pts.begin() + medianIdx + 1;
        auto first = pts.begin();
        auto last = pts.end();

        KD_Node *root = new KD_Node(pts[medianIdx]);

        root->left = KD_Tree::build(std::vector<KD_Point>(first, median), level + 1);
        root->right = KD_Tree::build(std::vector<KD_Point>(median + 1, last), level + 1);

        return root;
    }
};

/****************************************************************
 * Find Point
 */

bool findPointRec(KD_Node *root, KD_Point pt, int level)
{

    if (root == nullptr || root->deleted)
        return false;

    if (root->point == pt)
        return true;

    int axis = level % pt.size();

    if (root->point[axis] < pt[axis])
    {
        return findPointRec(root->left, pt, level + 1);
    }
    else
    {
        return findPointRec(root->right, pt, level + 1);
    }
}

bool KD_Tree::findPoint(KD_Point pt)
{
    return findPointRec(this->root, pt, 0);
};

/****************************************************************
 * Add Point
 */

KD_Node *addPointRec(KD_Node *root, KD_Point pt, int level)
{
    if (root == nullptr || root->deleted)
        return new KD_Node(pt);

    int axis = level % pt.size();

    if (root->point[axis] < pt[axis])
    {
        root->left = addPointRec(root->left, pt, level + 1);
    }
    else
    {
        root->right = addPointRec(root->right, pt, level + 1);
    }

    return root;
};

void KD_Tree::addPoint(KD_Point pt)
{
    this->root = addPointRec(this->root, pt, 0);
};

/****************************************************************
 * Delete Point
 */
bool deletePointRec(KD_Node *root, KD_Point pt, int level)
{
    if (root == nullptr || root->deleted)
    {
        return false;
    }

    if (root->point == pt)
    {
        return root->deleted = true;
    }

    int axis = level % pt.size();
    if (root->point[axis] < pt[axis])
    {
        return deletePointRec(root->left, pt, level + 1);
    }
    else
    {
        return deletePointRec(root->right, pt, level + 1);
    }
}

bool KD_Tree::deletePoint(KD_Point pt)
{
    return deletePointRec(this->root, pt, 0);
}

/****************************************************************
 * Points in range
 */

std::vector<KD_Point> pointsInRangeRec(KD_Node *root, KD_Point pt, int range, int level)
{
    std::vector<KD_Point> pts;
    if (root == nullptr || root->deleted)
    {
        return pts;
    }

    int axis = pt.size() % level;

    if (euc_kd_distance(root->point, pt) <= range)
    {
        pts.push_back(root->point);
    }

    if (pt[axis] - range < root->point[axis])
    {
        std::vector<KD_Point> leftResult = pointsInRangeRec(root->left, pt, range, level + 1);
        pts.insert(pts.end(), leftResult.begin(), leftResult.end());
    }
    if (pt[axis] + range > root->point[axis])
    {
        std::vector<KD_Point> rightResult = pointsInRangeRec(root->right, pt, range, level + 1);
        pts.insert(pts.end(), rightResult.begin(), rightResult.end());
    }

    return pts;
}

std::vector<KD_Point> KD_Tree::pointsInRange(KD_Point pt, int range)
{
    return pointsInRangeRec(this->root, pt, range, 0);
};

/****************************************************************
 * Print tree to standard output
 */

void KD_Tree::print()
{

    KD_Node *root = this->root;

    if (root == nullptr)
        return;

    std::queue<KD_Node *> nodeQ;
    std::queue<int> levelQ;
    std::queue<int> offsetQ;

    nodeQ.push(root);
    levelQ.push(0);

    while (!nodeQ.empty())
    {
        KD_Node *current = nodeQ.front();
        int currentLevel = levelQ.front();

        nodeQ.pop();
        levelQ.pop();

        current->print();

        if (levelQ.size() == 0 || currentLevel < levelQ.front())
        {
            std::cout << std::endl;
        }

        if (current->left && !current->left->deleted)
        {
            nodeQ.push(current->left);
            levelQ.push(currentLevel + 1);
        }

        if (current->right && !current->right->deleted)
        {
            nodeQ.push(current->right);
            levelQ.push(currentLevel + 1);
        }
    }
};