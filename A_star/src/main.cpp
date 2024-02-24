#include <queue>
#include <iostream>
#include <array>

#include "Graph.hpp"


struct Point
{
	int x;
	int y;
};

Point operator+(const Point& lhs, const Point& rhs)
{
	return Point{lhs.x + rhs.x, lhs.y + rhs.y};
}

const std::array<Point, 4> shifts{Point{1, 0}, Point{-1, 0}, Point{0, 1}, Point{0, -1}};

int main()
{
	try
	{
		size_t size = 5; 

		Grid grid{size};

		print(grid);

		std::queue<Point> nextDoors;

		Point start{0, 0};

		nextDoors.push(start);

		while(!nextDoors.empty())
		{
			Point current = nextDoors.front();
			nextDoors.pop();

			grid[current.y][current.x] = 1;

			for (Point shift : shifts) // use auto instead?
			{
				Point neighbour = current + shift;

				if (0 <= neighbour.x && neighbour.x < size &&
					0 <= neighbour.y && neighbour.y < size &&
					grid[neighbour.y][neighbour.x].value != 1 &&
					grid[neighbour.y][neighbour.x].value != 8)
				{
					grid[neighbour.y][neighbour.x] = 8;
					nextDoors.push(neighbour);
				}
			}

			print(grid);

			int x;
			std::cin >> x;

			system("clear");
		}

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