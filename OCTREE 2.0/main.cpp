#include "include/octree.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

struct preprocessing{
    int h;
    EDA::Point bottom_left;
};

preprocessing calculate_coords(const std::vector<EDA::Point>& points) {
    int x_min = std::numeric_limits<int>::max();
    int x_max = std::numeric_limits<int>::min();
    int y_min = std::numeric_limits<int>::max();
    int y_max = std::numeric_limits<int>::min();
    int z_min = std::numeric_limits<int>::max();
    int z_max = std::numeric_limits<int>::min();

    for (const auto& point : points) {
        x_min = std::min(x_min, point.x);
        x_max = std::max(x_max, point.x);
        y_min = std::min(y_min, point.y);
        y_max = std::max(y_max, point.y);
        z_min = std::min(z_min, point.z);
        z_max = std::max(z_max, point.z);
    }
    EDA::Point bottom_left(x_min,y_min,z_min);
    int h = std::max({x_max - x_min, y_max - y_min, z_max - z_min});
    preprocessing result;
    result.bottom_left = bottom_left;
    result.h = h;
    std::cout << "h:" << h << std::endl;
    std::cout << "bottomLeft: ( " << x_min << ", " << y_min << ", " << z_min << ")" << std::endl;
    return result;
}

std::vector<EDA::Point> readPointsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::vector<EDA::Point> points;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int x, y, z;

        if (std::getline(ss, token, ','))
            x = std::stoi(token);
        if (std::getline(ss, token, ','))
            y = std::stoi(token);
        if (std::getline(ss, token, ','))
            z = std::stoi(token);

        EDA::Point point(x, y, z);
        points.push_back(point);
    }

    file.close();
    return points;
}

int main() {
    const std::string filename = "points.csv"; 
    std::vector<EDA::Point> points = readPointsFromFile(filename);

    preprocessing tmp = calculate_coords(points);

    int maxPointsPerLeaf;
    std::cout << "Enter the maximum number of points per leaf node: ";
    std::cin >> maxPointsPerLeaf;

    EDA::Point targetPoint;
    std::cout << "Enter the target point (x, y, z): ";
    std::cin >> targetPoint.x >> targetPoint.y >> targetPoint.z;

    int searchRadius;
    std::cout << "Enter the search radius: ";
    std::cin >> searchRadius;

    EDA::Octree octree(tmp.bottom_left, tmp.h, maxPointsPerLeaf);

    for (const EDA::Point& point : points) {
        octree.insert(point);
    }

    EDA::Point closestPoint = octree.find_closest(targetPoint, searchRadius);

    std::cout << "Closest point to (" << targetPoint.x << ", " << targetPoint.y << ", " << targetPoint.z << ") within radius " << searchRadius << " is: (" << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << ")" << std::endl;

    return 0;
}
