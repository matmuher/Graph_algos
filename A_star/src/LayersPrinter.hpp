#pragma once

#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"

#include <vector>
// #include <functional> // ? reference_wrapper ? to avoid null checking

// Common interface for all grid printers
struct GridPrinter
{
	virtual bool isTransparent(Point point) const = 0;

	virtual void print(Point point) const = 0;


};

// Essentially it's a wrapper around grid.
// It lets organize grids using common interface into
// container. Then print grids with priorities.

template<class T>
struct TerminalPrinter final : public GridPrinter
{
	const Grid<T>& grid;

	const T TransparentValue;

	TerminalPrinter(const Grid<T>& grid_);

	TerminalPrinter(const Grid<T>& grid_, T TransparentValue_);

	bool isTransparent(Point point) const override;

	void print(Point point) const override;
};

template<class T>
TerminalPrinter<T>::TerminalPrinter(const Grid<T>& grid_, T TransparentValue_)
:
	grid{grid_},
	TransparentValue{TransparentValue_}
{}

template<class T>
TerminalPrinter<T>::TerminalPrinter(const Grid<T>& grid_)
:
	TerminalPrinter{grid_, T()} // default
{}

template<class T>
bool TerminalPrinter<T>::isTransparent(Point point) const
{
	return grid.at(point) == TransparentValue;
}

template<class T>
void TerminalPrinter<T>::print(Point point) const
{
	std::cout << grid.at(point);
}

void drawLayers(int size, const std::vector<const GridPrinter*> printers)
{
	// throw for size equality

	for (int y = size - 1; y >= 0; y--)
	{
		for (int x = 0; x < size; x++)
		{
			bool isTransparent = true; 

			for (auto printer : printers)
			{
				if (!printer->isTransparent({x, y}))
				{
					isTransparent = false;
					printer->print({x, y}); 	// under the hood it prints values of different types
												// depending on concrete instantiation of TerminalPrinter
					break;
				}
			}

			if (isTransparent)
			{
				std::cout << '-';
			}

			std::cout << ' ';
		}

		std::cout << '\n';
	}

	std::cin.get();
}
