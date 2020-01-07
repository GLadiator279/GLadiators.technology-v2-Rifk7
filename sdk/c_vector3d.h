#pragma once

#ifdef NDEBUG
#define Assert( _exp ) ((void)0)
#else
#define Assert(x)
#endif

#include "class_id.h"
#include <sstream>

#define CHECK_VALID( _v ) 0

#define FastSqrt(x)	(sqrt)(x)

#define deg(a) a * 57.295779513082

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_2      (M_PI * 2.f)

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#endif

#include <cmath>
#include "../utils/intrinsics.h"

typedef float vec_t;

class c_vector3d
{
public:
	float x, y, z;

	__forceinline c_vector3d() : c_vector3d(0.f, 0.f, 0.f) { }

	__forceinline c_vector3d(const float x, const float y, const float z) : x(x), y(y), z(z) { }

	__forceinline c_vector3d operator+(const c_vector3d& v) const
	{
		return c_vector3d(x + v.x, y + v.y, z + v.z);
	}

	__forceinline c_vector3d operator-(const c_vector3d& v) const
	{
		return c_vector3d(x - v.x, y - v.y, z - v.z);
	}

	__forceinline c_vector3d operator*(const c_vector3d& v) const
	{
		return c_vector3d(x * v.x, y * v.y, z * v.z);
	}

	__forceinline c_vector3d operator/(const c_vector3d& v) const
	{
		return c_vector3d(x / v.x, y / v.y, z / v.z);
	}

	__forceinline c_vector3d operator*(const float v) const
	{
		return c_vector3d(x * v, y * v, z * v);
	}

	__forceinline c_vector3d operator/(const float v) const
	{
		return c_vector3d(x / v, y / v, y / v);
	}
	__forceinline float& operator[](int i) {
		return ((float*)this)[i];
	}

	__forceinline float operator[](int i) const {
		return ((float*)this)[i];
	}

	__forceinline c_vector3d operator+=(const c_vector3d& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}



	__forceinline c_vector3d operator-=(const c_vector3d& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	__forceinline c_vector3d operator*=(const c_vector3d& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	__forceinline c_vector3d operator/=(const c_vector3d& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	__forceinline c_vector3d operator*=(const float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	__forceinline c_vector3d operator/=(const float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	__forceinline float length() const
	{
		m128 tmp;
		tmp.f[0] = x * x + y * y + z * z;
		const auto calc = sqrt_ps(tmp.v);
		return reinterpret_cast<const m128*>(&calc)->f[0];
	}

	__forceinline float length2d() const
	{
		m128 tmp;
		tmp.f[0] = x * x + y * y;
		const auto calc = sqrt_ps(tmp.v);
		return reinterpret_cast<const m128*>(&calc)->f[0];
	}

	__forceinline float length2dsqr() const
	{
		return x * x + y * y;
	}

	__forceinline float dot(const c_vector3d& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	__forceinline float dist_to(const c_vector3d& vOther) const 
	{
		c_vector3d delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.length();
	}

	__forceinline float dot(const float* other) const
	{
		return x * other[0] + y * other[1] + z * other[2];
	}

	__forceinline c_vector3d cross(const c_vector3d& other) const
	{
		return c_vector3d(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	__forceinline c_vector3d normalize()
	{
		const auto l = length();

		if (l > 0)
		{
			x /= l;
			y /= l;
			z /= l;
		}

		return *this;
	}

	__forceinline bool is_valid() const
	{
		return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
	}
	void Clamp();
	void Normalize();
	void Sanitize();
};

class c_vector3d_aligned : public c_vector3d
{
	float w{};	
};

using c_qangle = c_vector3d;
