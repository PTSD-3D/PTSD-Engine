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
	inline double magnitude() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	Vector2D normalize() {

		Vector2D r;
		r.x = x;
		r.y = y;
		double mag = magnitude();
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
};