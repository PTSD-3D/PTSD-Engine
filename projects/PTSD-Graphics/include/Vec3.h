#pragma once
//TODO PTSD Vec3

struct Vec3Placeholder
{
	float x, y, z;
	Vec3Placeholder(float x = 0, float y = 0, float z = 0):
	x(x),y(y),z(z){};
};

struct Vec4Placeholder {
	float x, y, z, w;
	Vec4Placeholder(float x = 0, float y = 0, float z = 0, float w = 0) :
		x(x), y(y), z(z), w(w) {};
};
