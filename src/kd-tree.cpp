#include "kd-tree.hpp"

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

    if (pt[axis] < root->point[axis])
    {
        root->left = addPointRec(root->left, pt, level + 1);
    }
    else
    {
        root->right = addPointRec(root->right, pt, level + 1);
    }

    return root;
}

void KD_Tree::addPoint(KD_Point pt)
{
    addPointRec(this->root, pt, 0);
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
