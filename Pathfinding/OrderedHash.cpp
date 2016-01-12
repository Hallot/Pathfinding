#include "OrderedHash.h"
#include "Node.h"
#include <iostream>

/*!
 * \brief OrderedHash::OrderedHash A hash and an ordered map to store order
 */
OrderedHash::OrderedHash() :
	_orderedMap(new QMultiMap<int, unsigned long>()),
	_hash(new QHash<unsigned long, Node*>())
{
}

/*!
 * \brief OrderedHash::~OrderedHash Destructor
 */
OrderedHash::~OrderedHash()
{
	_orderedMap->clear();
	delete _orderedMap;
	qDeleteAll(_hash->begin(), _hash->end());
	_hash->clear();
	delete _hash;
}

/*!
 * \brief OrderedHash::insert Insert an element both in the map and hash.
 * \param key The key of the element to add.
 * \param node The element to add.
 */
void OrderedHash::insert(unsigned long key, Node* node)
{
	_orderedMap->insert(node->cost(), key);
	_hash->insert(key, node);
}

/*!
 * \brief OrderedHash::remove Remove an element in both the map and hash.
 * \param key The key of the element to remove.
 */
void OrderedHash::remove(unsigned long key)
{
	// always erase the first element in the map
	_orderedMap->erase(_orderedMap->begin());
	_hash->remove(key);
}

/*!
 * \brief OrderedHash::find Find in the hash.
 * \param key The key to find
 * \return
 */
QHash<unsigned long, Node*>::const_iterator OrderedHash::find(const long& key) const
{
	return _hash->find(key);
}

/*!
 * \brief OrderedHash::popLowest Return the element with the lowest cost and delete it.
 * \return The value
 */
Node* OrderedHash::popLowest()
{
	// find the element with lowest cost
	auto it = _orderedMap->begin();
	// find the associated node in the hash
	Node* node = _hash->find(it.value()).value();
	// delete it in both containers
	_hash->remove(it.value());
	_orderedMap->erase(it);
	// and finally return it
	return node;
}

/*!
 * \brief OrderedHash::removeHighest Remove the element with the highest cost.
 */
void OrderedHash::removeHighest()
{
	// find the element with lowest cost
	auto it = _orderedMap->end();
	// end is beyond the latest element
	--it;
	// delete it in both containers
	delete _hash->find(it.value()).value();
	_hash->remove(it.value());
	_orderedMap->erase(it);
}

/*!
 * \brief OrderedHash::end Return an iterator to the end of the hash.
 * \return
 */
QHash<unsigned long, Node*>::const_iterator OrderedHash::end() const
{
	return _hash->end();
}

/*!
 * \brief OrderedHash::size Return the number of elements.
 * \return
 */
unsigned int OrderedHash::size()
{
	return _hash->size();
}

/*!
 * \brief OrderedHash::highestCost Return the cost of the last element, ie the one with the highest cost.
 * \return
 */
unsigned int OrderedHash::highestCost()
{
	return _orderedMap->lastKey();
}

/*!
 * \brief OrderedHash::empty If empty
 * \return True if no element, false otherwise.
 */
bool OrderedHash::empty() const
{
	return _hash->empty();
}

