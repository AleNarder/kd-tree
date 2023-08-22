#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include "./kd-node.hpp"

class KD_Tree
{
public:
    // CONSTRUCTOR
    KD_Tree(int dim = 2) : dim(dim)
    {
        this->root = nullptr;
    };

    KD_Tree(KD_Point pt)
    {
        this->root = new KD_Node(pt);
    };

    // PUBLIC METHODS
    void addPoint(KD_Point pt);
    bool deletePoint(KD_Point pt);
    bool findPoint(KD_Point pt);
    std::vector<KD_Point> pointsInRange(KD_Point pt, int range);

    // PUBLIC ATTRIBUTES
    int dim;
    KD_Node *root;

};

#endif