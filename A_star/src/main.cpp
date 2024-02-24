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

// [create layers]

		size_t size = 5; 

		Grid<Tile> map{size}; 	// it would be convinient to give list of neccessary layers
								// when craete grid. builder pattern?
		Grid<AlgoState> state{size};
		Grid<Point> paths{size};
		Grid<Results> results{size};

		map[0][1] = Tile::Obstacle;
		map[1][1] = Tile::Obstacle;
		map[2][1] = Tile::Obstacle;
		map[3][1] = Tile::Obstacle;

// [BFS]

		std::queue<Point> nextDoors;

		Point start{0, 0};
		Point finish{2, 0};

		nextDoors.push(start);

		while(!nextDoors.empty())
		{
			Point current = nextDoors.front();
			nextDoors.pop();

			state.at(current) = AlgoState::Checked;

			if (current == finish)
			{
				break;
			}

			for (Point shift : shifts)
			{
				Point neighbour = current + shift;

				if (lessEqualThan(Zeros, neighbour) && lessThan(neighbour, Point{size}) &&
					state.at(neighbour) != AlgoState::Checked &&
					state.at(neighbour) != AlgoState::InProgress &&
					map.at(neighbour) != Tile::Obstacle)
				{
					paths.at(neighbour) = current;
					state.at(neighbour) = AlgoState::InProgress;

					nextDoors.push(neighbour);
				}
			}

			// print(paths);
		}

		results.at(start) = Results::Path;
		results.at(finish) = Results::Path;

		Point currCell = paths.at(finish);
		
		while(currCell != start)
		{
			results.at(currCell) = Results::Path;

			Point prevCell = paths.at(currCell);

			currCell = prevCell;
		}

		print(results);

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