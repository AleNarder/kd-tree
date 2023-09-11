#include "kd-tree.hpp"
#include <iostream>

int main()
{

    std::vector<KdPoint> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
    KdTree *tree = new KdTree(points, 2);

    // TEST FIND NODE
    std::cout << "-------------------------" << std::endl;
    std::cout << "Testing find-node" << std::endl;
    std::cout << (tree->findNode({4, 4}) == nullptr ? "OK" : "KO") << " ";
    std::cout << (tree->findNode({2, 3}) != nullptr ? "OK" : "KO") << " ";
    std::cout << (tree->findNode({-1, -1}) == nullptr ? "OK" : "KO") << " ";
    std::cout << std::endl;

    // TEST NN
    std::cout << "-------------------------" << std::endl;
    std::cout << "Testing nearest-neighbour" << std::endl;
    std::cout << (tree->nearestNeighbourSearch({3, 3}) == std::vector<float>({2, 3}) ? "OK" : "KO") << " ";
    std::cout << (tree->nearestNeighbourSearch({0, 0}) == std::vector<float>({2, 3}) ? "OK" : "KO") << " ";
    std::cout << (tree->nearestNeighbourSearch({2, 3}) == std::vector<float>({2, 3}) ? "OK" : "KO") << " ";
    std::cout << std::endl;

    // TEST ADDPOINT
    std::cout << "-------------------------" << std::endl;
    std::cout << "Testing add-point" << std::endl;
    std::cout << (tree->addPoint({4, 4}) ? "OK" : "KO") << " ";
    std::cout << (tree->addPoint({4, 4}) ? "KO" : "Ok") << " ";
    std::cout << (tree->addPoint({2, 2}) ? "OK" : "KO") << " ";
    std::cout << std::endl;

    // TEST DELETE
    std::cout << "-------------------------" << std::endl;
    std::cout << "Testing delete-point" << std::endl;
    std::cout << (tree->deletePoint({-1, -1}) ? "KO" : "OK") << " ";
    std::cout << (tree->deletePoint(tree->root->point) ? "OK" : "KO") << " ";
    std::cout << std::endl;

    // TEST PRINT
    std::cout << "-------------------------" << std::endl;
    std::cout << "Testing tree-print" << std::endl;
    tree->print();

    return 0;
}