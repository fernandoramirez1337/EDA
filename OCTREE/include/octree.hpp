#ifndef OCTREE_H
#define OCTREE_H

#include <limits> // Include the <limits> header for numeric_limits

namespace EDA {
    // Represents a point in 3D space with integer coordinates x, y, and z.
    struct Point {
        int x;
        int y;
        int z;
        
        Point(int a, int b, int c) : x(a), y(b), z(c) {}
        Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    class Octree {
    private:
        // Array of pointers to child octrees, representing the eight octants of the current octree node.
        Octree *children[8];
        // Pointer to the point stored in the leaf node (nullptr if not a leaf node).
        Point *data;
        // Bottom-left corner of the bounding cube.
        Point bottomLeft;
        // Width/height/depth of the bounding cube.
        double h;
        // Number of inserted points (not used in code).
        int nPoints;

        // Determines the octant containing a given point.
        int get_octant_containing_point(const Point& point) const;
        // Checks if the current node is a leaf node (i.e., it has no children).
        bool is_leaf_node() const;
        // Recursively searches for the closest point to a target point within a specified radius.
        void search_closest_point(const Point&, int, Point&, double&);
        // Calculates the squared Euclidean distance between two points.
        double calculate_distance_squared(const Point&, const Point&) const;
        // Calculates the squared distance from a point to the bounding box of an octree node.
        double calculate_distance_to_bounding_box_squared(const Point&, const Point&, double) const;

    public:
        // Constructor to initialize the octree with a given bottom-left corner and size.
        Octree(const Point&, double);
        // Checks if a point exists in the octree.
        bool exist(const Point&);
        // Inserts a point into the octree.
        void insert(const Point&);
        // Finds the closest point to a target point within a specified radius
        Point find_closest(const Point&, int radius);
    };
}

#endif
