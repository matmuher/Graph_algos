#include <queue>
#include <iostream>
#include <array>

#include "Graph.hpp"

/*

	For path finding I want to store
	history of each 	

*/

using ValueType = int;

int main()
{
	try
	{
		size_t size = 5; 

		Grid<int> grid{size};
		Grid<Point> paths{size};

		// print(grid);

		std::queue<Point> nextDoors;

		Point start{0, 0};
		Point finish{2, 2};

		nextDoors.push(start);

		while(!nextDoors.empty())
		{
			Point current = nextDoors.front();
			nextDoors.pop();

			grid.at(current) = 1;

			if (current == finish)
			{
				break;
			}

			for (Point shift : shifts)
			{
				Point neighbour = current + shift;

				if (lessEqualThan(Zeros, neighbour) && lessThan(neighbour, Point{size}) &&
					grid.at(neighbour) != 1 &&
					grid.at(neighbour) != 8)
				{
					paths.at(neighbour) = current;
					grid.at(neighbour) = 8;
					nextDoors.push(neighbour);
				}
			}

			// print(paths);
		}

		grid.at(start) = 5;
		grid.at(finish) = 5;

		Point currCell = paths.at(finish);
		
		while(currCell != start)
		{
			grid.at(currCell) = 5;

			Point prevCell = paths.at(currCell);

			currCell = prevCell;
		}

		print(grid);

		// PathBFS = SearchBFS(grid, start, end);

		// PathDFS = SearchDFS(grid, start, end);

		// PathAStar = SearchAStar(grid, start, end);

		// print(PathBFS);

		// print(PathDFS);

		// print(PathAStar);
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}