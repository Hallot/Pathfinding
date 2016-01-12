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
	_z(z)
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
 * \brief Node::squaredEuclidianDistance Square of the euclidian distance between two nodes
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the euclidian distance between the two nodes squared
 */
unsigned int Node::squaredEuclidianDistance(Node* node1, Node* node2)
{
	return ((int)node1->x() - (int)node2->x()) * ((int)node1->x() - (int)node2->x()) +
			((int)node1->y() - (int)node2->y()) * ((int)node1->y() - (int)node2->y()) +
	  ((int)node1->z() - (int)node2->z()) * ((int)node1->z() - (int)node2->z());
}

/*!
 * \brief Node::euclidianDistance Euclidian distance between two nodes.
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the euclidian distance between the two nodes
 */
unsigned int Node::euclidianDistance(Node* node1, Node* node2)
{
	return qSqrt(((int)node1->x() - (int)node2->x()) * ((int)node1->x() - (int)node2->x()) +
				  ((int)node1->y() - (int)node2->y()) * ((int)node1->y() - (int)node2->y()) +
			((int)node1->z() - (int)node2->z()) * ((int)node1->z() - (int)node2->z()));
}

/*!
 * \brief Node::manhattanDistance Manhattan distance between two nodes.
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the manhattan distance between the two nodes
 */
unsigned int Node::manhattanDistance(Node* node1, Node* node2)
{
	return qAbs((int)node1->x() - (int)node2->x()) + qAbs((int)node1->y() - (int)node2->y()) + qAbs((int)node1->z() - (int)node2->z());
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
