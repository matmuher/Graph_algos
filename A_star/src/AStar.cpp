#include "AStar.hpp"
#include "Print.hpp"
#include "Command.hpp"

namespace GA
{

AStar::AStar(	const Grid<Tile>& map,
				const Grid<int>& tileCosts)
:
	size_{map.size},

	map_{map},
	tileCosts_{tileCosts},
	
	state_{size_},
	pathsToStart_{size_},
	pathCosts_{size_},
	moveDirections_{size_},
	resultPath_{size_}
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

bool AStar::stepBack()
{
	if (!history.empty())
	{
		auto command = history.back();

		command.cancel();

		history.pop_back();
	
		return true;
	}

	return false;
}

bool AStar::makeStep()
{
	if (isInit_ == false)
	{
		std::cout << "Non init\n";
		return false;
	}

	history.emplace_back(weightedNextDoors_, isInit_);
	Command& command = history.back();

	if (weightedNextDoors_.empty())
	{
		std::cout << "Empty queue\n";
		command.setInit(false);
		return isInit_;
	}

	Point current = command.popPoint();

	command.putValue(state_, current, AlgoState::Checked);
	state_.at(current) = AlgoState::Checked;

	if (current == end_)
	{
		setPath();
		command.setInit(false);
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
			command.putValue(moveDirections_, neighbour, dir);

			command.putValue(pathsToStart_, neighbour, current);

			command.putValue(state_, neighbour, AlgoState::InProgress);

			command.putValue(pathCosts_, neighbour, neighbourProbableCost);

			command.pushPoint({neighbour, pathCosts_.at(neighbour)});
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

const Grid<MoveDirection>& AStar::resultPath() const
{
	return resultPath_;
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

	state_.fill(AlgoState::No);
	pathsToStart_.fill(PathPoison);
	pathCosts_.fill(MaxCost);
	moveDirections_.fill(MoveDirection::No);
	resultPath_.fill(MoveDirection::No);

	resultPath_.at(start_) = MoveDirection::Start;
	resultPath_.at(end_) = MoveDirection::End;

	pathCosts_.at(start_) = 0;

	clearQueue(weightedNextDoors_);
	weightedNextDoors_.emplace(start_, 0);

	isInit_ = true;
}

void AStar::dump() const
{
	print(state_);
	print(pathCosts_);
	print(pathsToStart_);
}



void AStar::setPath()
{
	if (history.empty())
	{
		throw "Cant make route: history is empty";
	}

	Command& command = history.back();
	Point currCell = end_ + getShift(moveDirections_.at(end_));

	while(true)
	{
		command.putValue(resultPath_, currCell, moveDirections_.at(currCell));

		currCell = currCell + getShift(moveDirections_.at(currCell));

		if (currCell == start_)
		{
			break;
		}
	}
}

};