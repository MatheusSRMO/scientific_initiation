#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/**
 * @brief Represents a point in a 2D space.
 */
class Point {
    private:
        /**
         * @brief The id of the point.
         */
        int id;
        /**
         * @brief The x-coordinate of the point.
         */
        float x;

        /**
         * @brief The y-coordinate of the point.
         */
        float y;

        /**
         * Performs a binary search on a vector of points to find a specific point by its ID.
         *
         * @param points The vector of points to search in.
         * @param id The ID of the point to find.
         * @param left The left index of the search range.
         * @param right The right index of the search range.
         * @return The found point, or a default-constructed point if not found.
         */
        static Point binary_search(const vector<Point>& points, const int id, int left, int right);
    public:
        /**
         * @brief Default constructor for Point.
         */
        Point();


        /**
         * @brief Constructs a Point object with the given x and y coordinates.
         * 
         * @param x The x-coordinate of the point.
         * @param y The y-coordinate of the point.
         */
        Point(float x, float y);


        /**
         * @brief Represents a point in a 2D coordinate system.
         */
        Point(int id, float x, float y);


        /**
         * @brief Gets the x-coordinate of the point.
         * 
         * @return The x-coordinate of the point.
         */
        float get_x() const;


        /**
         * @brief Gets the y-coordinate of the point.
         * 
         * @return The y-coordinate of the point.
         */
        float get_y() const;


        /**
         * @brief Gets the ID of the point.
         * 
         * @return The ID of the point.
         */
        int get_id() const;
 

        /**
         * @brief Sets the x-coordinate of the point.
         * 
         * @param x The new value for the x-coordinate.
         */
        void set_x(float x);


        /**
         * @brief Sets the y-coordinate of the point.
         * 
         * @param y The new value for the y-coordinate.
         */
        void set_y(float y);


        /**
         * Calculates the distance between this point and another point.
         *
         * @param other The other point to calculate the distance to.
         * @return The distance between this point and the other point.
         */
        float get_distance(const Point& other) const;


        /**
         * Checks if the point is inside a circle.
         *
         * @param center The center of the circle.
         * @param radius The radius of the circle.
         * @return True if the point is inside the circle, false otherwise.
         */
        bool is_in_circle(const Point& center, float radius) const;


        /**
         * Finds a Point in the given vector by its ID.
         *
         * @param points The vector of Points to search in.
         * @param id The ID of the Point to find.
         * @return The Point with the specified ID, or a default-constructed Point if not found.
         */
        static Point find_by_id(const vector<Point>& points, const int id);

        void draw(RenderWindow& window, float radius, Color color) const;


        friend std::ostream& operator<<(std::ostream& os, const Point& point);
        friend std::istream& operator>>(std::istream& is, Point& point);
        friend bool operator==(const Point& lhs, const Point& rhs);
        friend bool operator!=(const Point& lhs, const Point& rhs);
        friend bool operator<(const Point& lhs, const Point& rhs);
        friend bool operator>(const Point& lhs, const Point& rhs);
};

#endif // POINT_HPP