#ifndef SMASTAR_H
#define SMASTAR_H

class Path;
class Node;
class Space3d;

class SMAStar
{
public:
	//! Return the path from start to end using the a* algorithm.
	static Path* findPath(Node* startPosition, Node* goalPosition, Space3d* space, unsigned int openSetMaxSize);
};

#endif // SMASTAR_H
