#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include "./kd-node.hpp"


class KdTree
{
public:
    // CONSTRUCTOR
    KdTree(int dim)
    {
        this->dim = dim;
        this->root = nullptr;
    }

    KdTree(std::vector<KdPoint> pts, int dim)
    {
        this->dim = dim;
        this->root = this->build(pts, 0, nullptr);
    };

    // PUBLIC METHODS
    bool deletePoint(KdPoint pt);
    bool addPoint(KdPoint pt);

    KdNode* findNode(KdPoint pt);
    KdPoint nearestNeighbourSearch(KdPoint pt);

    void print();

    

    // PUBLIC ATTRIBUTES
    KdNode *root;

private:
    KdNode *build(std::vector<KdPoint> pts, int level,  KdNode* parent);
    int dim;
};

#endif