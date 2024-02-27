#include "Print.hpp"
#include "Point.hpp"

std::ostream& operator<< (std::ostream& cout, Tile tileType)
{
	switch(tileType)
	{
		case Tile::Obstacle:

			cout << 'X';
			break;

		case Tile::Free:

			cout << '-';
			break;

		case Tile::Unknown:
		default:

			cout << '?';
			break;
	}

	return cout;
}


std::ostream& operator<< (std::ostream& cout, AlgoState algoState)
{
	switch(algoState)
	{
		case AlgoState::Checked:

			cout << '@';
			break;

		case AlgoState::InProgress:

			cout << '*';
			break;

		case AlgoState::Free:

			cout << '-';
			break;

		default:

			cout << '?';
			break;
	}

	return cout;
}

std::ostream& operator<< (std::ostream& cout, MoveDirection direction)
{
	switch(direction)
	{
		case MoveDirection::Up:

			cout << '^';
			break;

		case MoveDirection::Down:

			cout << 'v';
			break;


		case MoveDirection::Left:

			cout << '<';
			break;


		case MoveDirection::Right:

			cout << '>';
			break;

		case MoveDirection::No:

			cout << '-';
			break;
	}

	return cout;
}

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
