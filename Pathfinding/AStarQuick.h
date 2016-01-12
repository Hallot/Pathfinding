#ifndef ASTARQUICK_H
#define ASTARQUICK_H

class Path;
class Node;
class Space3d;

class AStarQuick
{
public:
	//! Return the path from start to end using the a* algorithm.
	static Path* findPath(Node* startPosition, Node* goalPosition, Space3d* space);
};

#endif // ASTARQUICK_H
