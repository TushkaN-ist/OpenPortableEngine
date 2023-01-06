#pragma once

#include	"Vec3.h"
#include	"Vec4.h"
#include	"Mat4.h"

namespace GL
{
	class Mat4;
	
	class Quaternion
	{
	public:							// make all members public
		float	x, y, z, w;
		
		Quaternion();
		Quaternion(float tx,float ty,float tz,float tw);
		Vec3 Euler() const;
		Vec3 Multyply(const Vec3) const;
		Quaternion Normal() const;
		Quaternion& Normalize();
		float Magnitude() const;
		static Quaternion FromDeg(const Vec3 Eular3);
		static Quaternion From(const Vec3 Eular3);
		static Quaternion From(const Vec3 v,const float angle);
		static Quaternion From(const Mat4 mat);
		static Quaternion LookAt(const Vec3 from, const Vec3 to, const Vec3 up = Vec3(0,1,0));
		
		Quaternion& operator = (const Quaternion&);
		Quaternion operator - () const;
		Quaternion operator + ( const Quaternion& q2 ) const;
		Quaternion operator - ( const Quaternion& q2 ) const;
		Quaternion operator * ( const Quaternion& q2) const;
		Quaternion operator * ( const float& f ) const;
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (const Quaternion& q);
		Quaternion& operator *= (const float& q);
		
	};
}