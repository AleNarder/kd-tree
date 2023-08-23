#ifndef KD_NODE_HPP
#define KD_NODE_HPP

#include "./kd-point.hpp"
#include <iostream>

class KD_Node
{
public:
    KD_Node *left;
    KD_Node *right;
    KD_Point point;
    bool deleted;

    KD_Node(const KD_Point &p) : left(nullptr), right(nullptr), point(p) {
        this->deleted = false;
    }

    void print();
};

#endif