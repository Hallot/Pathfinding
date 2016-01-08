#include "AStar.h"
#include "Node.h"
#include "Space3d.h"
#include <qmap.h>
#include <qhash.h>
#include <stdio.h>

/*!
 * \brief AStar::findPath Return the path from start to goal using the a* algorithm.
 * \param startPosition The node of the start position.
 * \param goalPosition The node of the goal.
 * \param space The space for the search.
 * \return The last node that contains the result's path.
 */
Node* AStar::findPath(Node* startPosition, Node* goalPosition, Space3d* space)
{
	// the open set where the nodes to be explored are stored
	// a min heap where the node with the lowest cost is stored first
	QMap<double, Node*> openSet;
	// the closed set where the already explored nodes are stored
	QHash<unsigned long, Node*> closedSet;

	// put the start position in the open set
	openSet.insert(openSet.begin(), 0., startPosition);

	while (!openSet.empty())
	{
		Node* current = openSet.begin().value();
		openSet.erase(openSet.begin());
		// create the neighbouring nodes
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					// center is the current one
					if (i != 0 && j != 0 && k != 0)
					{
						// if outside the space
						if ((int)current->x() + i < 0 || current->x() + i > space->sizeX() ||
								(int)current->y() + j < 0 || current->y() + j > space->sizeY() ||
								(int)current->z() + k < 0 || current->z() + k > space->sizeZ())
						{
							continue;
						}

						// set the parent node to current for the new nodes
						Node* newNode = new Node(current, current->x() + i, current->y() + j, current->z() + k);

						// if we have found the goal, we are done
						if (newNode == goalPosition)
						{
							return newNode;
						}

						// update the costs
						newNode->setPreviousCost(current->previousCost() + Node::squaredEuclidianDistance(current, newNode));
						newNode->setHeuristic(Node::squaredEuclidianDistance(newNode, goalPosition));
						newNode->setCost(newNode->previousCost() + newNode->heuristic());

						// if node with same coordinates in openSet but lower cost, skip
						for (auto it = openSet.begin(); it != openSet.end(); it++)
						{
							// only need to search over those with a lower cost
							if (it.key() > newNode->cost())
							{
								break;
							}
							// if same coordinates
							else if (it.value() == newNode)
							{
								// remove the node
								openSet.erase(it);
								// add the new node instead
								openSet.insert(newNode->cost(), newNode);
								// break out of the search loop
								break;
								// continue to the next value of the neighbours' loop
								continue;
							}
						}

						// if node with same coordinates in closedSet but lower cost, skip
						auto it = closedSet.find(cantorTuple(newNode->x(), newNode->y(), newNode->z()));
						if (it != closedSet.end() && it.value() == newNode)
						{
							// if the cost is lower for the existing node
							if (it.value()->cost() < newNode->cost())
							{
								// continue to the next value of the neighbours' loop
								continue;
							}
						}

						// add the node to the open list
						openSet.insertMulti(newNode->cost(), newNode);
					}
				}
			}
		}
		// add current to the closed list
		closedSet.insert(cantorTuple(current->x(), current->y(), current->z()), current);
	}

	// no solution found
	return nullptr;
}

/*!
 * \brief AStar::cantorTuple Return the cantor tuple associated with the 3 integers
 * https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function
 * \param a
 * \param b
 * \param c
 * \return A unique natural number based on the three inputs.
 */
unsigned long AStar::cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c)
{
	unsigned long cantor = (unsigned long)(1/2 * (1/2 * (a + b) * (a + b + 1) + b + c) * (1/2 * (a + b) * (a + b + 1) + b + c + 1) + c);
	//printf("%lu\n", cantor);
	return cantor;
}