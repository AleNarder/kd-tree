#ifndef KD_NODE_HPP
#define KD_NODE_HPP

#include "./kd-point.hpp"
#include <iostream>

class KdNode
{
public:
    KdNode *left;
    KdNode *right;
    KdNode *parent;

    int depth;
    KdPoint point;
  
    KdNode(const KdPoint &p) : left(nullptr), right(nullptr), point(p) {
        this->parent = nullptr;
    }

    void print();
};

#endif