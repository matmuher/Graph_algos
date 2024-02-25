#include "AStar.hpp"
#include "Point.hpp"
#include "Grid.hpp"

#include <map>

const Point AStar::PathPoison{-1, -1};
const Point Ones{1, 1};
const Point Zeros{0, 0};
const std::map<MoveDirection, Point> shifts{
											{MoveDirection::Up,    Point{0,  1}},
											{MoveDirection::Down,  Point{0, -1}},
											{MoveDirection::Left, Point{1,  0}},
											{MoveDirection::Right,  Point{-1, 0}}
											};
