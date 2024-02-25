#pragma once

#include "Grid.hpp"

#include <iostream>

std::ostream& operator<< (std::ostream& cout, Results results);

std::ostream& operator<< (std::ostream& cout, AlgoState algoState);

std::ostream& operator<< (std::ostream& cout, Tile tileType);

template<class ValueType>
void print(const Grid<ValueType>& graph);
