#pragma once

#include "Grid.hpp"
#include "Print.hpp"

#include <vector>
#include <functional>
#include <memory>
#include <queue>
#include <algorithm>

namespace GA
{

class BaseAction
{
public:

	virtual void setNewValue() = 0;
	virtual void setOldValue() = 0;

	virtual ~BaseAction() {};
};

template<class GridType>
class Action : public BaseAction
{
public:

	Action(Grid<GridType>& grid, Point point, GridType new_value)
	:
		grid_{grid},
		point_{point},
		new_value_{new_value},
		old_value_{grid.at(point)}
	{
		setNewValue();
	}

	void setNewValue() override
	{
		grid_.at(point_) = new_value_;
	}

	void setOldValue() override
	{
		grid_.at(point_) = old_value_;
	}

private:

	Grid<GridType>& grid_;
	const Point point_;

	const GridType new_value_;
	const GridType old_value_;
};


template<class Adapter>
Adapter::container_type& getUnderlyingContainer(Adapter& adapter)
{
    struct Getter : Adapter
    {
        auto getUnderlyingContainer() -> decltype(this->c)& {return this->c;}  
    };
    
    return static_cast<Getter&>(adapter).getUnderlyingContainer();
}

class Command
{
private:

	std::priority_queue<WeightedPoint>& weightedNextDoors_;
	bool& isInit_;

	bool oldIsInit_;
	bool newIsInit_;

	std::vector<std::shared_ptr<BaseAction>> actions_;

	WeightedPoint popPoint_;
	std::vector<WeightedPoint> pushPoints_;

public:

	Command(std::priority_queue<WeightedPoint>& weightedNextDoors, bool& isInit)
	:
		weightedNextDoors_{weightedNextDoors},
		isInit_{isInit},
		oldIsInit_{isInit},
		newIsInit_{isInit}
	{}

	void setInit(bool val)
	{
		oldIsInit_ = isInit_;
		isInit_ = val;
		newIsInit_ = val;
	}

	template<class GridType>
	void putValue(Grid<GridType>& grid, Point point, GridType new_value)
	{
		auto action = std::make_shared<Action<GridType>>(grid, point, new_value);
		actions_.push_back(action);
	}

	void apply() const
	{
		for (auto it = actions_.begin(); it != actions_.end(); ++it)
		{
			(*it)->setNewValue();
		}

		weightedNextDoors_.pop();
		for (auto point : pushPoints_)
		{
			weightedNextDoors_.push(point);
		}

		isInit_ = newIsInit_;
	}

	void pushPoint(WeightedPoint point)
	{
		pushPoints_.push_back(point);
		weightedNextDoors_.push(point);
	}

	Point popPoint()
	{
		popPoint_ = weightedNextDoors_.top();
		weightedNextDoors_.pop();
		return popPoint_.point;
	}

	void cancel() const
	{
		for (auto it = actions_.rbegin(); it != actions_.rend(); ++it)
		{
			(*it)->setOldValue();
		}

		weightedNextDoors_.push(popPoint_);
		for (auto point : pushPoints_)
		{
			auto& vec = getUnderlyingContainer(weightedNextDoors_); 
			vec.erase(std::find(	vec.begin(),
									vec.end(),
									point));
		}

		isInit_ = oldIsInit_;
	}
};

};
