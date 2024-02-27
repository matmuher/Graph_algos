#pragma once

#include "Grid.hpp"
#include "Point.hpp"

#include <iostream>

std::ostream& operator<< (std::ostream& cout, AlgoState algoState);

std::ostream& operator<< (std::ostream& cout, Tile tileType);

void printPath(	const Grid<MoveDirection>& directions,
				const Point& start,
				const Point& finish);

template<class ValueType>
void print(const Grid<ValueType>& graph);
