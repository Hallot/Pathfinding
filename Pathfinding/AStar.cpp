#include "AStar.h"
#include "Node.h"
#include "Space3d.h"
#include <QMultiMap>
#include <qhash.h>
#include <iostream>

/*!
 * \brief AStar::findPath Return the path from start to goal using the a* algorithm.
 * \param startPosition The node of the start position.
 * \param goalPosition The node of the goal.
 * \param space The space for the search.
 * \return The last node that contains the result's path.
 */
Path* AStar::findPath(Node* startPosition, Node* goalPosition, Space3d* space)
{
	// check that the start and goal are valid
	if (!isValid(space, startPosition->x(), startPosition->y(), startPosition->z()) ||
			!isValid(space, goalPosition->x(), goalPosition->y(), goalPosition->z()))
	{
		return nullptr;
	}

	// and check that start is not goal
	if (startPosition->operator ==(goalPosition))
	{
		return pathFromNode(goalPosition);
	}

	// the open set where the nodes to be explored are stored
	// a min heap where the node with the lowest cost is stored first
	QHash<unsigned long, Node*> openSet;
	// the closed set where the already explored nodes are stored
	QHash<unsigned long, Node*> closedSet;

	// put the start position in the open set
	openSet.insert(cantorTuple(startPosition->x(), startPosition->y(), startPosition->z()), startPosition);

	while (!openSet.empty())
	{
		// select the node with the lowest cost
		Node* current = nullptr;
		foreach (Node* node, openSet)
		{
			if (current == nullptr)
			{
				current = node;
			}
			else if (node->cost() < current->cost())
			{
				current = node;
			}
		}
		// remove it from the openset
		openSet.remove(cantorTuple(current->x(), current->y(), current->z()));
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
					if (!isValid(space, current->x() + i, current->y() + j, current->z() + k))
					{
						continue;
					}

					// set the parent node to current for the new nodes
					Node* newNode = new Node(current, current->x() + i, current->y() + j, current->z() + k);

					// if we have found the goal, we are done
					if (newNode->operator ==(goalPosition))
					{
						// recreate the path from the final node
						Path* path = pathFromNode(newNode);

						// delete all the nodes
						delete newNode;
						qDeleteAll(openSet);
						openSet.clear();
						qDeleteAll(closedSet);
						closedSet.clear();

						return path;
					}

					// update the costs
					newNode->setPreviousCost(current->previousCost() + Node::squaredEuclidianDistance(current, newNode));
					newNode->setHeuristic(Node::squaredEuclidianDistance(newNode, goalPosition));
					newNode->setCost(newNode->previousCost() + newNode->heuristic());

					// if node with same coordinates in openSet but lower cost, skip
					// else replace it
					auto itOpen = openSet.find(cantorTuple(newNode->x(), newNode->y(), newNode->z()));
					if (itOpen != openSet.end())
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
					auto itClosed = closedSet.find(cantorTuple(newNode->x(), newNode->y(), newNode->z()));
					if (itClosed != closedSet.end())
					{
						// delete the node
						delete newNode;
						// continue to the next value of the neighbours' loop
						continue;
					}

					// add the node to the open list
					openSet.insert(cantorTuple(newNode->x(), newNode->y(), newNode->z()), newNode);
				}
			}
		}
		// add current to the closed list
		closedSet.insert(cantorTuple(current->x(), current->y(), current->z()), current);
	}

	// no solution found
	// delete all the nodes
	qDeleteAll(openSet);
	openSet.clear();
	qDeleteAll(closedSet);
	closedSet.clear();

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
	return (unsigned long)((double)1/2 * ((double)1/2 * (a + b) * (a + b + 1) + b + c) * ((double)1/2 * (a + b) * (a + b + 1) + b + c + 1) + c);
}

/*!
 * \brief AStar::nodeFromPath Return the path from the final node.
 * \param node The end node of the path.
 * \return
 */
Path* AStar::pathFromNode(Node* node)
{
	Path* path = new Path();
	while (node != nullptr)
	{
		Path::Point* point = new Path::Point(node->x(), node->y(), node->z());
		path->prepend(point);
		node = node->parent();
	}
	return path;
}

/*!
 * \brief AStar::isValid Return if a node is valid or not.
 * \param space The space to check
 * \param i
 * \param j
 * \param k
 * \return True is the point is in the space and point to a valid point, false otherwise
 */
bool AStar::isValid(Space3d* space, const unsigned int i, const unsigned int j, const unsigned int k)
{
	return (i > 0 && i < space->sizeX() &&
			j > 0 && j < space->sizeY() &&
			k > 0 && k < space->sizeZ() &&
			space->operator ()(i, j, k));
}
