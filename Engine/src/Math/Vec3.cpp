/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <Math/Vec3.h>
#include <cmath>

namespace GL
{
	Vec3& Vec3::operator+=( const Vec3& v )
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3& Vec3::operator-=( const Vec3& v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	const Vec3 Vec3::operator+( const Vec3& v ) const
	{
		return Vec3( x + v.x, y + v.y, z + v.z );
	}

	const Vec3 Vec3::operator-( const Vec3& v ) const
	{
		return Vec3( x - v.x, y - v.y, z - v.z );
	}

	Vec3 operator*( const Vec3& v, float n )
	{
		return Vec3( v.x * n, v.y * n, v.z * n );
	}

	Vec3 operator*( float n, const Vec3& v )
	{
		return Vec3( v.x * n, v.y * n, v.z * n );
	}

	Vec3 operator/( const Vec3& v, float n )
	{
		return Vec3( v.x / n, v.y / n, v.z / n );
	}

	Vec3 operator/( float n, const Vec3& v )
	{
		return Vec3( v.x / n, v.y / n, v.z / n );
	}

	const Vec3 Vec3::Cross( const Vec3& v ) const
	{
		return Vec3( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
	}

	float Vec3::Dot( const Vec3& v ) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	float Vec3::Angle( const Vec3& v ) const
	{
		return acos( Dot( v ) / Length() / v.Length() );
	}

	float Vec3::LengthSqr() const
	{
		return x*x + y*y + z*z;
	}

	float Vec3::Length() const
	{
		return sqrt( x*x + y*y + z*z );
	}

	float Vec3::Distance( const Vec3& v ) const
	{
		return ( *this - v ).Length();
	}

	const Vec3 Vec3::Normal() const
	{
		return *this / Length();
	}
}