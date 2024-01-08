#include "point.hpp"

Point Point::binary_search(const vector<Point> &points, const int id, int left, int right) {
    if (left > right) {
        return Point();
    }

    int middle = (left + right) / 2;
    if (points[middle].id == id) {
        return points[middle];
    }

    if (points[middle].id > id) {
        return binary_search(points, id, left, middle - 1);
    }

    return binary_search(points, id, middle + 1, right);
}

Point::Point() : id(0), x(0), y(0) {
    this->id = 0;
}

Point::Point(float x, float y) : id(0), x(x), y(y) {
    this->id = 0;
}

Point::Point(int id, float x, float y) : id(id), x(x), y(y) {
}

float Point::get_x() const {
    return this->x;
}

float Point::get_y() const {
    return this->y;
}

int Point::get_id() const {
    return this->id;
}

void Point::set_x(float x) {
    this->x = x;
}

void Point::set_y(float y) {
    this->y = y;
}

float Point::get_distance(const Point& other) const {
    float dx = this->x - other.x;
    float dy = this->y - other.y;
    return sqrt(dx * dx + dy * dy);
}

bool Point::is_in_circle(const Point &center, float radius) const {
    return this->get_distance(center) <= radius;
}

Point Point::find_by_id(const vector<Point> &points, const int id) {
    return binary_search(points, id, 0, points.size() - 1);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Point &point) {
    is >> point.id >> point.x >> point.y;
    return is;
}

bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Point &lhs, const Point &rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator>(const Point &lhs, const Point &rhs) {
    return rhs < lhs;
}
