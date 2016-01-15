#include "Node.h"
#include <qmath.h>

/*!
 * \brief Node::Node Constructor.
 * \param Parent The parent node.
 * \param x The x coordinate of the node.
 * \param y The x coordinate of the node.
 * \param z The x coordinate of the node.
 */
Node::Node(Node* parent, unsigned int x, unsigned int y, unsigned int z):
	_parent(parent),
	_x(x),
	_y(y),
	_z(z),
	_cost(0),
	_previousCost(0),
	_heuristic(0)
{
}

Node::Node(Node* parent, unsigned int x, unsigned int y, unsigned int z, double cost, double previousCost, double heuristic):
	_parent(parent),
	_x(x),
	_y(y),
	_z(z),
	_cost(cost),
	_previousCost(previousCost),
	_heuristic(heuristic)
{
}

/*!
 * \brief Node::operator == Two nodes are equals if the have the same position
 * \param rightHandSide The right hand side value to be compared.
 * \return True if the two nodes have the same coordinates, false otherwise.
 */
bool Node::operator==(const Node* rightHandSide) const
{
	return (this->x() == rightHandSide->x()) && (this->y() == rightHandSide->y()) && (this->z() == rightHandSide->z());
}

/*!
 * \brief Node::operator != Two nodes are different if they have different position
 * \param rightHandSide The right hand side value to be compared.
 * \return False if the two nodes have the same coordinates, true otherwise.
 */
bool Node::operator!=(const Node* rightHandSide) const
{
	return !(*this == rightHandSide);
}

/*!
 * \brief Node::setValue Set the value of a node to this node.
 * \param node The node from which to set the values.
 */
void Node::setValue(Node* node)
{
	this->setX(node->x());
	this->setY(node->y());
	this->setZ(node->z());
	this->setCost(node->cost());
	this->setHeuristic(node->heuristic());
	this->setParent(node->parent());
	this->setPreviousCost(node->previousCost());
}

/*!
 * \brief Node::depth Return the depth of the node.
 * \return The number of parents this node has.
 */
unsigned int Node::depth()
{
	unsigned int depth = 0;
	Node * node = this;
	while (node != nullptr)
	{
		depth++;
		node = node->parent();
	}
	return depth;
}


Node* Node::parent() const
{
	return _parent;
}

void Node::setParent(Node* parent)
{
	_parent = parent;
}

unsigned int Node::x() const
{
	return _x;
}

void Node::setX(unsigned int x)
{
	_x = x;
}

unsigned int Node::y() const
{
	return _y;
}

void Node::setY(unsigned int y)
{
	_y = y;
}

unsigned int Node::z() const
{
	return _z;
}

void Node::setZ(unsigned int z)
{
	_z = z;
}

unsigned int Node::cost() const
{
	return _cost;
}

void Node::setCost(unsigned int cost)
{
	_cost = cost;
}

unsigned int Node::previousCost() const
{
	return _previousCost;
}

void Node::setPreviousCost(unsigned int previousCost)
{
	_previousCost = previousCost;
}

unsigned int Node::heuristic() const
{
	return _heuristic;
}

void Node::setHeuristic(unsigned int heuristic)
{
	_heuristic = heuristic;
}
