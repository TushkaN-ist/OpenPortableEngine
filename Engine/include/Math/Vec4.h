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

#pragma once

#ifndef OOGL_VEC4_HPP
#define OOGL_VEC4_HPP

#include "Vec3.h"

namespace GL
{
	/*
		4D vector
	*/
	class Vec4
	{
	public:
		Vec4( float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f ) : x( X ), y( Y ), z( Z ), w( W ) {}
		Vec4( const Vec3& v, float W = 1.0f ) : x( v.x ), y( v.y ), z( v.z ), w( W ) {}

		Vec4& operator+=( const Vec4& v );
		Vec4& operator-=( const Vec4& v );

		const Vec4 operator+( const Vec4& v ) const;
		const Vec4 operator-( const Vec4& v ) const;

		friend Vec4 operator*( const Vec4& v, float n );
		friend Vec4 operator*( float n, const Vec4& v );

		friend Vec4 operator/( const Vec4& v, float n );
		friend Vec4 operator/( float n, const Vec4& v );

		float x, y, z, w;
	};
}

#endif