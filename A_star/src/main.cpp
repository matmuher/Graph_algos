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

		Grid<TileType> grid{size};

		grid[0][1] = TileType::Obstacle;
		grid[1][1] = TileType::Obstacle;
		grid[2][1] = TileType::Obstacle;
		grid[3][1] = TileType::Obstacle;

		Grid<Point> paths{size};

		// print(grid);

		std::queue<Point> nextDoors;

		Point start{0, 0};
		Point finish{2, 0};

		nextDoors.push(start);

		while(!nextDoors.empty())
		{
			Point current = nextDoors.front();
			nextDoors.pop();

			grid.at(current) = TileType::Checked;

			if (current == finish)
			{
				break;
			}

			for (Point shift : shifts)
			{
				Point neighbour = current + shift;

				if (lessEqualThan(Zeros, neighbour) && lessThan(neighbour, Point{size}) &&
					grid.at(neighbour) != TileType::Checked &&
					grid.at(neighbour) != TileType::InProgress &&
					grid.at(neighbour) != TileType::Obstacle)
				{
					paths.at(neighbour) = current;
					grid.at(neighbour) = TileType::InProgress;
					nextDoors.push(neighbour);
				}
			}

			// print(paths);
		}

		grid.at(start) = TileType::Path;
		grid.at(finish) = TileType::Path;

		Point currCell = paths.at(finish);
		
		while(currCell != start)
		{
			grid.at(currCell) = TileType::Path;

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