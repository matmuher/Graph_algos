#include "AStar.hpp"
#include "Point.hpp"
#include "Grid.hpp"

#include <map>

const Point AStar::PathPoison{-1, -1};
const Point Ones{1, 1};
const Point Zeros{0, 0};
