#ifndef PATH_H
#define PATH_H

#include <qlist.h>
#include <string>

class Path
{
public:
	//! The structure for the coordinates of a point.
	struct Point
	{
		unsigned int x;
		unsigned int y;
		unsigned int z;
	};

	//! Constructor.
	Path();

	//! Return the path.
	QList<Point> path();

	//! Append a point.
	void append(Point point);
	//! Prepend a point.
	void prepend(Point point);

	//! To string.
	std::string toString();

private:
	QList<Point> _path;
};

#endif // PATH_H
