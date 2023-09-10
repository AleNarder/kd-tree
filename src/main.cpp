#include "kd-tree.hpp"
#include <iostream>

int main()
{

    std::vector<KdPoint> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
    KdTree *tree = new KdTree(points);
    auto pt1 = tree->nearestNeighbourSearch({3, 3});

    return 0;
}