#include "Utils.h"
#include "Node.h"
#include "Space3d.h"
#include "Path.h"

/*!
 * \brief Utils::cantorTuple Return the cantor tuple associated with the 3 integers
 * https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function
 * \param a
 * \param b
 * \param c
 * \return A unique natural number based on the three inputs.
 */
unsigned long Utils::cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c)
{
	return (unsigned long)((double)1/2 * ((double)1/2 * (a + b) * (a + b + 1) + b + c) * ((double)1/2 * (a + b) * (a + b + 1) + b + c + 1) + c);
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
