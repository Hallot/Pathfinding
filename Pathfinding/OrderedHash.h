#ifndef ORDEREDHASH_H
#define ORDEREDHASH_H

#include <QHash>
#include <QMultiMap>

class Node;

class OrderedHash
{
public:
	//! Constructor
	OrderedHash();

	//! Destructor
	~OrderedHash();

	//! Insert an element both in the map and hash.
	void insert(unsigned long key, Node* node);
	// Remove an element in both the map and hash.
	void remove(unsigned long key);

	//! Find in the hash.
	QHash<unsigned long, Node*>::const_iterator find(const long &key) const;
	//! Return the element with the lowest cost.
	Node* lowest();
	//! Return the element with the lowest cost and delete it.
	Node* popLowest();
	// Remove the element with the highest cost.
	void removeHighest();
	//! Return an iterator to the end of the hash.
	QHash<unsigned long, Node*>::const_iterator end() const;

	//! Return the number of elements.
	unsigned int size();
	//! If the hash contains a certain node.
	bool contains(Node* node);
	//! Return the cost of the last element, ie the one with the highest cost.
	unsigned int highestCost();

	//! If empty.
	bool empty() const;

private:
	QMultiMap<int, unsigned long>* _orderedMap;
	QHash<unsigned long, Node*>* _hash;
};

#endif // ORDEREDHASH_H
