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

#include <Math/Vec2.h>
#include <cmath>

namespace GL
{
	Vec2& Vec2::operator+=( const Vec2& v )
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& Vec2::operator-=( const Vec2& v )
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	const Vec2 Vec2::operator+( const Vec2& v ) const
	{
		return Vec2( x + v.x, y + v.y );
	}

	const Vec2 Vec2::operator-( const Vec2& v ) const
	{
		return Vec2( x - v.x, y - v.y );
	}

	Vec2 operator*( const Vec2& v, float n )
	{
		return Vec2( v.x * n, v.y * n );
	}

	Vec2 operator*( float n, const Vec2& v )
	{
		return Vec2( v.x * n, v.y * n );
	}

	Vec2 operator/( const Vec2& v, float n )
	{
		return Vec2( v.x/ n, v.y / n );
	}

	Vec2 operator/( float n, const Vec2& v )
	{
		return Vec2( v.x / n, v.y / n );
	}

	float Vec2::Dot( const Vec2& v ) const
	{
		return x * v.x + y * v.y;
	}

	float Vec2::Angle( const Vec2& v ) const
	{
		return acos( Dot( v ) / Length() / v.Length() );
	}

	float Vec2::LengthSqr() const
	{
		return x*x + y*y;
	}

	float Vec2::Length() const
	{
		return sqrt( x*x + y*y );
	}

	float Vec2::Distance( const Vec2& v ) const
	{
		return ( *this - v ).Length();
	}

	const Vec2 Vec2::Normal() const
	{
		return *this / Length();
	}
}