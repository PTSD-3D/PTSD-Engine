#pragma once
#ifdef _PTSDGRAPHICS
#define GRAPHICSAPI  __declspec(dllexport)   // export DLL information

#else
#define GRAPHICSAPI  __declspec(dllimport)   // import DLL information

#endif

#include <memory>
#include "Vec3.h"

namespace PTSD
{
	class CameraImpl;
	class GRAPHICSAPI Camera {
	private:
		std::unique_ptr<CameraImpl> mImpl;//private implementation w Ogre
	public:	
		Camera(Vec3_placeholder v);
		~Camera();
		
		void lookAt(Vec3_placeholder v);
		void translate(Vec3_placeholder v);
		void setPosition(Vec3_placeholder v);
		
	};
}