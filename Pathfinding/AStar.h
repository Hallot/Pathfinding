#ifndef ASTAR_H
#define ASTAR_H

#include "Path.h"

class Node;
class Space3d;

class AStar
{
public:
	//! Return the path from start to end using the a* algorithm.
	static Path* findPath(Node* startPosition, Node* goalPosition, Space3d* space);

protected:
	//! Return the cantor tuple associated with the 3 integers
	//! That's a bijection NxNxN -> N
	static unsigned long cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c);

	//! Return the path from the final node.
	static Path* nodeFromPath(Node* node);
};

#endif // ASTAR_H
