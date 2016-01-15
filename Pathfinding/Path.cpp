#include "Path.h"
#include <sstream>

/*!
 * \brief Path::Path Constructor.
 */
Path::Path():
	_path(new QList<Point*>())
{
}

/*!
 * \brief Path::~Path Destructor.
 */
Path::~Path()
{
	qDeleteAll(*_path);
	delete _path;
}

/*!
 * \brief Path::path Return the path
 * \return
 */
QList<Path::Point*>* Path::path()
{
	return _path;
}

/*!
 * \brief Path::toString Convert the path to a string.
 * \return The string representing the path.
 */
std::string Path::toString()
{
	std::stringstream res;
	foreach (Point* p, *_path)
	{
		res << "[x: " << p->x << ", y: " << p->y << ", z: " << p->z << "]\n";
	}
	return res.str();
}

/*!
 * \brief Path::append Append a point to the path.
 * \param point The point to append.
 */
void Path::append(Point* point)
{
	_path->append(point);
}

/*!
 * \brief Path::prepend Prepend a point to the path.
 * \param point The point to prepend
 */
void Path::prepend(Point* point)
{
	_path->prepend(point);
}

/*!
 * \brief Path::Point::Point Point constructor.
 * \param x
 * \param y
 * \param z
 */
Path::Point::Point(const unsigned int &x, const unsigned int &y, const unsigned int &z):
	x(x),
	y(y),
	z(z)
{

}

bool Path::Point::operator==(const Path::Point* rightHandSide) const
{
	return (this->x == rightHandSide->x) && (this->y == rightHandSide->y) && (this->z == rightHandSide->z);
}

bool Path::Point::operator!=(const Path::Point* rightHandSide) const
{
	return !(*this == rightHandSide);
}
