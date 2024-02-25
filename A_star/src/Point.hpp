#pragma once

#include <array>
#include <iostream>

struct Point
{
	int x;
	int y;

	Point(int _x, int _y);
	Point(int index);
	Point();
};

Point operator+(const Point& lhs, const Point& rhs);

Point operator-(const Point& lhs, const Point& rhs);

bool operator==(const Point& lhs, const Point& rhs);

bool operator!=(const Point& lhs, const Point& rhs);

std::ostream& operator<< (std::ostream& cout, const Point& point);

bool lessThan(const Point& lhs, const Point& rhs);

bool lessEqualThan(const Point& lhs, const Point& rhs);

int dot(const Point& lhs, const Point& rhs);

extern const Point Ones;
extern const Point Zeros;
extern const std::array<Point, 4> shifts;
