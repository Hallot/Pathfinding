#include "Space3d.h"
#include "AStar.h"
#include "Node.h"
#include "Path.h"
#include <iostream>

int main()
{
	// Create the 3d space
	Space3d* space = new Space3d(50, 50, 50);

	// Set the inner values at true, the rest false
	for (unsigned int i = 0; i < 50; i++)
	{
		for (unsigned int j = 0; j < 50; j++)
		{
			for (unsigned int k = 0; k < 50; k++)
			{
				if ((i > 0 && i < 50) && (j > 0 && j < 50) && (k > 0 && k < 15))
				{
					space->operator ()(i, j, k) = true;
				}
				if ((i > 0 && i < 50) && (j > 0 && j < 50) && (k > 35 && k < 50))
				{
					space->operator ()(i, j, k) = true;
				}
			}
		}
	}

	for (unsigned int k = 0; k < 50; k++)
	{
		space->operator ()(29, 29, k) = true;
		space->operator ()(30, 30, k) = true;
		space->operator ()(31, 31, k) = true;
	}

	Node* start = new Node(nullptr, 10, 10, 10);
	Node* goal = new Node(nullptr, 40, 40, 40);

	Path* result = AStar::findPath(start, goal, space);
	if (result != nullptr)
	{
		std::cout << result->toString();
	}
	else
	{
		std::cout << "Invalid path.\n";
	}

	delete space;

	return 0;
}

