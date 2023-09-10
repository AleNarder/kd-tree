#include "kd-node.hpp"

void KdNode::print () {
    std::cout << "( ";
    for (float c : this->point) {
        std::cout << c << " ";
    }
    std::cout << ")";
}