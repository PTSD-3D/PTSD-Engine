#pragma once
#include <cmath>

//Struct use for axis directions and operations
struct Vector2D {
	float x;
	float y;

	inline float getX() const {
		return x;
	}
	inline float getY() const {
		return y;
	}
	inline void setX(float x_) {
		x = x_;
	}
	inline void setY(float y_) {
		y = y_;
	}
	inline float magnitude() const {
		return sqrt(x*x + y*y);
	}
	Vector2D normalize() {

		Vector2D r;
		r.x = x;
		r.y = y;
		float mag = magnitude();
		if (mag > 0.0) {
			r.x = r.x / mag;
			r.y = r.y / mag;
		}
		return r;

	}
	Vector2D() :
		x(), y() {
	}
	Vector2D(float x_, float y_) :
		x(x_), y(y_) {
	}
	Vector2D(const Vector2D& v) :
		x(v.getX()), y(v.getY()) {
	}
	Vector2D operator - (const Vector2D& v) const {
		return(Vector2D(x - v.x, y - v.y));
	}
	Vector2D operator + (const Vector2D& v) const{
		return(Vector2D(x + v.x, y + v.y));
	}
	Vector2D operator * (const float &f) const{
		return(Vector2D(x * f, y * f));
	}
};

struct Vec3
{
	float x, y, z;
	Vec3(float x = 0, float y = 0, float z = 0):
	x(x),y(y),z(z){};

	inline float magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	Vec3 normalize() {

		Vec3 r;
		r.x = x;
		r.y = y;
		r.z = z;

		float mag = magnitude();
		if (mag > 0.0) {
			r.x = r.x / mag;
			r.y = r.y / mag;
			r.z = r.z / mag;
		}
		return r;

	}

	Vec3 operator - (const Vec3& v) const {
		return(Vec3(x - v.x, y - v.y,z-v.z));
	}
	Vec3 operator + (const Vec3& v) const{
		return(Vec3(x + v.x, y + v.y,z+v.z));
	}
	Vec3 operator * (const float &f) const{
		return(Vec3(x * f, y * f,z*f));
	}
};

struct Vec4Placeholder {
	float x, y, z, w;
	Vec4Placeholder(float x = 0, float y = 0, float z = 0, float w = 0) :
		x(x), y(y), z(z), w(w) {};
};

struct QuatPlaceholder {
	float x, y, z, w;
	QuatPlaceholder(float x = 0, float y = 0, float z = 0, float w = 0) :
		x(x), y(y), z(z), w(w) {};

	QuatPlaceholder(const QuatPlaceholder& rhs)
		: w(rhs.w), x(rhs.x), y(rhs.y), z(rhs.z)
	{};
};
