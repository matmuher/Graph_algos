#include "Print.hpp"
#include "Point.hpp"

#define PRINT_AS(enumVal, sym) 		\
			case enumVal:			\
				cout << sym;		\
				break;				\

std::ostream& operator<< (std::ostream& cout, Tile tileType)
{
	using enum Tile;

	switch(tileType)
	{
		PRINT_AS(Obstacle, 'X')
		PRINT_AS(No, '-')
	}

	return cout;
}


std::ostream& operator<< (std::ostream& cout, AlgoState algoState)
{
	using enum AlgoState;

	switch(algoState)
	{
		PRINT_AS(Checked, '@')
		PRINT_AS(InProgress, '*')
		PRINT_AS(No, '-')
	}

	return cout;
}

std::ostream& operator<< (std::ostream& cout, MoveDirection direction)
{
	using enum MoveDirection;

	switch(direction)
	{
		PRINT_AS(Up, 	'^')
		PRINT_AS(Down, 	'v')
		PRINT_AS(Left, 	'<')
		PRINT_AS(Right, '>')
		PRINT_AS(No, 	'-')
	}

	return cout;
}

#undef PRINT_AS

template<class ValueType>
void print(const Grid<ValueType>& grid)
{
	// system("clear");

	for (int y = int(grid.size) - 1; y >= 0; y--)
	{
		for (int x = 0; x < int(grid.size); x++)
		{
			std::cout << grid[y][x] << ' ';
		}

		std::cout << '\n';
	}

	std::cin.get();
}


void printPath(	const Grid<MoveDirection>& backDirections,
				const Point& start,
				const Point& finish)
{
	Grid<MoveDirection> resultPath{backDirections.size, MoveDirection::No};

	Point currCell = finish;

	while(true)
	{
		resultPath.at(currCell) = backDirections.at(currCell);
		
		currCell = currCell + getShift(backDirections.at(currCell));

		if (currCell == start)
		{
			break;
		}
	}

	print(resultPath);
}

// For compiller to know which version to generate
template void print<int>(const Grid<int>& graph);
template void print<Point>(const Grid<Point>& graph);
template void print<AlgoState>(const Grid<AlgoState>& graph);
template void print<Tile>(const Grid<Tile>& graph);
template void print<MoveDirection>(const Grid<MoveDirection>& graph);
