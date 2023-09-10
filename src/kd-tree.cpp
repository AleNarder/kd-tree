#include "kd-tree.hpp"
#include <bits/stdc++.h>
#include "valarray"
#include <queue>
#include <iostream>

/****************************************************************
 * Build k-d Tree
 */

KdNode *KdTree::build(std::vector<KdPoint> pts, int depth)
{

    if (pts.size() == 0)
    {
        return nullptr;
    }

    if (pts.size() == 1)
    {
        return new KdNode(pts[0]);
    }
    else
    {
        int axis = depth % pts[0].size();
        sort(pts.begin(), pts.end(), [axis](KdPoint pt1, KdPoint pt2) -> bool
             { return pt1[axis] < pt2[axis]; });

        int medianIdx = pts.size() / 2 == 0 ? (pts.size() / 2) - 1 : ((pts.size() + 1) / 2) - 1;

        auto median = pts.begin() + medianIdx;
        auto first = pts.begin();
        auto last = pts.end();

        KdNode *root = new KdNode(pts[medianIdx]);

        root->left = KdTree::build(std::vector<KdPoint>(first, median), depth + 1);

        if (root->left)
        {
            root->left->parent = root;
            root->left->depth = depth;
        }

        root->right = KdTree::build(std::vector<KdPoint>(median + 1, last), depth + 1);

        if (root->right)
        {
            root->right->parent = root;
            root->right->depth = depth;
        }

        return root;
    }
};

/****************************************************************
 * Find Point
 */

KdNode *findNodeRec(KdNode *root, KdPoint pt, int depth)
{

    if (root == nullptr)
        return nullptr;

    if (root->point == pt)
        return root;

    int axis = depth % pt.size();

    if (root->point[axis] < pt[axis])
    {
        return findNodeRec(root->left, pt, depth + 1);
    }
    else
    {
        return findNodeRec(root->right, pt, depth + 1);
    }
}

KdNode *KdTree::findNode(KdPoint pt)
{
    return findNodeRec(this->root, pt, 0);
};

/****************************************************************
 * Add Point
 */

KdNode *addPointRec(KdNode *root, KdPoint pt, int depth)
{
    if (root == nullptr)
        return new KdNode(pt);

    int axis = depth % pt.size();

    if (root->point[axis] < pt[axis])
    {
        root->left = addPointRec(root->left, pt, depth + 1);
        root->left->parent = root;
    }
    else
    {
        root->right = addPointRec(root->right, pt, depth + 1);
        root->right->parent = root;
    }

    return root;
};

void KdTree::addPoint(KdPoint pt)
{
    this->root = addPointRec(this->root, pt, 0);
};

/****************************************************************
 * Delete Point
 */

void subTree(KdNode *root, std::vector<KdPoint> vec)
{
    if (root != nullptr)
    {
        vec.push_back(root->point);
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

        subTree(nodeToDelete->left, pts);
        subTree(nodeToDelete->right, pts);

        // Keep depth to guarantee the invariant is not broken
        KdNode *newSubTree = this->build(pts, nodeToDelete->depth);

        // Replace the node with the subtree
        if (nodeToDelete->parent->left == nodeToDelete)
        {
            nodeToDelete->parent->left = newSubTree;
        }
        else
        {
            nodeToDelete->parent->right = newSubTree;
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

void nearestNeighbourSearchRec(KdNode *current_node, KdPoint search_pt, double &minDist, KdPoint &minPt, int depth)
{

    double distance = euc_kd_distance(current_node->point, search_pt);

    int axis = depth % current_node->point.size();

    // Check if the hypersphere with radius minDist intersects the splitting hyperplane
    // Since the hyperplanes are all axis-aligned this is implemented as a simple comparison to see
    // whether the distance between the splitting coordinate of the search point and current node is lesser
    // than the distance (overall coordinates) from the search point to the current best
    if (search_pt[axis] + minDist < current_node->point[axis])
    {
        // It doesn't intersect
        if (current_node->left)
            nearestNeighbourSearchRec(current_node->left, search_pt, minDist, minPt, depth + 1);
        if (search_pt[axis] + minDist >= current_node->point[axis])
            if (current_node->right)
                nearestNeighbourSearchRec(current_node->right, search_pt, minDist, minPt, depth + 1);
    }
    else
    {
        // It intersects
        if (current_node->right)
            nearestNeighbourSearchRec(current_node->right, search_pt, minDist, minPt, depth + 1);
        if (search_pt[axis] - minDist <= current_node->point[axis])
            if (current_node->left)
                nearestNeighbourSearchRec(current_node->left, search_pt, minDist, minPt, depth + 1);
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
    nearestNeighbourSearchRec(this->root, pt, max, minPt, 0);
    return minPt;
};

/****************************************************************
 * Print tree to standard output
 */

void KdTree::print()
{

    KdNode *root = this->root;

    if (root == nullptr)
        return;

    std::queue<KdNode *> nodeQ;
    std::queue<int> depthQ;
    std::queue<int> offsetQ;

    nodeQ.push(root);
    depthQ.push(0);

    while (!nodeQ.empty())
    {
        KdNode *current = nodeQ.front();
        int currentdepth = depthQ.front();

        nodeQ.pop();
        depthQ.pop();

        current->print();

        if (depthQ.size() == 0 || currentdepth < depthQ.front())
        {
            std::cout << std::endl;
        }

        if (current->left)
        {
            nodeQ.push(current->left);
            depthQ.push(currentdepth + 1);
        }

        if (current->right)
        {
            nodeQ.push(current->right);
            depthQ.push(currentdepth + 1);
        }
    }
};