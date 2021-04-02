#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDGRAPHICS
		#define GRAPHICSAPI  __declspec(dllexport)   // export DLL information
	#else
		#define GRAPHICSAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDLOG
		#define GRAPHICSAPI __attribute__((visibility("default")))
	#else
		#define GRAPHICSAPI
	#endif 
#endif 

#include <memory>
#include "Vec3.h"

namespace PTSD
{
	class CameraImplementation;
	class GRAPHICSAPI Camera {
	private:
		std::unique_ptr<CameraImplementation> mImplementation;//private implementation w Ogre
	public:	
		Camera(Vec3Placeholder v);
		~Camera();
		
		void lookAt(Vec3Placeholder v);
		void translate(Vec3Placeholder v);
		void setPosition(Vec3Placeholder v);
		
	};
}