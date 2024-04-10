#ifndef OCTREE_H
#define OCTREE_H

namespace EDA {
    const int MAX_POINTS = 5;

    struct Point {
        int x;
        int y;
        int z;

        Point(int a, int b, int c) : x(a), y(b), z(c) {}
        Point() : x(0), y(0), z(0) {}
        Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    class Octree {
    private:
        Point data[MAX_POINTS];
        Octree* children[8];
        Point bottomLeft;
        double h;
        int nPoints;
        int maxPoints;

        int get_octant_containing_point(const Point& point) const;
        bool is_leaf_node() const;
        void search_closest_point(const Point&, int, Point&, double&);
        double calculate_distance_squared(const Point&, const Point&) const;
        double calculate_distance_to_bounding_box_squared(const Point&, const Point&, double) const;

    public:
        Octree(const Point&, double, int);
        bool exist(const Point&);
        void insert(const Point&);
        Point find_closest(const Point&, int);
    };
}

#endif