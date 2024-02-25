#include <queue>
#include <iostream>
#include <array>
#include <limits>
#include <queue>
#include <cmath>

#include "Graph.hpp"

struct WeightedPoint
{
	Point point;
	int weight;

	WeightedPoint(const Point& _point, int _weight) : point{_point}, weight{_weight} {}
};

bool operator<(const WeightedPoint& lhs, const WeightedPoint& rhs)
{
	return lhs.weight > rhs.weight;
}

/*
	For path finding I want to store
	history of each 	

*/

using ValueType = int;

class Bloodhound // aka "isheika"
{
	// ending node points to its predecessor
	virtual Grid<Point> findPath(const Point& start, const Point& end) = 0;
};

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
		Grid<int> costs{size, 1};
		Grid<int> pathCosts{size, 1000};

		// map[0][1] = Tile::Obstacle; // add read from file
		// map[1][1] = Tile::Obstacle;
		// map[2][1] = Tile::Obstacle;
		// map[3][1] = Tile::Obstacle;

		pathCosts.at({0, 0}) = 0;

// [Dijkstra]

		std::priority_queue<WeightedPoint> weightedNextDoors;

		Point start{0, 0};
		Point finish{4, 0};

		costs.at({0, 1}) = 1;
		costs.at({0, 2}) = 1;

		costs.at({1, 1}) = 1;
		costs.at({1, 2}) = 1;

		weightedNextDoors.emplace(start, pathCosts.at(start));

		while(!weightedNextDoors.empty())
		{
			Point current = weightedNextDoors.top().point; // choose point with the least cost
			weightedNextDoors.pop();

			state.at(current) = AlgoState::Checked;

			if (current == finish)
			{
				break;
			}

			auto f = [&](Point point)
						{
							return costs.at(point) + dot(point - finish, point - finish);
						}; 

			for (Point shift : shifts)
			{
				Point neighbour = current + shift;

				if (lessEqualThan(Zeros, neighbour) && lessThan(neighbour, Point{size}) &&
					state.at(neighbour) != AlgoState::Checked &&
					state.at(neighbour) != AlgoState::InProgress &&
					map.at(neighbour) != Tile::Obstacle &&
					pathCosts.at(current) + f(neighbour) < pathCosts.at(neighbour)) // add to queue only if path is shorter
				{
					paths.at(neighbour) = current;
					state.at(neighbour) = AlgoState::InProgress;
					pathCosts.at(neighbour) = pathCosts.at(current) + f(neighbour);

					weightedNextDoors.emplace(neighbour, pathCosts.at(neighbour));
				}
			}

			print(state);
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

		print(results); // add effect of transparenc to draw layer up layer
						// or priority drawing 
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}