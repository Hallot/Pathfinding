#include "AStarQuick.h"
#include "Node.h"
#include "Space3d.h"
#include "Utils.h"
#include "OrderedHash.h"
#include <qhash.h>
#include <iostream>

/*!
 * \brief AStarQuick::findPath Return the path from start to goal using the a* algorithm.
 * \param startPosition The node of the start position.
 * \param goalPosition The node of the goal.
 * \param space The space for the search.
 * \return The last node that contains the result's path.
 */
Path* AStarQuick::findPath(Node* startPosition, Node* goalPosition, Space3d* space)
{
	// check that the start and goal are valid
	if (!Utils::isValid(space, startPosition->x(), startPosition->y(), startPosition->z()) ||
			!Utils::isValid(space, goalPosition->x(), goalPosition->y(), goalPosition->z()))
	{
		return nullptr;
	}

	// and check that start is not goal
	if (startPosition->operator ==(goalPosition))
	{
		return Utils::pathFromNode(goalPosition);
	}

	// the open set where the nodes to be explored are stored
	// the nodes are stored in a hash map while the order is stored in a map
	OrderedHash* openSet = new OrderedHash();
	// the closed set where the already explored nodes are stored
	QHash<unsigned long, Node*>* closedSet = new QHash<unsigned long, Node*>();

	// put the start position in the open set
	openSet->insert(Utils::cantorTuple(startPosition->x(), startPosition->y(), startPosition->z()), startPosition);

	while (!openSet->empty())
	{
		// select the node with the lowest cost and delete it from the openset
		Node* current = openSet->popLowest();

		// create the neighbouring nodes
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					// 0, 0, 0 is the current position
					if (i == 0 && j == 0 && k == 0)
					{
						continue;
					}

					// if outside the space or in invalid case
					if (!Utils::isValid(space, current->x() + i, current->y() + j, current->z() + k))
					{
						continue;
					}

					// set the parent node to current for the new nodes
					Node* newNode = new Node(current, current->x() + i, current->y() + j, current->z() + k);

					// if we have found the goal, we are done
					if (newNode->operator ==(goalPosition))
					{
						// recreate the path from the final node
						Path* path = Utils::pathFromNode(newNode);

						// delete all the nodes
						delete newNode;
						delete openSet;
						qDeleteAll(closedSet->begin(), closedSet->end());
						closedSet->clear();
						delete closedSet;

						return path;
					}

					// update the costs
					newNode->setPreviousCost(current->previousCost() + Utils::squaredEuclidianDistance(current, newNode));
					newNode->setHeuristic(Utils::squaredEuclidianDistance(newNode, goalPosition));
					newNode->setCost(newNode->previousCost() + newNode->heuristic());

					// if node with same coordinates in openSet but lower cost, skip
					// else replace it
					auto itOpen = openSet->find(Utils::cantorTuple(newNode->x(), newNode->y(), newNode->z()));
					if (itOpen != openSet->end())
					{
						// existing with lower cost than in openset
						if (itOpen.value()->cost() > newNode->cost())
						{
							// replace the old node by the new one
							itOpen.value()->setValue(newNode);
						}
						// delete the now useless new one
						delete newNode;
						// continue to the next value of the neighbours' loop
						continue;
					}

					// if node with same coordinates in closedSet skip
					auto itClosed = closedSet->find(Utils::cantorTuple(newNode->x(), newNode->y(), newNode->z()));
					if (itClosed != closedSet->end())
					{
						// delete the node
						delete newNode;
						// continue to the next value of the neighbours' loop
						continue;
					}

					// add the node to the open list
					openSet->insert(Utils::cantorTuple(newNode->x(), newNode->y(), newNode->z()), newNode);
				}
			}
		}
		// add current to the closed list
		closedSet->insert(Utils::cantorTuple(current->x(), current->y(), current->z()), current);
	}

	// no solution found
	// delete all the nodes
	delete openSet;
	qDeleteAll(closedSet->begin(), closedSet->end());
	closedSet->clear();
	delete closedSet;

	return nullptr;
}
