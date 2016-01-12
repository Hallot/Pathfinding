#ifndef UTILS_H
#define UTILS_H

class Path;
class Node;
class Space3d;

class Utils
{
public:
	//! Return the cantor tuple associated with the 3 integers
	//! That's a bijection NxNxN -> N
	static unsigned long cantorTuple(const unsigned int a, const unsigned int b, const unsigned int c);

	//! Return the path from the final node.
	static Path* pathFromNode(Node* node);

	//! Return if a node is valid or not.
	static bool isValid(Space3d* space, const unsigned int i, const unsigned int j, const unsigned int k);
};

#endif // UTILS_H
