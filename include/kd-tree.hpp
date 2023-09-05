#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include "./kd-node.hpp"

class KD_Tree
{
public:
    // CONSTRUCTOR
    KD_Tree() {
        this->root = nullptr;
    }

    KD_Tree(std::vector<KD_Point> pts)
    {
        this->root = this->build(pts, 0);
    };

    // PUBLIC METHODS
    void addPoint(KD_Point pt);
    bool deletePoint(KD_Point pt);
    bool findPoint(KD_Point pt);
    void print();
    std::vector<KD_Point> pointsInRange(KD_Point pt, int range);

    // PUBLIC ATTRIBUTES
    KD_Node *root;

private:
    KD_Node* build (std::vector<KD_Point> pts, int level);

};

#endif