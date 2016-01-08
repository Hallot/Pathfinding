#include "Space3d.h"
#include <stdio.h>

/*!
 * \brief Space3d::Space3d Create the 3d space representing the world.
 * \param sizeX The size of the space along x.
 * \param sizeY The size of the space along y.
 * \param sizeZ The size of the space along z.
 */
Space3d::Space3d(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ):
	_x(sizeX),
	_y(sizeY),
	_z(sizeZ)
{
	if (sizeX > 0 && sizeY > 0 && sizeZ > 0)
	{
		_space = new bool[sizeX * sizeY * sizeZ];
		setAll(false);
	}
	else
	{
		printf("Array's dimension must be greater than 0.\n");
	}
}

/*!
 * \brief Space3d::~Space3d Destructor
 */
Space3d::~Space3d()
{
	delete[] _space;
}

/*!
 * \brief Space3d::operator () Access the element at i, j, k.
 * \param i
 * \param j
 * \param k
 * \return The element at i, j, k.
 */
bool&Space3d::operator()(const unsigned int i, const unsigned int j, const unsigned int k)
{
	return _space[i + j*_x + k*_x*_y];
}

/*!
 * \brief Space3d::operator () Access the element at i, j, k.
 * \param i
 * \param j
 * \param k
 * \return The element at i, j, k.
 */
const bool&Space3d::operator()(const unsigned int i, const unsigned int j, const unsigned int k) const
{
	return _space[i + j*_x + k*_x*_y];
}

/*!
 * \brief Space3d::sizeX
 * \return The width of the space.
 */
unsigned int Space3d::sizeX() const
{
	return _x;
}

/*!
 * \brief Space3d::sizeY
 * \return The length of the space.
 */
unsigned int Space3d::sizeY() const
{
	return _y;
}

/*!
 * \brief Space3d::sizeZ
 * \return The height of the space.
 */
unsigned int Space3d::sizeZ() const
{
	return _z;
}

/*!
 * \brief Space3d::setAll Set all the values in the array.
 * \param value The boolean value to be set.
 */
void Space3d::setAll(const bool value)
{
	for (unsigned int i = 0; i < _x * _y * _z; i++)
	{
		_space[i] = value;
	}
}


