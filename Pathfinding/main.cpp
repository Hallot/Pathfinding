#include "Space3d.h"
#include "AStar.h"
#include "Node.h"
#include <stdio.h>

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

	Node* start = new Node(nullptr, 30, 30, 30);
	Node* goal = new Node(nullptr, 30, 50, 30);

	Node* result = AStar::findPath(start, goal, space);
	//printf("%du, %du, %du\n", result->x(), result->y(), result->z());

	return 0;
}

