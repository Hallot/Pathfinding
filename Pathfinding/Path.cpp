#include "Path.h"
#include <sstream>

/*!
 * \brief Path::Path Constructor.
 */
Path::Path():
	_path(QList<Point>())
{
}

/*!
 * \brief Path::path Return the path
 * \return
 */
QList<Path::Point> Path::path()
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
	foreach (Point p, _path)
	{
		res << "[x: " << p.x << ", y: " << p.y << ", z: " << p.z << "]\n";
	}
	return res.str();
}

/*!
 * \brief Path::append Append a point to the path.
 * \param point The point to append.
 */
void Path::append(Path::Point point)
{
	_path.append(point);
}

/*!
 * \brief Path::prepend Prepend a point to the path.
 * \param point The point to prepend
 */
void Path::prepend(Path::Point point)
{
	_path.prepend(point);
}
