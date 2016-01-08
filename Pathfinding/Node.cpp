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

/*!
 * \brief Node::operator == Two nodes are equals if the have the same position
 * \param rightHandSide The right hand side value to be compared.
 * \return True if the tow nodes have the same coordinates, false otherwise.
 */
bool Node::operator==(Node* rightHandSide)
{
	return (this->x() == rightHandSide->x()) && (this->y() == rightHandSide->y()) && (this->z() == rightHandSide->z());
}

/*!
 * \brief Node::squaredEuclidianDistance Square of the euclidian distance between two nodes
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the euclidian distance betweent the two nodes squared
 */
double Node::squaredEuclidianDistance(Node* node1, Node* node2)
{
	return qAbs((node1->x() - node2->x()) + (node1->y() - node2->y()) + (node1->z() - node2->z()));
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

double Node::cost() const
{
	return _cost;
}

void Node::setCost(double cost)
{
	_cost = cost;
}

double Node::previousCost() const
{
	return _previousCost;
}

void Node::setPreviousCost(double previousCost)
{
	_previousCost = previousCost;
}

double Node::heuristic() const
{
	return _heuristic;
}

void Node::setHeuristic(double heuristic)
{
	_heuristic = heuristic;
}