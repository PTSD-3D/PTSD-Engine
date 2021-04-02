#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDPHYS
		#define PHYSICSAPI  __declspec(dllexport)   // export DLL information
	#else
		#define PHYSICSAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDPHYS
		#define PHYSICSAPI __attribute__((visibility("default")))
	#else
		#define PHYSICSAPI
	#endif 
#endif 

#include <memory>
#include "Vec3.h"

class btRigidBody;

namespace PTSD
{
	class RigidbodyImplementation;
	class PHYSICSAPI Rigidbody {
	private:
		std::unique_ptr<RigidbodyImplementation> mImplementation;//private implementation w Bullet
		btRigidBody* mObj;
		Rigidbody();
		~Rigidbody() = default;
	public:
		Rigidbody* addSphereRigidBody(float size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		Rigidbody* addBoxRigidBody(Vec3Placeholder size, float mass, Vec3Placeholder pos, Vec4Placeholder quat = { 0,0,0,1 });
		void addForce(Vec3Placeholder force, Vec3Placeholder ref = { 0,0,0 });
	};
}