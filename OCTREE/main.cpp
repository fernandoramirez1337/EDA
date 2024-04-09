#include <iostream>
#include "include/octree.hpp"

int main() {
    // Create an Octree object
    EDA::Octree octree(EDA::Point(0, 0, 0), 1000.0);

    // Test insertion of points
    EDA::Point point1(1, 1, 1);
    EDA::Point point2(2, 2, 2);
    EDA::Point point3(3, 3, 3);

    //octree.insert(point1);
    //octree.insert(point2);

    // Test existence of points
    std::cout << "Point 1 exists: " << std::boolalpha << octree.exist(point1) << std::endl;
    std::cout << "Point 2 exists: " << std::boolalpha << octree.exist(point2) << std::endl;
    std::cout << "Point 3 exists: " << std::boolalpha << octree.exist(point3) << std::endl;

    // Test finding closest point
    EDA::Point targetPoint(0, 0, 0);
    int radius = 100;

    octree.insert(EDA::Point(10, 20, 30));
    octree.insert(EDA::Point(50, 60, 70));
    octree.insert(EDA::Point(80, 90, 100));
    octree.insert(EDA::Point(15, 25, 30));
    octree.insert(EDA::Point(40, 30, 20));
    octree.insert(EDA::Point(70, 50, 40));
    octree.insert(EDA::Point(90, 80, 60));
    octree.insert(EDA::Point(25, 35, 15));
    octree.insert(EDA::Point(30, 40, 70));
    octree.insert(EDA::Point(60, 70, 90));

    EDA::Point closestPoint = octree.find_closest(targetPoint, radius);

    std::cout << "Closest point to target point (" << targetPoint.x << ", " << targetPoint.y << ", " << targetPoint.z << ") within radius " << radius << ": ";
    if (closestPoint.x != -1) {
        std::cout << "(" << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << ")" << std::endl;
    } else {
        std::cout << "None found." << std::endl;
    }

    return 0;
}
