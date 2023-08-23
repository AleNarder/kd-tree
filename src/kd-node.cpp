#include "kd-node.hpp"

void KD_Node::print () {
    std::cout << "( ";
    for (float c : this->point) {
        std::cout << c << " ";
    }
    std::cout << ")";
}