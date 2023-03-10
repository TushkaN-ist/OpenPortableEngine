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

#include <Math/Mat4.h>
#include <cmath>

namespace GL
{
	Mat4::Mat4()
	{
		*this = Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Mat4::Mat4( float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33 )
	{
		m[0] = v00; m[4] = v01; m[8]  = v02; m[12] = v03;
		m[1] = v10; m[5] = v11; m[9]  = v12; m[13] = v13;
		m[2] = v20; m[6] = v21; m[10] = v22; m[14] = v23;
		m[3] = v30; m[7] = v31; m[11] = v32; m[15] = v33;
	}

	const Mat4 Mat4::operator*( const Mat4& mat ) const
	{
		return Mat4(
			m[0]*mat.m[0]+m[4]*mat.m[1]+m[8]*mat.m[2]+m[12]*mat.m[3], m[0]*mat.m[4]+m[4]*mat.m[5]+m[8]*mat.m[6]+m[12]*mat.m[7], m[0]*mat.m[8]+m[4]*mat.m[9]+m[8]*mat.m[10]+m[12]*mat.m[11], m[0]*mat.m[12]+m[4]*mat.m[13]+m[8]*mat.m[14]+m[12]*mat.m[15],
			m[1]*mat.m[0]+m[5]*mat.m[1]+m[9]*mat.m[2]+m[13]*mat.m[3], m[1]*mat.m[4]+m[5]*mat.m[5]+m[9]*mat.m[6]+m[13]*mat.m[7], m[1]*mat.m[8]+m[5]*mat.m[9]+m[9]*mat.m[10]+m[13]*mat.m[11], m[1]*mat.m[12]+m[5]*mat.m[13]+m[9]*mat.m[14]+m[13]*mat.m[15],
			m[2]*mat.m[0]+m[6]*mat.m[1]+m[10]*mat.m[2]+m[14]*mat.m[3], m[2]*mat.m[4]+m[6]*mat.m[5]+m[10]*mat.m[6]+m[14]*mat.m[7], m[2]*mat.m[8]+m[6]*mat.m[9]+m[10]*mat.m[10]+m[14]*mat.m[11], m[2]*mat.m[12]+m[6]*mat.m[13]+m[10]*mat.m[14]+m[14]*mat.m[15],
			m[3]*mat.m[0]+m[7]*mat.m[1]+m[11]*mat.m[2]+m[15]*mat.m[3], m[3]*mat.m[4]+m[7]*mat.m[5]+m[11]*mat.m[6]+m[15]*mat.m[7], m[3]*mat.m[8]+m[7]*mat.m[9]+m[11]*mat.m[10]+m[15]*mat.m[11], m[3]*mat.m[12]+m[7]*mat.m[13]+m[11]*mat.m[14]+m[15]*mat.m[15]
		);
	}

	const Vec3 Mat4::operator*( const Vec3& v ) const
	{
		return Vec3(
			m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12],
			m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13],
			m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]
		);
	}

	const Vec4 Mat4::operator*( const Vec4& v ) const
	{
		return Vec4(
			m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12]*v.w,
			m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13]*v.w,
			m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w,
			m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w
		);
	}

	Mat4 Mat4::Identity( )
	{
		return Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
	
	Mat4& Mat4::Translate( const Vec3& v )
	{
		return *this = *this * Mat4(
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::Scale( const Vec3& v )
	{
		return *this = *this * Mat4(
			v.x, 0, 0, 0,
			0, v.y, 0, 0,
			0, 0, v.z, 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::Scale( const float& x, const float& y, const float& z  )
	{
		return *this = *this * Mat4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateX( float ang )
	{
		return *this = *this * Mat4(
			1, 0, 0, 0,
			0, cos( ang ), -sin( ang ), 0,
			0, sin( ang ), cos( ang ), 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateY( float ang )
	{
		return *this = *this * Mat4(
			cos( ang ), 0, sin( ang ), 0,
			0, 1, 0, 0,
			-sin( ang ), 0, cos( ang ), 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateZ( float ang )
	{
		return *this = *this * Mat4(
			cos( ang ), -sin( ang ), 0, 0,
			sin( ang ), cos( ang ), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::Rotate( const Vec3& axis, float ang )
	{
		float s = sin( ang );
		float c = cos( ang );
		float t = 1 - c;
		Vec3 a = axis.Normal();

		return *this = *this * Mat4(
			a.x * a.x * t + c, a.x * a.y * t - a.z * s, a.x * a.z * t + a.y * s, 0,
			a.y * a.x * t + a.z * s, a.y * a.y * t + c, a.y * a.z * t - a.x * s, 0,
			a.z * a.x * t - a.y * s, a.z * a.y * t + a.x * s, a.z * a.z * t + c, 0,
			0, 0, 0, 1
		);
	}
	
	Mat4& Mat4::Rotate( const Quaternion& rotate )
	{
		return *this = *this * Mat4::FromR(rotate);
	}

	Mat4 Mat4::Transpose() const
	{
		Mat4 res;

		res.m[0] = m[0];
		res.m[1] = m[4];
		res.m[2] = m[8];
		res.m[3] = m[12];

		res.m[4] = m[1];
		res.m[5] = m[5];
		res.m[6] = m[9];
		res.m[7] = m[13];

		res.m[8] = m[2];
		res.m[9] = m[6];
		res.m[10] = m[10];
		res.m[11] = m[14];

		res.m[12] = m[3];
		res.m[13] = m[7];
		res.m[14] = m[11];
		res.m[15] = m[15];

		return res;
	}

	float Mat4::Determinant() const
	{
		return m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] - m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
               m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] - m[12] * m[9] * m[2] * m[7] + m[8] * m[13] * m[2] * m[7] +
               m[12] * m[1] * m[10] * m[7] - m[0] * m[13] * m[10] * m[7] - m[8] * m[1] * m[14] * m[7] + m[0] * m[9] * m[14] * m[7] +
               m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] - m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
               m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] - m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
               m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] - m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
	}

	Mat4 Mat4::Inverse() const
	{
		float det = Determinant();

		Mat4 res;

		float t0 = m[0] * m[5] - m[1] * m[4];
        float t1 = m[0] * m[6] - m[2] * m[4];
        float t2 = m[0] * m[7] - m[3] * m[4];
        float t3 = m[1] * m[6] - m[2] * m[5];
        float t4 = m[1] * m[7] - m[3] * m[5];
        float t5 = m[2] * m[7] - m[3] * m[6];
        float t6 = m[8] * m[13] - m[9] * m[12];
        float t7 = m[8] * m[14] - m[10] * m[12];
        float t8 = m[8] * m[15] - m[11] * m[12];
        float t9 = m[9] * m[14] - m[10] * m[13];
        float t10 = m[9] * m[15] - m[11] * m[13];
        float t11 = m[10] * m[15] - m[11] * m[14];

		res.m[0] = ( m[5] * t11 - m[6] * t10 + m[7] * t9 ) / det;
        res.m[1] = ( -m[1] * t11 + m[2] * t10 - m[3] * t9 ) / det;
        res.m[2] = ( m[13] * t5 - m[14] * t4 + m[15] * t3 ) / det;
        res.m[3] = ( -m[9] * t5 + m[10] * t4 - m[11] * t3 ) / det;
        res.m[4] = ( -m[4] * t11 + m[6] * t8 - m[7] * t7 ) / det;
        res.m[5] = ( m[0] * t11 - m[2] * t8 + m[3] * t7 ) / det;
        res.m[6] = ( -m[12] * t5 + m[14] * t2 - m[15] * t1 ) / det;
        res.m[7] = ( m[8] * t5 - m[10] * t2 + m[11] * t1 ) / det;
        res.m[8] = ( m[4] * t10 - m[5] * t8 + m[7] * t6 ) / det;
        res.m[9] = ( -m[0] * t10 + m[1] * t8 - m[3] * t6 ) / det;
        res.m[10] = ( m[12] * t4 - m[13] * t2 + m[15] * t0 ) / det;
        res.m[11] = ( -m[8] * t4 + m[9] * t2 - m[11] * t0 ) / det;
        res.m[12] = ( -m[4] * t9 + m[5] * t7 - m[6] * t6 ) / det;
        res.m[13] = ( m[0] * t9 - m[1] * t7 + m[2] * t6 ) / det;
        res.m[14] = ( -m[12] * t3 + m[13] * t1 - m[14] * t0 ) / det;
        res.m[15] = ( m[8] * t3 - m[9] * t1 + m[10] * t0 ) / det;

		return res;
	}

	Mat4 Mat4::Frustum( float left, float right, float bottom, float top, float near, float far )
	{
		Mat4 res;

		res.m[0] = near * 2.0f / ( right - left );
		res.m[5] = near * 2.0f / ( top - bottom );
		res.m[8] = ( right + left ) / ( right - left );
		res.m[9] = ( top + bottom ) / ( top - bottom );
		res.m[10] = ( -far - near ) / ( far - near );
		res.m[11] = -1;
		res.m[14] = -2.0f * far * near / ( far - near );
		res.m[15] = 0;

		return res;
	}

	Mat4 Mat4::Perspective( float fovy, float aspect, float near, float far )
	{
		float top = near * tan( fovy / 2.0f );
		float right = top * aspect;
		return Frustum( -right, right, -top, top, near, far );
	}

	Mat4 Mat4::Ortho( float left, float right, float bottom, float top, float near, float far )
	{
		Mat4 res;

		res.m[0] = 2 / ( right - left );
		res.m[5] = 2 / ( top - bottom );
		res.m[10] = -2 / ( far - near );
		res.m[12] = -( left + right ) / ( right - left );
		res.m[13] = -( top + bottom ) / ( top - bottom );
		res.m[14] = -( far + near ) / ( far - near );

		return res;
	}

	Mat4 Mat4::LookAt( const Vec3& eye, const Vec3& center, const Vec3& up )
	{
		Mat4 res;

		Vec3 Z = ( eye - center ).Normal();

		Vec3 X = Vec3(
			up.y * Z.z - up.z * Z.y,
			up.z * Z.x - up.x * Z.z,
			up.x * Z.y - up.y * Z.x
		).Normal();

		Vec3 Y = Vec3(
			Z.y * X.z - Z.z * X.y,
			Z.z * X.x - Z.x * X.z,
			Z.x * X.y - Z.y * X.x
		).Normal();

		res.m[0] = X.x;
        res.m[1] = Y.x;
        res.m[2] = Z.x;
        res.m[4] = X.y;
        res.m[5] = Y.y;
        res.m[6] = Z.y;
        res.m[8] = X.z;
        res.m[9] = Y.z;
        res.m[10] = Z.z;
		res.m[12] = -X.Dot( eye );
		res.m[13] = -Y.Dot( eye );
		res.m[14] = -Z.Dot( eye );

		return res;
	}
	Mat4 Mat4::LookAt( const Vec3& forward, const Vec3& up )
	{
		return LookAt(forward, GL::Vec3(0,0,0),up);
	}

	Vec3 Mat4::UnProject( const Vec3& vec, const Mat4& view, const Mat4& proj, const float viewport[] )
	{
		Mat4 inv = ( proj * view ).Inverse();
		Vec3 v(
			( vec.x - viewport[0] ) * 2.0f / viewport[2] - 1.0f,
			( vec.y - viewport[1] ) * 2.0f / viewport[3] - 1.0f,
			2.0f * vec.z - 1.0f
		);

		Vec3 res = inv * v;
		float w = inv.m[3] * v.x + inv.m[7] * v.y + inv.m[11] * v.z + inv.m[15];

		return res / w;
	}

	Vec3 Mat4::Project( const Vec3& vec, const Mat4& view, const Mat4& proj, const float viewport[] )
	{
		Mat4 trans = proj * view;
		Vec3 v = trans * vec;

		float w = trans.m[3] * vec.x + trans.m[7] * vec.y + trans.m[11] * vec.z + trans.m[15];
		v = v / w;

		return Vec3(
			viewport[0] + viewport[2] * ( v.x + 1.0f ) / 2.0f,
			viewport[1] + viewport[3] * ( v.y + 1.0f ) / 2.0f,
			( v.z + 1.0f ) / 2.0f
		);
	}

	Mat4 Mat4::FromR(const Quaternion& rotate){
		Mat4 m;
		float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
		x2 = rotate.x + rotate.x;
		y2 = rotate.y + rotate.y;
		z2 = rotate.z + rotate.z;
		xx = rotate.x * x2;   xy = rotate.x * y2;   xz = rotate.x * z2;
		yy = rotate.y * y2;   yz = rotate.y * z2;   zz = rotate.z * z2;
		wx = rotate.w * x2;   wy = rotate.w * y2;   wz = rotate.w * z2;

		m[0]=1.0f-(yy+zz); m[1]=xy-wz;        m[2]=xz+wy;
		m[4]=xy+wz;        m[5]=1.0f-(xx+zz); m[6]=yz-wx;
		m[8]=xz-wy;        m[9]=yz+wx;        m[10]=1.0f-(xx+yy);

		m[3] = m[7] = m[11] = 0;
		m[12] = m[13] = m[14] = 0;
		m[15] = 1;
		return m;
	}

	Mat4 Mat4::TRS(const Vec3 &pos, const Quaternion& rotate, const Vec3 &scale){
		Mat4 trs = Mat4(
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		);
		trs.Translate(pos);
		trs=trs*FromR(rotate);
		trs.Scale(scale);
		return trs;
	}
}