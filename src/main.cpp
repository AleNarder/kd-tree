#include "kd-tree.hpp"
#include <iostream>

int main()
{

    std::vector<KD_Point> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
    KD_Tree *tree = new KD_Tree(points);

    tree->print();

    return 0;
}