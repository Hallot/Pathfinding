#ifndef NODE_H
#define NODE_H

class Node
{
public:
	//! Constructor
	Node(Node* parent, unsigned int x, unsigned int y, unsigned int z);
	Node(Node* parent, unsigned int x, unsigned int y, unsigned int z, double cost, double previousCost, double heuristic);

	//! Two nodes are equals if the have the same position
	bool operator==(const Node* rightHandSide) const;
	bool operator!=(const Node* rightHandSide) const;

	//! Set the value of a node to this node.
	void setValue(Node* node);

	//! Return the depth of the node.
	unsigned int depth();

	//! Getters and setters
	Node* parent() const;
	void setParent(Node* parent);

	unsigned int x() const;
	void setX(unsigned int x);

	unsigned int y() const;
	void setY(unsigned int y);

	unsigned int z() const;
	void setZ(unsigned int z);

	unsigned int cost() const;
	void setCost(unsigned int cost);

	unsigned int previousCost() const;
	void setPreviousCost(unsigned int previousCost);

	unsigned int heuristic() const;
	void setHeuristic(unsigned int heuristic);

protected:
	//! Parent node
	Node* _parent;
	//! Coordinates
	unsigned int _x;
	unsigned int _y;
	unsigned int _z;
	//! Cost of the node
	unsigned int _cost;
	//! Cost to get to the node
	unsigned int _previousCost;
	//! Heuristic cost to get to the goal
	unsigned int _heuristic;
};

#endif // NODE_H
