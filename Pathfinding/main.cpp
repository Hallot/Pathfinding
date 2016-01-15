#include "Space3d.h"
#include "AStar.h"
#include "AStarQuick.h"
#include "SMAStar.h"
#include "Node.h"
#include "Path.h"
#include "Utils.h"
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
				if ((i > 0 && i < 500) && (j > 0 && j < 500) && (k > 250 && k < 500))
				{
					space->operator ()(i, j, k) = true;
				}
			}
		}
	}

	for (unsigned int k = 15; k < 251; k++)
	{
		space->operator ()(29 + k, 29 + k, k) = true;
		space->operator ()(30 + k, 30 + k, k) = true;
		space->operator ()(31 + k, 31 + k, k) = true;
	}

	std::clock_t begin;


	// A*
	Node* start = new Node(nullptr, 10, 10, 10, 0., 0., 0.);
	Node* goal = new Node(start, 10, 10, 400, 0., 0., 0.);

	begin = std::clock();
	Path* result = AStar::findPath(start, goal, space);
	std::cout << "AStar time: " << (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	// A*Quick
	Node* start2 = new Node(nullptr, 10, 10, 10, 0., 0., 0.);
	Node* goal2 = new Node(start2, 10, 10, 400, 0., 0., 0.);

	begin = std::clock();
	Path* result2 = AStarQuick::findPath(start2, goal2, space);
	std::cout << "AStarQuick time: " << (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	// SMA*
	Node* start3 = new Node(nullptr, 10, 10, 10, 0., 0., 0.);
	Node* goal3 = new Node(start3, 10, 10, 400, 0., 0., 0.);

	begin = std::clock();
//	Path* result3 = SMAStar::findPath(start3, goal3, space, 1000);
	std::cout << "SMAStar(1000) time: " << (std::clock() - begin) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;


	// check the results to see of they are the same.
	if (!Utils::samePaths(result, result2))
	{
		std::cout << "Path 1 and 2 different.\n";
	}
//	if (!Utils::samePaths(result2, result3))
//	{
//		std::cout << "Path 2 and 3 different.\n";
//	}


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

//	// print result3
//	if (result3 != nullptr)
//	{
//		std::cout << result3->toString();
//	}
//	else
//	{
//		std::cout << "Invalid path.\n";
//	}


	// cleaning up
	delete result;
	delete result2;
//	delete result3;
	delete goal;
	delete goal2;
	delete goal3;
	delete space;

	return 0;
}

