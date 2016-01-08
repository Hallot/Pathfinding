#ifndef SPACE3D_H
#define SPACE3D_H

class Space3d
{
public:
	//! Constructor
	Space3d(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ);
	//! Destructor
	~Space3d();

	//! Accessors
	bool& operator() (const unsigned int i, const unsigned int j, const unsigned int k);
	const bool& operator() (const unsigned int i, const unsigned int j, const unsigned int k) const;

	//! Return the space sizes
	unsigned int sizeX() const;
	unsigned int sizeY() const;
	unsigned int sizeZ() const;

	//! Set all values
	void setAll(const bool value);

protected:
	//! The array width
	const unsigned int _x;
	//! The array length
	const unsigned int _y;
	//! The array height
	const unsigned int _z;
	//! The 3d space
	bool* _space;
};

#endif // SPACE3D_H
