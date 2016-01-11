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
				if ((i > 10 && i < 40) && (k > 20 && k < 30))
				{
					space->operator ()(i, j, k) = true;
				}
			}
		}
	}

	space->operator ()(0, 2, 0) = false;

	Node* start = new Node(nullptr, 30, 30, 30);
	Node* goal = new Node(nullptr, 35, 49, 31);

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

