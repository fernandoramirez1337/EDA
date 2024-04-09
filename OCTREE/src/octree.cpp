#include "../include/octree.hpp"

namespace EDA {
    double max(double a, double b) {
        return (a > b) ? a : b;
    }

    Octree::Octree(const Point& bottomLeft, double h) 
        : bottomLeft(bottomLeft), h(h), data(nullptr), nPoints(0) {
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }

    int Octree::get_octant_containing_point(const Point& point) const {
        int oct = 0;
        if (point.x >= bottomLeft.x + h / 2) oct |= 4;
        if (point.y >= bottomLeft.y + h / 2) oct |= 2;
        if (point.z >= bottomLeft.z + h / 2) oct |= 1;
        return oct;
    }

    bool Octree::is_leaf_node() const {
        return children[0] == nullptr;
    }

    void Octree::insert(const Point& point) {
        if (is_leaf_node()) {
            if (data == nullptr) {
                data = new Point(point);
                return;
            }
            Point* oldPoint = data;
            data = nullptr;

            for (int i = 0; i < 8; ++i) {
                Point newBottomLeft = bottomLeft;
                newBottomLeft.x += (i & 4) ? h / 2 : 0;
                newBottomLeft.y += (i & 2) ? h / 2 : 0;
                newBottomLeft.z += (i & 1) ? h / 2 : 0;
                children[i] = new Octree(newBottomLeft, h / 2);
            }
            children[get_octant_containing_point(*oldPoint)]->insert(*oldPoint);
            children[get_octant_containing_point(point)]->insert(point);
        } else {
            int octant = get_octant_containing_point(point);
            children[octant]->insert(point);
        }
    }

    bool Octree::exist(const Point& point) {
        if (is_leaf_node()) {
            return (data != nullptr && *data == point);
        }
        int octant = get_octant_containing_point(point);
        return children[octant]->exist(point);
    }

    Point Octree::find_closest(const Point& targetPoint, int radius) {
        Point closestPoint(-1, -1, -1);
        double minDistanceSquared = std::numeric_limits<double>::infinity();
        search_closest_point(targetPoint, radius, closestPoint, minDistanceSquared);
        return closestPoint;
    }

    void Octree::search_closest_point(const Point& targetPoint, int radius, Point& closestPoint, double& minDistanceSquared) {
        if (is_leaf_node()) {
            if (data != nullptr) {
                double distanceSquared = calculate_distance_squared(targetPoint, *data);
                if (distanceSquared <= radius * radius && distanceSquared < minDistanceSquared) {
                    closestPoint = *data;
                    minDistanceSquared = distanceSquared;
                }
            }
        } else {
            for (int i = 0; i < 8; ++i) {
                double distanceToBoundingBoxSquared = calculate_distance_to_bounding_box_squared(targetPoint, children[i]->bottomLeft, children[i]->h);
                if (distanceToBoundingBoxSquared <= radius * radius) {
                    children[i]->search_closest_point(targetPoint, radius, closestPoint, minDistanceSquared);
                }
            }
        }
    }

    double Octree::calculate_distance_squared(const Point& p1, const Point& p2) const {
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;
        int dz = p2.z - p1.z;
        return dx * dx + dy * dy + dz * dz;
    }

    double Octree::calculate_distance_to_bounding_box_squared(const Point& point, const Point& bottomLeft, double h) const {
        double dx = max(0.0, max(bottomLeft.x - point.x, point.x - (bottomLeft.x + h)));
        double dy = max(0.0, max(bottomLeft.y - point.y, point.y - (bottomLeft.y + h)));
        double dz = max(0.0, max(bottomLeft.z - point.z, point.z - (bottomLeft.z + h)));
        return dx * dx + dy * dy + dz * dz;
    }
}
