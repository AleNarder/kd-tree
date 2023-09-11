#include "kd-tree.hpp"
#include <bits/stdc++.h>
#include "valarray"
#include <queue>

/****************************************************************
 * Build k-d Tree
 */

KdNode *KdTree::build(std::vector<KdPoint> pts, int depth, KdNode *parent)
{

    if (pts.size() == 0)
    {
        return nullptr;
    }

    if (pts.size() == 1)
    {
        auto root = new KdNode(pts[0]);
        root->depth = depth;
        root->parent = parent;
        return root;
    }
    else
    {
        int axis = depth % this->dim;
        sort(pts.begin(), pts.end(), [axis](KdPoint pt1, KdPoint pt2) -> bool
             { return pt1[axis] < pt2[axis]; });

        int medianIdx = (pts.size() / 2 == 0 ? (pts.size() / 2) : ((pts.size() + 1) / 2)) - 1;

        auto median = pts.begin() + medianIdx;
        auto first = pts.begin();
        auto last = pts.end();

        KdNode *root = new KdNode(pts[medianIdx]);
        root->depth = depth;
        root->parent = parent;

        root->left = KdTree::build(std::vector<KdPoint>(first, median), depth + 1, root);

        if (root->left)
        {
            root->left->parent = root;
            root->left->depth = depth + 1;
        }

        root->right = KdTree::build(std::vector<KdPoint>(median + 1, last), depth + 1, root);

        if (root->right)
        {
            root->right->parent = root;
            root->right->depth = depth + 1;
        }

        return root;
    }
};

/****************************************************************
 * Find the node associated to a point
 */

KdNode *findNodeRec(KdNode *root, KdPoint pt, int depth, int dim)
{

    if (root == nullptr || root->point == pt)
        return root;

    int axis = depth % dim;

    if (root->point[axis] > pt[axis])
    {
        return findNodeRec(root->left, pt, depth + 1, dim);
    }
    else
    {
        return findNodeRec(root->right, pt, depth + 1, dim);
    }
}

KdNode *KdTree::findNode(KdPoint pt)
{

    auto node = findNodeRec(this->root, pt, 0, this->dim);
    return node;
};

/****************************************************************
 * Add Point
 */

KdNode *addPointRec(KdNode *root, KdPoint pt, int depth, int dim)
{
    if (root == nullptr)
    {
        return new KdNode(pt);
    }
    else
    {
        int axis = depth % dim;

        if (root->point[axis] > pt[axis])
        {
            root->left = addPointRec(root->left, pt, depth + 1, dim);
            root->left->parent = root;
        }
        else
        {
            root->right = addPointRec(root->right, pt, depth + 1, dim);
            root->right->parent = root;
        }

        return root;
    }
};

bool KdTree::addPoint(KdPoint pt)
{

    if (this->findNode(pt) != nullptr)
    {
        return false;
    }
    this->root = addPointRec(this->root, pt, 0, this->dim);
    return true;
};

/****************************************************************
 * Delete Point
 */

void subTree(KdNode *root, std::vector<KdPoint> *vec)
{
    if (root != nullptr)
    {
        vec->push_back(root->point);
        subTree(root->left, vec);
        subTree(root->right, vec);
    }
}

bool KdTree::deletePoint(KdPoint pt)
{
    // Locate the node to delete
    KdNode *nodeToDelete = findNode(pt);
    if (nodeToDelete != nullptr)
    {

        // List the points stored in the subtree
        std::vector<KdPoint> pts;

        subTree(nodeToDelete->left, &pts);
        subTree(nodeToDelete->right, &pts);

        // Keep depth to guarantee the invariant is not broken
        KdNode *newSubTree = this->build(pts, nodeToDelete->depth, nodeToDelete->parent);

        // Replace the node with the subtree

        if (nodeToDelete->parent != nullptr)
        {
            newSubTree->parent = nodeToDelete->parent;
            if (nodeToDelete->parent->left == nodeToDelete)
            {
                nodeToDelete->parent->left = newSubTree;
            }
            else
            {
                nodeToDelete->parent->right = newSubTree;
            }
        }
        else
        {
            this->root = newSubTree;
        }
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************
 * NearestNeighbour search for a given point
 */

void nearestNeighbourSearchRec(KdNode *current_node, KdPoint search_pt, double &minDist, KdPoint &minPt, int depth, int dim)
{

    double distance = euc_kd_distance(current_node->point, search_pt);

    int axis = depth % dim;

    // Check if the hypersphere with radius minDist intersects the splitting hyperplane
    // Since the hyperplanes are all axis-aligned this is implemented as a simple comparison to see
    // whether the distance between the splitting coordinate of the search point and current node is lesser
    // than the distance (overall coordinates) from the search point to the current best
    if (search_pt[axis] + minDist < current_node->point[axis])
    {
        // It doesn't intersect
        if (current_node->left)
            nearestNeighbourSearchRec(current_node->left, search_pt, minDist, minPt, depth + 1, dim);
        if (search_pt[axis] + minDist >= current_node->point[axis])
            if (current_node->right)
                nearestNeighbourSearchRec(current_node->right, search_pt, minDist, minPt, depth + 1, dim);
    }
    else
    {
        // It intersects
        if (current_node->right)
            nearestNeighbourSearchRec(current_node->right, search_pt, minDist, minPt, depth + 1, dim);
        if (search_pt[axis] - minDist <= current_node->point[axis])
            if (current_node->left)
                nearestNeighbourSearchRec(current_node->left, search_pt, minDist, minPt, depth + 1, dim);
    }

    if (distance < minDist)
    {
        minDist = distance;
        minPt = current_node->point;
    }
};

KdPoint KdTree::nearestNeighbourSearch(KdPoint pt)
{
    double max = std::numeric_limits<double>::max();
    KdPoint minPt = this->root->point;
    nearestNeighbourSearchRec(this->root, pt, max, minPt, 0, this->dim);
    return minPt;
};

/****************************************************************
 * Print tree to standard output
 * https://stackoverflow.com/a/75125896
 */

void printRec(const std::string &prefix, KdNode *node, bool isLeft, bool isRoot)
{
    if (node == nullptr)
        return;

    if (isRoot)
    {
        std::cout << "─────";
    }
    else
    {
        std::cout << prefix << (isLeft ? "L├───" : "R└───");
    }
    node->print();
    std::cout << std::endl;

    printRec(prefix + (isLeft ? " │   " : "    "),
             node->left, true, false);
    printRec(prefix + (isLeft ? " │   " : "    "),
             node->right, false, false);
}

void KdTree::print()
{
    std::cout << std::endl;
    printRec("", this->root, false, true);
    std::cout << std::endl;
};