#include "PTSDVectors.h"
std::ostream& operator<<(std::ostream& os, const Vec3& r) 
{
	os << "{x: "<< r.x << " y: "<< r.y <<" z: " << r.z << "}";
	return os;
};
