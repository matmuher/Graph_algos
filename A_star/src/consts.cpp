#include "AStar.hpp"
#include "Point.hpp"

#include <array>

const Point AStar::PathPoison{-1, -1};
const Point Ones{1, 1};
const Point Zeros{0, 0};
const std::array<Point, 4> shifts{Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}};
