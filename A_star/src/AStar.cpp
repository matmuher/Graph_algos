#include "AStar.hpp"
#include "Print.hpp"

AStar::AStar(	const Grid<Tile>& map,
				const Grid<int>& tileCosts)
:
	size_{map.size},

	map_{map},
	tileCosts_{tileCosts},
	
	state_{size_},
	pathsToStart_{size_},
	pathCosts_{size_},
	moveDirections_{size_}
{}

AStar::AStar(	const Grid<Tile>& map,
				const Grid<int>& tileCosts,
				Point start,
				Point end,
				Heuristic heuristic)
:
	AStar(map, tileCosts)
{
	initSearch(start, end, heuristic);
}

bool AStar::makeStep()
{
	if (!isInit_)
	{
		throw "Algorithm is not initialized";
	}

	if (weightedNextDoors_.empty())
	{
		isInit_ = false;
		return false;
	}

	Point current = weightedNextDoors_.top().point; // choose point with the least cost
	weightedNextDoors_.pop();

	state_.at(current) = AlgoState::Checked;

	if (current == end_)
	{
		isInit_ = false;
		return false;
	}

	for (MoveDirection dir : {	MoveDirection::Up,
								MoveDirection::Right,
								MoveDirection::Down,
								MoveDirection::Left})
	{
		Point neighbour = current + getShift(!dir); // write return address

		int neighbourProbableCost = pathCosts_.at(current) +
									heuristic_(neighbour, tileCosts_.at(neighbour), end_);

		if (isInBoundaries(neighbour) &&
			map_.at(neighbour) != Tile::Obstacle &&
			isUnprocessed(neighbour) &&
			neighbourProbableCost < pathCosts_.at(neighbour))
		{
			moveDirections_.at(neighbour) = dir;
			pathsToStart_.at(neighbour) = current;

			state_.at(neighbour) = AlgoState::InProgress;
			pathCosts_.at(neighbour) = neighbourProbableCost;

			weightedNextDoors_.emplace(neighbour, pathCosts_.at(neighbour)); // how emplace works?
		}
	}

	return true;
}

const Grid<AlgoState>& AStar::state() const
{
	return state_;
}

const Grid<Point>& AStar::pathsToStart() const
{
	return pathsToStart_;
}

const Grid<int>& AStar::pathCosts() const
{
	return pathCosts_;
}

const Grid<MoveDirection>& AStar::moveDirections() const
{
	return moveDirections_;
}

bool AStar::isInBoundaries(const Point& point) const
{
	return 	lessEqualThan(Zeros, point) &&
			lessThan(point, Point{int(size_)});
}

bool AStar::isUnprocessed(const Point& point) const
{
	return 	state_.at(point) != AlgoState::Checked &&
			state_.at(point) != AlgoState::InProgress;
}

Grid<Point> AStar::search(Point start, Point end, Heuristic heuristic)
{
	initSearch(start, end, heuristic);
	while(makeStep()) {;}

	return pathsToStart_;
}

template<class T>
void clearQueue(std::priority_queue<T>& queue)
{
	std::priority_queue<T> empty;
	std::swap(empty, queue); 
}

void AStar::initSearch(Point start, Point end, Heuristic heuristic)
{
	start_ = start;
	end_ = end;
	heuristic_ = heuristic;

	state_.fill(AlgoState::Free);
	pathsToStart_.fill(PathPoison);
	pathCosts_.fill(MaxCost);
	moveDirections_.fill(MoveDirection::No);

	pathCosts_.at(start_) = 0;

	clearQueue(weightedNextDoors_);
	weightedNextDoors_.emplace(start_, 0);

	isInit_ = true;

	// dump();
}

void AStar::dump() const
{
	print(state_);
	print(pathCosts_);
	print(pathsToStart_);
}
