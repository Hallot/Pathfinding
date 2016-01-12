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
	//! Return the element with the lowest cost and delete it.
	Node* popLowest() const;
	//! Return an iterator to the end of the hash.
	QHash<unsigned long, Node*>::const_iterator end() const;

	//! If empty.
	bool empty() const;

private:
	QMultiMap<int, unsigned long>* _orderedMap;
	QHash<unsigned long, Node*>* _hash;
};

#endif // ORDEREDHASH_H
