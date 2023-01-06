#include <Math/Quaternion.h>
#include <Math/Util.h>
#include <math.h>

namespace GL
{
	Quaternion::Quaternion(){
		x=y=z=0;
		w=1;
	}
	Quaternion::Quaternion(float tx,float ty,float tz,float tw):x(tx),y(ty),z(tz),w(tw) {}

	Vec3 Quaternion::Multyply(const Vec3 position) const
	{
		Vec3 q = Vec3(x,y,z);
		Vec3 v2 = q.Cross(q.Cross(position) + position * w)*2.0;
		return position + v2;
	}
	Quaternion Quaternion::From(const Vec3 axis,const float angle){
		Quaternion qr;
		float half_angle = (angle * 0.5) * 3.14159 / 180.0;
		qr.x = axis.x * sin(half_angle);
		qr.y = axis.y * sin(half_angle);
		qr.z = axis.z * sin(half_angle);
		qr.w = cos(half_angle);
		return qr;
	}
	Quaternion Quaternion::From(const Mat4 m){
		Quaternion quat;
		float  tr, s, q[4];
		int    i, j, k;

		int nxt[3] = {1, 2, 0};

		tr = m[0] + m[5] + m[10];

		if (tr > 0.0)
		{
			s = sqrt (tr + 1.0);
			quat.w = s / 2.0;
			s = 0.5 / s;
			quat.x = (m[6] - m[9]) * s;
			quat.y = (m[8] - m[2]) * s;
			quat.z = (m[1] - m[4]) * s;
		}
		else
		{
			i = 0;
			if (m[5] > m[0]) i = 1;
			if (m[10] > m[i*5]) i = 2;
			j = nxt[i];
			k = nxt[j];

			s = sqrt ((m[i*5] - (m[j*5] + m[k*5])) + 1.0);

			q[i] = s * 0.5;

			if (s != 0.0) s = 0.5 / s;

			q[3] = (m[j*4+k] - m[k*4+j]) * s;
			q[j] = (m[i*4+j] + m[j*4+i]) * s;
			q[k] = (m[i*4+k] + m[k*4+i]) * s;

			quat.x = q[0];
			quat.y = q[1];
			quat.z = q[2];
			quat.w = q[3];
		}
		
		return quat;
	}

	Quaternion Quaternion::From(const Vec3 Eular3){
		return (Quaternion(0,0,sin(Eular3.z/2),cos(Eular3.z/2))*Quaternion(sin(Eular3.x/2),0,0,cos(Eular3.x/2))*Quaternion(0,sin(Eular3.y/2),0,cos(Eular3.y/2)));
	}
	Quaternion Quaternion::FromDeg(const Vec3 Eular3){
		return (Quaternion(0,0,sin(GL::Deg2Rad(Eular3.z)/2),cos(GL::Deg2Rad(Eular3.z)/2))*Quaternion(sin(GL::Deg2Rad(Eular3.x)/2),0,0,cos(GL::Deg2Rad(Eular3.x)/2))*Quaternion(0,sin(GL::Deg2Rad(Eular3.y)/2),0,cos(GL::Deg2Rad(Eular3.y)/2)));
	}
	
	Quaternion Quaternion::LookAt(const Vec3 from,const Vec3 to,const Vec3 up){
		return Quaternion();
	}

	float Quaternion::Magnitude() const{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}
	Quaternion Quaternion::Normal() const{
		Quaternion result(*this);
		float magnitude = Magnitude();
		result.x/=magnitude;
		result.y/=magnitude;
		result.z/=magnitude;
		result.w/=magnitude;
		return result;
	}
	Quaternion& Quaternion::Normalize(){
		float magnitude = Magnitude();
		x/=magnitude;
		y/=magnitude;
		z/=magnitude;
		w/=magnitude;
		return *this;
	}

    Quaternion& Quaternion::operator = (const Quaternion& q){
        x=q.x;
        y=q.y;
        z=q.z;
        w=q.w;
        return *this;
    }
    Quaternion Quaternion::operator - () const{
        return Quaternion(-x,-y,-z,-w).Normal();
    }
    Quaternion Quaternion::operator + ( const Quaternion& q2 ) const{
        return Quaternion(x+q2.x,y+q2.y,z+q2.z,w+q2.w).Normal();
    }
    Quaternion Quaternion::operator - ( const Quaternion& q2 ) const{
        return Quaternion(x-q2.x,y-q2.y,z-q2.z,w-q2.w).Normal();
    }
    Quaternion Quaternion::operator * ( const float& f ) const{
        return Quaternion(x*f,y*f,z*f,w*f).Normal();
    }
    Quaternion Quaternion::operator * (const Quaternion& q2) const{
        return Quaternion ( y * q2.z - z * q2.y + w * q2.x + x * q2.w,
                        z * q2.x - x * q2.z + w * q2.y + y * q2.w,
                        x * q2.y - y * q2.x + w * q2.z + z * q2.w,
                        w * q2.w - x * q2.x - y * q2.y - z * q2.z );
    }
    Quaternion& Quaternion::operator += (const Quaternion& q){
        x+=q.x;
        y+=q.y;
        z+=q.z;
        w+=q.w;
        return Normalize();
    }
    Quaternion& Quaternion::operator -= (const Quaternion& q){
        x-=q.x;
        y-=q.y;
        z-=q.z;
        w-=q.w;
        return Normalize();
    }
    Quaternion& Quaternion::operator *= (const float& f){
        x*=f;
        y*=f;
        z*=f;
        w*=f;
        return Normalize();
    }
    Quaternion& Quaternion::operator *=(const Quaternion& q){
        *this = Quaternion ( y * q.z - z * q.y + w * q.x + x * q.w,
            z * q.x - x * q.z + w * q.y + y * q.w,
            x * q.y - y * q.x + w * q.z + z * q.w,
            w * q.w - x * q.x - y * q.y - z * q.z );
        return *this;
    }
    
}

