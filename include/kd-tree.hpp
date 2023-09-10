#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include "./kd-node.hpp"

class KdTree
{
public:
    // CONSTRUCTOR
    KdTree()
    {
        this->root = nullptr;
    }

    KdTree(std::vector<KdPoint> pts)
    {
        this->root = this->build(pts, 0);
    };

    // PUBLIC METHODS
    bool deletePoint(KdPoint pt);
    void addPoint(KdPoint pt);

    KdNode* findNode(KdPoint pt);
    KdPoint nearestNeighbourSearch(KdPoint pt);

    void print();

    

    // PUBLIC ATTRIBUTES
    KdNode *root;

private:
    KdNode *build(std::vector<KdPoint> pts, int level);

};

#endif