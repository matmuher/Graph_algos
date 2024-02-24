#include "Point.hpp"

Point::Point(int _x, int _y) : x{_x}, y{_y} {}
Point::Point(int index) : Point(index, index) {}
Point::Point() : Point(0) {}

Point operator+(const Point& lhs, const Point& rhs)
{
	return Point{lhs.x + rhs.x, lhs.y + rhs.y};
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<< (std::ostream& cout, const Point& point)
{
	cout << '[' << point.x << ", " << point.y << ']';

	return cout;
}

bool lessThan(const Point& lhs, const Point& rhs)
{
	return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}

bool lessEqualThan(const Point& lhs, const Point& rhs)
{
	return (lhs.x <= rhs.x) && (lhs.y <= rhs.y);
}

const Point Ones{1, 1};
const Point Zeros{0, 0};
const std::array<Point, 4> shifts{Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}};
