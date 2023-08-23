#include "kd-tree.hpp"
#include <iostream>

int main()
{
    KD_Tree *tree = new KD_Tree(2);

    std::vector<KD_Point> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};

    // Insert points into the k-d tree
    for (const auto &point : points)
    {
        tree->addPoint(point);
    }

    tree->print();

    return 0;
}