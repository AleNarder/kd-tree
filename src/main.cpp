#include "kd-tree.hpp"

int main (int argc, char** argv) {
    KD_Tree* tree = new KD_Tree(2);

    std::vector<KD_Point> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};

    tree->findPoint({2,2});

    // Insert points into the k-d tree
    for (const auto& point : points) {
        tree->addPoint(point);
    }

    return 0;
}  