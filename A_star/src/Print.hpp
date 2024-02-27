#pragma once

#include "Grid.hpp"
#include "Point.hpp"

#include <iostream>

std::ostream& operator<< (std::ostream& cout, AlgoState algoState);

std::ostream& operator<< (std::ostream& cout, Tile tileType);

std::ostream& operator<< (std::ostream& cout, MoveDirection direction);

template<class ValueType>
void print(const Grid<ValueType>& graph);
