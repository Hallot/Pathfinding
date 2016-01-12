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

	//! Square of the euclidian distance between two nodes
	static double squaredEuclidianDistance(Node* node1, Node* node2);

	//! Euclidian distance between two nodes.
	static double euclidianDistance(Node* node1, Node* node2);

	//! Manhattan distance between two nodes.
	static double manhattanDistance(Node* node1, Node* node2);

	//! Set the value of a node to this node.
	void setValue(Node* node);

	//! Getters and setters
	Node* parent() const;
	void setParent(Node* parent);

	unsigned int x() const;
	void setX(unsigned int x);

	unsigned int y() const;
	void setY(unsigned int y);

	unsigned int z() const;
	void setZ(unsigned int z);

	double cost() const;
	void setCost(double cost);

	double previousCost() const;
	void setPreviousCost(double previousCost);

	double heuristic() const;
	void setHeuristic(double heuristic);

protected:
	//! Parent node
	Node* _parent;
	//! Coordinates
	unsigned int _x;
	unsigned int _y;
	unsigned int _z;
	//! Cost of the node
	double _cost;
	//! Cost to get to the node
	double _previousCost;
	//! Heuristic cost to get to the goal
	double _heuristic;

};

#endif // NODE_H
