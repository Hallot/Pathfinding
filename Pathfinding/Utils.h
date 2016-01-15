#ifndef UTILS_H
#define UTILS_H

class Path;
class Node;
class Space3d;

class Utils
{
public:
	//! Square of the euclidian distance between two nodes
	static unsigned int squaredEuclidianDistance(Node* node1, Node* node2);

	//! Euclidian distance between two nodes.
	static unsigned int euclidianDistance(Node* node1, Node* node2);

	//! Manhattan distance between two nodes.
	static unsigned int manhattanDistance(Node* node1, Node* node2);

	//! Return the cantor tuple associated with the 3 integers
	//! That's a bijection NxNxN -> N
	static unsigned long cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c);
	static unsigned long cantorTuple(Node* node);

	//! Return the path from the final node.
	static Path* pathFromNode(Node* node);

	//! Return if a node is valid or not.
	static bool isValid(Space3d* space, const unsigned int i, const unsigned int j, const unsigned int k);

	//! Compare two paths.
	static bool samePaths(Path* path1, Path* path2);
};

#endif // UTILS_H
