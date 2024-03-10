#pragma once

#include <map>
#include <iostream>

namespace GA
{

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

int distanceManhattan(const Point& lhs, const Point& rhs);

int distanceEuclidian(const Point& lhs, const Point& rhs);

struct WeightedPoint
{
	Point point;
	int weight;

	// WeightedPoint() : point{}, weight{}
	// {}

	// WeightedPoint(const Point& _point, int _weight);

	// WeightedPoint(const WeightedPoint& other)
	// :
	// 	point{other.point},
	// 	weight{other.weight}
	// {}

	// WeightedPoint& operator= (const WeightedPoint& other)
	// {
	// 	point = other.point;
	// 	weight = other.weight;

	// 	return *this;
	// }
};

bool operator==(const WeightedPoint& lhs, const WeightedPoint& rhs);

bool operator<(const WeightedPoint& lhs, const WeightedPoint& rhs);


extern const Point Ones;
extern const Point Zeros;
};
