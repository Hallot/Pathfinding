#include "SMAStar.h"
#include "Node.h"
#include "Space3d.h"
#include "Utils.h"
#include "OrderedHash.h"
#include <qhash.h>
#include <QtMath>
#include <iostream>
#include <QQueue>

/*!
 * \brief SMAStar::findPath Return the path from start to goal using the a* algorithm.
 * \param startPosition The node of the start position.
 * \param goalPosition The node of the goal.
 * \param space The space for the search.
 * \return The last node that contains the result's path.
 */
Path* SMAStar::findPath(Node* startPosition, Node* goalPosition, Space3d* space, unsigned int maxDepth)
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

	// put the start position in the open set
	openSet->insert(Utils::cantorTuple(startPosition), startPosition);

	// create the nodeTree
	NodeTree* nodeTree = new NodeTree(startPosition);

	while (!openSet->empty())
	{
		// select the node with the lowest cost
		Node* current = openSet->lowest();
		NodeTree* currentNodeTree = nullptr;
		NodeTree::find(current, nodeTree, currentNodeTree);
		if (currentNodeTree == nullptr)
		{
			std::cout << "Couldn't find node in nodeTree." << std::endl;
			return nullptr;
		}

		// if we have found the goal, we are done
		if (current->operator ==(goalPosition))
		{
			// recreate the path from the final node
			Path* path = Utils::pathFromNode(current);

			// delete all the nodes
			delete openSet;

			// return the path
			return path;
		}

		QList<Node*>* neighbours = new QList<Node*>();

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

					// add it to the neighbour's list
					neighbours->append(newNode);
				}
			}
		}

		// now add the neighbours one by one
		while (!neighbours->empty())
		{
			// get the first neighbour
			Node* neighbour = neighbours->at(0);

			// if not a goal and max depth
			if (neighbour->operator !=(goalPosition) && neighbour->depth() == maxDepth)
			{
				// infinity, or max unsigned int size
				unsigned int infinity = 0;
				infinity -= 1;
				// there is no memory left to go past this node, so the entire path is useless
				neighbour->setCost(infinity);
			}
			else
			{
				// update the costs
				neighbour->setPreviousCost(current->previousCost() + Utils::squaredEuclidianDistance(current, neighbour));
				neighbour->setHeuristic(Utils::squaredEuclidianDistance(neighbour, goalPosition));

				// new cost is max of parent and this node cost
				neighbour->setCost(qMax(current->cost(), neighbour->previousCost() + neighbour->heuristic()));
			}

			// if all children have already been added to the queue via a shorter way
			bool remove = true;
			foreach (Node* node, *neighbours)
			{
				if (!openSet->contains(node))
				{
					remove = false;
					break;
				}
			}
			// then remove the parrent
			if (remove)
			{
				nodeTree->removeLeaf(currentNodeTree);
				delete currentNodeTree;
			}

			// if memory is full
			if (current->depth() == maxDepth)
			{
				// find the shallowest node with the highest cost
				NodeTree* worstNode = nodeTree->findShallowestHighestCost();
				// add it to the forgotten node of the parent
				worstNode->parent->forgottenCost = worstNode->node->cost();
				worstNode->parent->forgottenNode = worstNode;
				// and now remove it from the parent children list
				worstNode->parent->children->removeOne(worstNode);
			}

			// now finally insert the node
			openSet->insert(Utils::cantorTuple(neighbour), neighbour);
			nodeTree->addChild(new NodeTree(neighbour, currentNodeTree), currentNodeTree);
			// and remove it from the neighbours' list
			neighbours->removeAt(0);
		}

		// update current cost to the minimum of its children
		nodeTree->updateCost(currentNodeTree);
	}

	// no solution found
	// delete all the nodes
	delete openSet;

	return nullptr;
}

/*!
 * \brief SMAStar::NodeTree::NodeTree Constructor
 * \param node The node to add as the node value.
 */
SMAStar::NodeTree::NodeTree(Node* node):
	node(node),
	parent(nullptr),
	children(new QList<NodeTree*>()),
	forgottenCost(-1),
	forgottenNode(nullptr)
{

}

/*!
 * \brief SMAStar::NodeTree::NodeTree Constructor
 * \param node The node to add as the node value.
 * \param parent The parent of the node.
 */
SMAStar::NodeTree::NodeTree(Node* node, SMAStar::NodeTree* parent):
	node(node),
	parent(parent),
	children(new QList<NodeTree*>()),
	forgottenCost(-1),
	forgottenNode(nullptr)
{
	addChild(this->node, parent);
}

/*!
 * \brief SMAStar::NodeTree::find Return the nodeTree associated with a node.
 * \param node The node to find.
 * \param nodeTree The nodeTree in which to search.
 * \param result The result of the function
 */
void SMAStar::NodeTree::find(Node* node, NodeTree* nodeTree, NodeTree* result)
{
	if (nodeTree->node->operator ==(node))
	{
		result = nodeTree;
	}
	else if (nodeTree->children->empty())
	{
		result = nullptr;
	}
	else
	{
		foreach (NodeTree* child, *nodeTree->children)
		{
			find(node, child, result);
		}
	}
}

/*!
 * \brief SMAStar::NodeTree::addChild Add a child to the node.
 * \param child The nodeTree child to add.
 * \param parent The parent to which we attach the node.
 */
void SMAStar::NodeTree::addChild(SMAStar::NodeTree* child, NodeTree* parent)
{
	parent->children->append(child);
}

/*!
 * \brief SMAStar::NodeTree::addChild Add a child to the node.
 * \param child The node child to add.
 * \param parent The parent to which we attach the node.
 */
void SMAStar::NodeTree::addChild(Node* child, SMAStar::NodeTree* parent)
{
	parent->children->append(new NodeTree(child));
}

/*!
 * \brief SMAStar::NodeTree::removeLeaf Remove a leaf from the tree.
 * \param leaf The leaf to remove.
 */
void SMAStar::NodeTree::removeLeaf(NodeTree* leaf)
{
	// if the leaf is the root
	if (leaf->parent == nullptr)
	{
		delete leaf;
	}
	// else remove from the parent then free
	else
	{
		leaf->parent->children->removeOne(leaf);
		delete leaf;
	}
}

/*!
 * \brief SMAStar::NodeTree::updateCost Update cost based on minimum of its children.
 */
void SMAStar::NodeTree::updateCost(NodeTree* node)
{
	// if leaf
	if (node->children->empty())
	{
		node = node->parent;
	}

	// walk the tree back up to the root
	while (node != nullptr)
	{
		// set to infinity at first
		unsigned int minCost = 0;
		minCost--;

		// find the lowest cost of the children
		foreach (NodeTree* nodeTree, *node->children)
		{
			minCost = qMin(minCost, nodeTree->node->cost());
		}
		node->node->setCost(minCost);

		// now update the parent
		node = node->parent;
	}
}

/*!
 * \brief SMAStar::NodeTree::depth Return the depth of a given nodeTree in the tree.
 * \return The depth of the node.
 */
unsigned int SMAStar::NodeTree::depth()
{
	unsigned int depth = 0;
	NodeTree* node = this;
	while (node != nullptr)
	{
		depth++;
		node = node->parent;
	}
	return depth;
}

/*!
 * \brief SMAStar::NodeTree::findShallowestHighestCost Find the shallowest node with the highest cost.
 * \return The shallowest node with the highest cost.
 */
SMAStar::NodeTree* SMAStar::NodeTree::findShallowestHighestCost()
{
	QQueue<NodeTree*> queue;
	NodeTree* traverse;
	// max unsigned int
	unsigned int shallowestDepth = -1;
	unsigned int highestCost = 0;
	NodeTree* bestCandidate = this;

	if (this->children->empty())
	{
		return bestCandidate;
	}

	queue.enqueue(this);

	while (!queue.empty())
	{
		// get the first element
		traverse = queue.dequeue();

		// if no children then we have found the first element with the shallowest depth
		if (traverse->children->empty())
		{
			shallowestDepth = traverse->depth();

			// check if it has a higher cost than the previous one
			if (traverse->node->cost() > highestCost)
			{
				bestCandidate = traverse;
				highestCost = traverse->node->cost();
			}
		}

		// break out of the loop if the current element has a higher depth than the max we are looking for
		if (traverse->depth() > shallowestDepth)
		{
			return bestCandidate;
		}

		// add each child in left/right order
		foreach (NodeTree* node, *traverse->children)
		{
			queue.enqueue(node);
		}
	}

	return bestCandidate;
}
