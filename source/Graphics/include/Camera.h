#pragma once

#include <memory>
#include "PTSDVectors.h"

namespace PTSD
{
	class CameraImplementation;
	class Camera {
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