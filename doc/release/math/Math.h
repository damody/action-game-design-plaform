#pragma once
/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <cassert>
#include <cmath>
#include <algorithm>

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef __int64		int64;
typedef unsigned __int64	uint64;

typedef std::vector<bool>	bool_vector;
typedef std::vector<uchar>	uchar_vector;
typedef std::vector<ushort>	ushort_vector;
typedef std::vector<uint>	uint_vector;
typedef std::vector<double>	double_vector;
typedef std::vector<double_vector>	double_vector2d;
typedef std::vector<float>	float_vector;
typedef std::vector<float_vector>	float_vector2d;
typedef std::vector<int>	int_vector;
typedef std::vector<std::vector<int> >	int_vector2d;
typedef std::vector<int64>	int64_vector;
typedef std::vector<std::vector<int64> > int64_vector2d;

class Vector2;
class Vector3;
class Vector4;
class Matrix3;
class Matrix4;
class Ray;
class AxisAlignedBox;
class Quaternion;
class Sphere;
class Plane;
class Degree;
class Radian;

template <class VEC>
struct VLine
{
	union
	{
		struct
		{
			VEC begin, end;
		};
		struct
		{
			VEC from, to;
		};
	};
	VEC v[2];

	VLine(){}
	VLine(const VEC& v1, const VEC& v2)
	{
		begin = v1;
		end = v2;
	}
};

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
typedef Matrix3 Mat3;
typedef Matrix4 Mat4;
typedef Degree Degree;
typedef Radian Radian;
typedef Quaternion Quaternion;
typedef VLine<Vec2> Vec2Line;
typedef VLine<Vec3> Vec3Line;
typedef std::vector<Vec2Line> Vec2Lines;
typedef std::vector<Vec3Line> Vec3Lines;
typedef std::vector<Vec2> Vec2s;
typedef std::vector<Vec3> Vec3s;
typedef std::vector<Vec4> Vec4s;

/** Wrapper class which indicates a given angle value is in Radians.
@remarks
Radian values are interchangeable with Degree values, and conversions
will be done automatically between them.
*/

class Radian
{
	double mRad;

public:
	explicit Radian ( double r=0 ) : mRad(r) {}
	Radian ( const Degree& d );
	Radian& operator = ( const double& f ) { mRad = f; return *this; }
	Radian& operator = ( const Radian& r ) { mRad = r.mRad; return *this; }
	Radian& operator = ( const Degree& d );
	Radian( float x, float y )
	{
		mRad = atan2(x, y);
	}

	double valueDegrees() const; // see bottom of this file
	double valueRadians() const { return mRad; }
	double valueAngleUnits() const;

	const Radian& operator + () const { return *this; }
	Radian operator + ( const Radian& r ) const { return Radian ( mRad + r.mRad ); }
	Radian operator + ( const Degree& d ) const;
	Radian& operator += ( const Radian& r ) { mRad += r.mRad; return *this; }
	Radian& operator += ( const Degree& d );
	Radian operator - () const { return Radian(-mRad); }
	Radian operator - ( const Radian& r ) const { return Radian ( mRad - r.mRad ); }
	Radian operator - ( const Degree& d ) const;
	Radian& operator -= ( const Radian& r ) { mRad -= r.mRad; return *this; }
	Radian& operator -= ( const Degree& d );
	Radian operator * ( double f ) const { return Radian ( mRad * f ); }
	Radian operator * ( const Radian& f ) const { return Radian ( mRad * f.mRad ); }
	Radian& operator *= ( double f ) { mRad *= f; return *this; }
	Radian operator / ( double f ) const { return Radian ( mRad / f ); }
	Radian& operator /= ( double f ) { mRad /= f; return *this; }

	bool operator <  ( const Radian& r ) const { return mRad <  r.mRad; }
	bool operator <= ( const Radian& r ) const { return mRad <= r.mRad; }
	bool operator == ( const Radian& r ) const { return mRad == r.mRad; }
	bool operator != ( const Radian& r ) const { return mRad != r.mRad; }
	bool operator >= ( const Radian& r ) const { return mRad >= r.mRad; }
	bool operator >  ( const Radian& r ) const { return mRad >  r.mRad; }


	inline friend std::ostream& operator <<
		( std::ostream& o, const Radian& v )
	{
		o << "Radian(" << v.valueRadians() << ")";
		return o;
	}
};

/** Wrapper class which indicates a given angle value is in Degrees.
@remarks
Degree values are interchangeable with Radian values, and conversions
will be done automatically between them.
*/
class Degree
{
	double mDeg; // if you get an error here - make sure to define/typedef 'Real' first

public:
	explicit Degree ( double d=0 ) : mDeg(d) {}
	Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
	Degree& operator = ( const double& f ) { mDeg = f; return *this; }
	Degree& operator = ( const Degree& d ) { mDeg = d.mDeg; return *this; }
	Degree& operator = ( const Radian& r ) { mDeg = r.valueDegrees(); return *this; }
	Degree( float x, float y )
	{
		*this = Radian(atan2(x, y));
	}
	double valueDegrees() const { return mDeg; }
	double valueRadians() const; // see bottom of this file
	double valueAngleUnits() const;

	const Degree& operator + () const { return *this; }
	Degree operator + ( const Degree& d ) const { return Degree ( mDeg + d.mDeg ); }
	Degree operator + ( const Radian& r ) const { return Degree ( mDeg + r.valueDegrees() ); }
	Degree& operator += ( const Degree& d ) { mDeg += d.mDeg; return *this; }
	Degree& operator += ( const Radian& r ) { mDeg += r.valueDegrees(); return *this; }
	Degree operator - () const { return Degree(-mDeg); }
	Degree operator - ( const Degree& d ) const { return Degree ( mDeg - d.mDeg ); }
	Degree operator - ( const Radian& r ) const { return Degree ( mDeg - r.valueDegrees() ); }
	Degree& operator -= ( const Degree& d ) { mDeg -= d.mDeg; return *this; }
	Degree& operator -= ( const Radian& r ) { mDeg -= r.valueDegrees(); return *this; }
	Degree operator * ( double f ) const { return Degree ( mDeg * f ); }
	Degree operator * ( const Degree& f ) const { return Degree ( mDeg * f.mDeg ); }
	Degree& operator *= ( double f ) { mDeg *= f; return *this; }
	Degree operator / ( double f ) const { return Degree ( mDeg / f ); }
	Degree& operator /= ( double f ) { mDeg /= f; return *this; }

	bool operator <  ( const Degree& d ) const { return mDeg <  d.mDeg; }
	bool operator <= ( const Degree& d ) const { return mDeg <= d.mDeg; }
	bool operator == ( const Degree& d ) const { return mDeg == d.mDeg; }
	bool operator != ( const Degree& d ) const { return mDeg != d.mDeg; }
	bool operator >= ( const Degree& d ) const { return mDeg >= d.mDeg; }
	bool operator >  ( const Degree& d ) const { return mDeg >  d.mDeg; }

	inline friend std::ostream& operator <<
		( std::ostream& o, const Degree& v )
	{
		o << "Degree(" << v.valueDegrees() << ")";
		return o;
	}
};

/** Wrapper class which identifies a value as the currently default angle 
type, as defined by Math::setAngleUnit.
@remarks
Angle values will be automatically converted between radians and degrees,
as appropriate.
*/
class Angle
{
	double mAngle;
public:
	explicit Angle ( double angle ) : mAngle(angle) {}
	operator Radian() const;
	operator Degree() const;
};

// these functions could not be defined within the class definition of class
// Radian because they required class Degree to be defined
inline Radian::Radian ( const Degree& d ) : mRad(d.valueRadians()) {
}
inline Radian& Radian::operator = ( const Degree& d ) {
	mRad = d.valueRadians(); return *this;
}
inline Radian Radian::operator + ( const Degree& d ) const {
	return Radian ( mRad + d.valueRadians() );
}
inline Radian& Radian::operator += ( const Degree& d ) {
	mRad += d.valueRadians();
	return *this;
}
inline Radian Radian::operator - ( const Degree& d ) const {
	return Radian ( mRad - d.valueRadians() );
}
inline Radian& Radian::operator -= ( const Degree& d ) {
	mRad -= d.valueRadians();
	return *this;
}

/** Class to provide access to common mathematical functions.
@remarks
Most of the maths functions are aliased versions of the C runtime
library functions. They are aliased here to provide future
optimisation opportunities, either from faster RTLs or custom
math approximations.
@note
<br>This is based on MgcMath.h from
<a href="http://www.geometrictools.com/">Wild Magic</a>.
*/
class Math 
{
public:
	/** The angular units used by the API. This functionality is now deprecated in favor
	of discreet angular unit types ( see Degree and Radian above ). The only place
	this functionality is actually still used is when parsing files. Search for
	usage of the Angle class for those instances
	*/
	enum AngleUnit
	{
		AU_DEGREE,
		AU_RADIAN
	};

protected:
	// angle units used by the api
	static AngleUnit msAngleUnit;

	/// Size of the trig tables as determined by constructor.
	static int mTrigTableSize;

	/// Radian -> index factor value ( mTrigTableSize / 2 * PI )
	static double mTrigTableFactor;
	static double* mSinTable;
	static double* mTanTable;

	/** Private function to build trig tables.
	*/
	void buildTrigTables();

	static double SinTable (double fValue);
	static double TanTable (double fValue);
public:
	/** Default constructor.
	@param
	trigTableSize Optional parameter to set the size of the
	tables used to implement Sin, Cos, Tan
	*/
	Math(unsigned int trigTableSize = 4096);

	/** Default destructor.
	*/
	~Math();

	static inline int IAbs (int iValue) { return ( iValue >= 0 ? iValue : -iValue ); }
	static inline int ICeil (double fValue) { return int(ceil(fValue)); }
	static inline int IFloor (double fValue) { return int(floor(fValue)); }
	static int ISign (int iValue);

	static inline double Abs (double fValue) { return double(fabs(fValue)); }
	static inline Degree Abs (const Degree& dValue) { return Degree(fabs(dValue.valueDegrees())); }
	static inline Radian Abs (const Radian& rValue) { return Radian(fabs(rValue.valueRadians())); }
	static Radian ACos (double fValue);
	static Radian ASin (double fValue);
	static inline Radian ATan (double fValue) { return Radian(atan(fValue)); }
	static inline Radian ATan2 (double fY, double fX) { return Radian(atan2(fY,fX)); }
	static inline double Ceil (double fValue) { return double(ceil(fValue)); }
	static inline bool isNaN(double f)
	{
		// std::isnan() is C99, not supported by all compilers
		// However NaN always fails this next test, no other number does.
		return f != f;
	}

	/** Cosine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Cos (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? double(cos(fValue.valueRadians())) : SinTable(fValue.valueRadians() + HALF_PI);
	}
	/** Cosine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Cos (double fValue, bool useTables = false) {
		return (!useTables) ? double(cos(fValue)) : SinTable(fValue + HALF_PI);
	}

	static inline double Exp (double fValue) { return double(exp(fValue)); }

	static inline double Floor (double fValue) { return double(floor(fValue)); }

	static inline double Log (double fValue) { return double(log(fValue)); }

	/// Stored value of log(2) for frequent use
	static const double LOG2;

	static inline double Log2 (double fValue) { return double(log(fValue)/LOG2); }

	static inline double LogN (double base, double fValue) { return double(log(fValue)/log(base)); }

	static inline double Pow (double fBase, double fExponent) { return double(pow(fBase,fExponent)); }

	static double Sign (double fValue);
	static inline Radian Sign ( const Radian& rValue )
	{
		return Radian(Sign(rValue.valueRadians()));
	}
	static inline Degree Sign ( const Degree& dValue )
	{
		return Degree(Sign(dValue.valueDegrees()));
	}
	/** Sine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Sin (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? double(sin(fValue.valueRadians())) : SinTable(fValue.valueRadians());
	}
	/** Sine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Sin (double fValue, bool useTables = false) {
		return (!useTables) ? double(sin(fValue)) : SinTable(fValue);
	}

	static inline double Sqr (double fValue) { return fValue*fValue; }

	static inline double Sqrt (double fValue) { return double(sqrt(fValue)); }

	static inline Radian Sqrt (const Radian& fValue) { return Radian(sqrt(fValue.valueRadians())); }

	static inline Degree Sqrt (const Degree& fValue) { return Degree(sqrt(fValue.valueDegrees())); }

	/** Inverse square root i.e. 1 / Sqrt(x), good for vector
	normalisation.
	*/
	static double InvSqrt(double fValue)
	{
		return 1./sqrt(fValue);
	}

	static double UnitRandom ();  // in [0,1]

	static double RangeRandom (double fLow, double fHigh);  // in [fLow,fHigh]

	static double SymmetricRandom ();  // in [-1,1]

	/** Tangent function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Tan (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? double(tan(fValue.valueRadians())) : TanTable(fValue.valueRadians());
	}
	/** Tangent function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline double Tan (double fValue, bool useTables = false) {
		return (!useTables) ? double(tan(fValue)) : TanTable(fValue);
	}

	static inline double DegreesToRadians(double degrees) { return degrees * fDeg2Rad; }
	static inline double RadiansToDegrees(double radians) { return radians * fRad2Deg; }

	/** These functions used to set the assumed angle units (radians or degrees) 
	expected when using the Angle type.
	@par
	You can set this directly after creating a new Root, and also before/after resource creation,
	depending on whether you want the change to affect resource files.
	*/
	static void setAngleUnit(AngleUnit unit);
	/** Get the unit being used for angles. */
	static AngleUnit getAngleUnit(void);

	/** Convert from the current AngleUnit to radians. */
	static double AngleUnitsToRadians(double units);
	/** Convert from radians to the current AngleUnit . */
	static double RadiansToAngleUnits(double radians);
	/** Convert from the current AngleUnit to degrees. */
	static double AngleUnitsToDegrees(double units);
	/** Convert from degrees to the current AngleUnit. */
	static double DegreesToAngleUnits(double degrees);

	/** Checks whether a given point is inside a triangle, in a
	2-dimensional (Cartesian) space.
	@remarks
	The vertices of the triangle must be given in either
	trigonometrical (anticlockwise) or inverse trigonometrical
	(clockwise) order.
	@param
	p The point.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@returns
	If the point resides in the triangle, <b>true</b> is
	returned.
	@par
	If the point is outside the triangle, <b>false</b> is
	returned.
	*/
	static bool pointInTri2D(const Vector2& p, const Vector2& a, 
		const Vector2& b, const Vector2& c);

	/** Checks whether a given 3D point is inside a triangle.
	@remarks
	The vertices of the triangle must be given in either
	trigonometrical (anticlockwise) or inverse trigonometrical
	(clockwise) order, and the point must be guaranteed to be in the
	same plane as the triangle
	@param
	p The point.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param 
	normal The triangle plane's normal (passed in rather than calculated
	on demand since the caller may already have it)
	@returns
	If the point resides in the triangle, <b>true</b> is
	returned.
	@par
	If the point is outside the triangle, <b>false</b> is
	returned.
	*/
	static bool pointInTri3D(const Vector3& p, const Vector3& a, 
		const Vector3& b, const Vector3& c, const Vector3& normal);
	/** Ray / plane intersection, returns boolean result and distance. */
	static std::pair<bool, double> intersects(const Ray& ray, const Plane& plane);

	/** Ray / sphere intersection, returns boolean result and distance. */
	static std::pair<bool, double> intersects(const Ray& ray, const Sphere& sphere, 
		bool discardInside = true);

	/** Ray / box intersection, returns boolean result and distance. */
	static std::pair<bool, double> intersects(const Ray& ray, const AxisAlignedBox& box);

	/** Ray / box intersection, returns boolean result and two intersection distance.
	@param
	ray The ray.
	@param
	box The box.
	@param
	d1 A real pointer to retrieve the near intersection distance
	from the ray origin, maybe <b>null</b> which means don't care
	about the near intersection distance.
	@param
	d2 A real pointer to retrieve the far intersection distance
	from the ray origin, maybe <b>null</b> which means don't care
	about the far intersection distance.
	@returns
	If the ray is intersects the box, <b>true</b> is returned, and
	the near intersection distance is return by <i>d1</i>, the
	far intersection distance is return by <i>d2</i>. Guarantee
	<b>0</b> <= <i>d1</i> <= <i>d2</i>.
	@par
	If the ray isn't intersects the box, <b>false</b> is returned, and
	<i>d1</i> and <i>d2</i> is unmodified.
	*/
	static bool intersects(const Ray& ray, const AxisAlignedBox& box,
		double* d1, double* d2);

	/** Ray / triangle intersection, returns boolean result and distance.
	@param
	ray The ray.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param 
	normal The triangle plane's normal (passed in rather than calculated
	on demand since the caller may already have it), doesn't need
	normalised since we don't care.
	@param
	positiveSide Intersect with "positive side" of the triangle
	@param
	negativeSide Intersect with "negative side" of the triangle
	@returns
	If the ray is intersects the triangle, a pair of <b>true</b> and the
	distance between intersection point and ray origin returned.
	@par
	If the ray isn't intersects the triangle, a pair of <b>false</b> and
	<b>0</b> returned.
	*/
	static std::pair<bool, double> intersects(const Ray& ray, const Vector3& a,
		const Vector3& b, const Vector3& c, const Vector3& normal,
		bool positiveSide = true, bool negativeSide = true);

	/** Ray / triangle intersection, returns boolean result and distance.
	@param
	ray The ray.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param
	positiveSide Intersect with "positive side" of the triangle
	@param
	negativeSide Intersect with "negative side" of the triangle
	@returns
	If the ray is intersects the triangle, a pair of <b>true</b> and the
	distance between intersection point and ray origin returned.
	@par
	If the ray isn't intersects the triangle, a pair of <b>false</b> and
	<b>0</b> returned.
	*/
	static std::pair<bool, double> intersects(const Ray& ray, const Vector3& a,
		const Vector3& b, const Vector3& c,
		bool positiveSide = true, bool negativeSide = true);

	/** Sphere / box intersection test. */
	static bool intersects(const Sphere& sphere, const AxisAlignedBox& box);

	/** Plane / box intersection test. */
	static bool intersects(const Plane& plane, const AxisAlignedBox& box);

	/** Ray / convex plane list intersection test. 
	@param ray The ray to test with
	@param plaeList List of planes which form a convex volume
	@param normalIsOutside Does the normal point outside the volume
	*/
	static std::pair<bool, double> intersects(
		const Ray& ray, const std::vector<Plane>& planeList, 
		bool normalIsOutside);
	/** Ray / convex plane list intersection test. 
	@param ray The ray to test with
	@param plaeList List of planes which form a convex volume
	@param normalIsOutside Does the normal point outside the volume
	*/
	static std::pair<bool, double> intersects(
		const Ray& ray, const std::list<Plane>& planeList, 
		bool normalIsOutside);

	/** Sphere / plane intersection test. 
	@remarks NB just do a plane.getDistance(sphere.getCenter()) for more detail!
	*/
	static bool intersects(const Sphere& sphere, const Plane& plane);

	/** Compare 2 reals, using tolerance for inaccuracies.
	*/
	static bool RealEqual(double a, double b,
		double tolerance = std::numeric_limits<double>::epsilon());

	/** Calculates the tangent space vector for a given set of positions / texture coords. */
	static Vector3 calculateTangentSpaceVector(
		const Vector3& position1, const Vector3& position2, const Vector3& position3,
		double u1, double v1, double u2, double v2, double u3, double v3);

	/** Build a reflection matrix for the passed in plane. */
	static Matrix4 buildReflectionMatrix(const Plane& p);
	/** Calculate a face normal, including the w component which is the offset from the origin. */
	static Vector4 calculateFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	/** Calculate a face normal, no w-information. */
	static Vector3 calculateBasicFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	/** Calculate a face normal without normalize, including the w component which is the offset from the origin. */
	static Vector4 calculateFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	/** Calculate a face normal without normalize, no w-information. */
	static Vector3 calculateBasicFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	/** Generates a value based on the Gaussian (normal) distribution function
	with the given offset and scale parameters.
	*/
	static double gaussianDistribution(double x, double offset = 0.0f, double scale = 1.0f);

	/** Clamp a value within an inclusive range. */
	template <typename T>
	static T Clamp(T val, T minval, T maxval)
	{
		assert (minval < maxval && "Invalid clamp range");
		return __max(__min(val, maxval), minval);
	}

	static Matrix4 makeViewMatrix(const Vector3& position, const Quaternion& orientation, 
		const Matrix4* reflectMatrix = 0);

	/** Get a bounding radius value from a bounding box. */
	static double boundingRadiusFromAABB(const AxisAlignedBox& aabb);



	static const double POS_INFINITY;
	static const double NEG_INFINITY;
	static const double PI;
	static const double TWO_PI;
	static const double HALF_PI;
	static const double fDeg2Rad;
	static const double fRad2Deg;

};

// these functions must be defined down here, because they rely on the
// angle unit conversion functions in class Math:

inline double Radian::valueDegrees() const
{
	return Math::RadiansToDegrees ( mRad );
}

inline double Radian::valueAngleUnits() const
{
	return Math::RadiansToAngleUnits ( mRad );
}

inline double Degree::valueRadians() const
{
	return Math::DegreesToRadians ( mDeg );
}

inline double Degree::valueAngleUnits() const
{
	return Math::DegreesToAngleUnits ( mDeg );
}

inline Angle::operator Radian() const
{
	return Radian(Math::AngleUnitsToRadians(mAngle));
}

inline Angle::operator Degree() const
{
	return Degree(Math::AngleUnitsToDegrees(mAngle));
}

inline Radian operator * ( double a, const Radian& b )
{
	return Radian ( a * b.valueRadians() );
}

inline Radian operator / ( double a, const Radian& b )
{
	return Radian ( a / b.valueRadians() );
}

inline Degree operator * ( double a, const Degree& b )
{
	return Degree ( a * b.valueDegrees() );
}

inline Degree operator / ( double a, const Degree& b )
{
	return Degree ( a / b.valueDegrees() );
}
