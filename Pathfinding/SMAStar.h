#ifndef SMASTAR_H
#define SMASTAR_H

#include <QList>

class Path;
class Node;
class Space3d;

class SMAStar
{
public:
	//! Return the path from start to end using the SMA* algorithm.
	static Path* findPath(Node* startPosition, Node* goalPosition, Space3d* space, unsigned int maxDepth);


protected:
	//! Tree structure containing the current path.
	struct NodeTree
	{
		   Node* node;
		   NodeTree* parent;
		   QList<NodeTree*>* children;
		   unsigned int forgottenCost;
		   NodeTree* forgottenNode;

		   //! Constructor
		   NodeTree(Node* node);
		   NodeTree(Node* node, NodeTree* parent);
		   //! Return the nodeTree associated with a node.
		   static void find(Node* node, NodeTree* nodeTree, NodeTree* result);
		   //! Add child
		   void addChild(NodeTree* child, NodeTree* parent);
		   void addChild(Node* child, NodeTree* parent);
		   //! Remove a leaf.
		   void removeLeaf(NodeTree* leaf);
		   //! Update cost based on minimum of its children starting from a leaf.
		   void updateCost(NodeTree* node);
		   //! Return the depth of a given nodeTree in the tree.
		   unsigned int depth();
		   //! Find the shallowest node with the highest cost.
		   NodeTree* findShallowestHighestCost();
	};
};

#endif // SMASTAR_H
