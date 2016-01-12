#ifndef ASTAR_H
#define ASTAR_H

class Node;
class Space3d;
class Path;

class AStar
{
public:
	//! Return the path from start to end using the a* algorithm.
	static Path* findPath(Node* startPosition, Node* goalPosition, Space3d* space);

};

#endif // ASTAR_H
