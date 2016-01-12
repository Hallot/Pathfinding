#include "Space3d.h"
#include "AStar.h"
#include "AStarQuick.h"
#include "Node.h"
#include "Path.h"
#include <iostream>
#include <ctime>

int main()
{
	// Create the 3d space
	Space3d* space = new Space3d(500, 500, 500);

	// Set the inner values at true, the rest false
	for (unsigned int i = 0; i < 500; i++)
	{
		for (unsigned int j = 0; j < 500; j++)
		{
			for (unsigned int k = 0; k < 500; k++)
			{
				if ((i > 0 && i < 500) && (j > 0 && j < 500) && (k > 0 && k < 15))
				{
					space->operator ()(i, j, k) = true;
				}
				if ((i > 0 && i < 500) && (j > 0 && j < 500) && (k > 85 && k < 500))
				{
					space->operator ()(i, j, k) = true;
				}
			}
		}
	}

	for (unsigned int k = 0; k < 500; k++)
	{
		space->operator ()(29, 29, k) = true;
		space->operator ()(30, 30, k) = true;
		space->operator ()(31, 31, k) = true;
	}

	Node* start = new Node(nullptr, 10, 10, 10, 0., 0., 0.);
	Node* goal = new Node(start, 400, 400, 400, 0., 0., 0.);


	std::clock_t begin;
	begin = std::clock();
	Path* result = AStar::findPath(start, goal, space);
	std::cout << "AStar time: " << (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	Node* start2 = new Node(nullptr, 10, 10, 10, 0., 0., 0.);
	Node* goal2 = new Node(start2, 400, 400, 400, 0., 0., 0.);

	begin = std::clock();
	Path* result2 = AStarQuick::findPath(start2, goal2, space);
	std::cout << "AStarQuick time: " << (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	// print result
	if (result != nullptr)
	{
		std::cout << result->toString();
	}
	else
	{
		std::cout << "Invalid path.\n";
	}

	// print result2
	if (result2 != nullptr)
	{
		std::cout << result2->toString();
	}
	else
	{
		std::cout << "Invalid path.\n";
	}

	// cleaning up
	delete result;
	delete result2;
	delete goal;
	delete goal2;
	delete space;

	return 0;
}

