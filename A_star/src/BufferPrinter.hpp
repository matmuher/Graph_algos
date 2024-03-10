#pragma once

#include <vector>

namespace GA
{
	/*
		Что меня интересует в конкретном grid'е,
		и что нужно свести к однородному виду:

		isTransparent()
		getValue()
	*/

	#include <iostream>

	template<class BufferType>
	struct BaseInterLayer
	{
		virtual bool isTransparent(Point point) const = 0;
		virtual BufferType getValue(Point point) const = 0;
		
		virtual ~BaseInterLayer() {}; // for free'ing derived classes
	};

	template<class BufferType, class GridType>
	struct FreeInterLayer : public BaseInterLayer<BufferType>
	{
		const Grid<GridType>& grid;
		const GridType transparent; 

		FreeInterLayer(const Grid<GridType>& grid_, GridType transparent_)
		:
			grid{grid_},
			transparent{transparent_}
		{}

		FreeInterLayer(const Grid<GridType>& grid_)
		:
			FreeInterLayer{grid_, GridType()}
		{}

		bool isTransparent(Point point) const override
		{
			return grid.at(point) == transparent;
		}

		BufferType getValue(Point point) const override
		{
			BufferType x = static_cast<BufferType>(grid.at(point));
			return x;
		}
	};

	template<class BufferType>
	struct Filler
	{
		template<class GridType>
		Filler(const Grid<GridType>& grid, GridType transparent)
		:
			interLayer{new FreeInterLayer<BufferType, GridType>{grid, transparent}}
		{}

		Filler(const Filler& other) = delete;
		Filler(Filler&& other)
		{
			interLayer = other.interLayer;
			other.interLayer = nullptr;
		}
		
		bool isTransparent(Point point) const
		{
			return interLayer->isTransparent(point);
		}

		BufferType getValue(Point point) const
		{
			return interLayer->getValue(point);
		}

		~Filler()
		{
			delete interLayer;
		}

		const BaseInterLayer<BufferType>* interLayer;
	};

	template<class BufferType>
	void fillBuffer(Grid<BufferType>& buffer,
					const std::vector<Filler<BufferType>>& fillers)
	{
		int size = buffer.size;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				for (auto const& filler : fillers)
				{
					if (!filler.isTransparent({x, y}))
					{
						buffer[y][x] = filler.getValue({x, y});
						break;
					}
				}
			}
		}
	}

};