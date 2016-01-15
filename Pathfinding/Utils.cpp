#include "Utils.h"
#include "Node.h"
#include "Space3d.h"
#include "Path.h"
#include "QtMath"

/*!
 * \brief Utils::squaredEuclidianDistance Square of the euclidian distance between two nodes
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the euclidian distance between the two nodes squared
 */
unsigned int Utils::squaredEuclidianDistance(Node* node1, Node* node2)
{
	return ((int)node1->x() - (int)node2->x()) * ((int)node1->x() - (int)node2->x()) +
			((int)node1->y() - (int)node2->y()) * ((int)node1->y() - (int)node2->y()) +
	  ((int)node1->z() - (int)node2->z()) * ((int)node1->z() - (int)node2->z());
}

/*!
 * \brief Utils::euclidianDistance Euclidian distance between two nodes.
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the euclidian distance between the two nodes
 */
unsigned int Utils::euclidianDistance(Node* node1, Node* node2)
{
	return qSqrt(((int)node1->x() - (int)node2->x()) * ((int)node1->x() - (int)node2->x()) +
				  ((int)node1->y() - (int)node2->y()) * ((int)node1->y() - (int)node2->y()) +
			((int)node1->z() - (int)node2->z()) * ((int)node1->z() - (int)node2->z()));
}

/*!
 * \brief Utils::manhattanDistance Manhattan distance between two nodes.
 * \param node1 The first node
 * \param node2 The second node
 * \return Return the manhattan distance between the two nodes
 */
unsigned int Utils::manhattanDistance(Node* node1, Node* node2)
{
	return qAbs((int)node1->x() - (int)node2->x()) + qAbs((int)node1->y() - (int)node2->y()) + qAbs((int)node1->z() - (int)node2->z());
}

/*!
 * \brief Utils::cantorTuple Return the cantor tuple associated with the 3 integers
 * https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function
 * \param a An unsigned int.
 * \param b An unsigned int.
 * \param c An unsigned int.
 * \return A unique natural number based on the three inputs.
 */
unsigned long Utils::cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c)
{
	return (unsigned long)((double)1/2 * ((double)1/2 * (a + b) * (a + b + 1) + b + c) * ((double)1/2 * (a + b) * (a + b + 1) + b + c + 1) + c);
}

/*!
 * \brief Utils::cantorTuple Return the cantor tuple associated with the node.
 * \param node The node and its geocoordinates.
 * \return A unique natural number based on the three inputs.
 */
unsigned long Utils::cantorTuple(Node* node)
{
	return cantorTuple(node->x(), node->y(), node->z());
}

/*!
 * \brief Utils::nodeFromPath Return the path from the final node.
 * \param node The end node of the path.
 * \return
 */
Path* Utils::pathFromNode(Node* node)
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
 * \brief Utils::isValid Return if a node is valid or not.
 * \param space The space to check
 * \param i
 * \param j
 * \param k
 * \return True is the point is in the space and point to a valid point, false otherwise
 */
bool Utils::isValid(Space3d* space, const unsigned int i, const unsigned int j, const unsigned int k)
{
	return (i > 0 && i < space->sizeX() &&
			j > 0 && j < space->sizeY() &&
			k > 0 && k < space->sizeZ() &&
			space->operator ()(i, j, k));
}

/*!
 * \brief Utils::samePaths Compare two paths.
 * \param path1 The first path to compare.
 * \param path2 The second path to compare.
 * \return True of the two path are identical, false otherwise.
 */
bool Utils::samePaths(Path* path1, Path* path2)
{
	// false if different size
	if (path1->path()->size() != path2->path()->size())
	{
		return false;
	}

	for (int i = 0; i < path1->path()->size(); i++)
	{
		if (path1->path()->at(i)->operator !=(path2->path()->at(i)))
		{
			return false;
		}
	}

	return true;
}
