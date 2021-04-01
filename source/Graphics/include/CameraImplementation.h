#pragma once


#include <PTSDVectors.h>

namespace Ogre
{
	class SceneNode;
	class Camera;
	class RenderWindow;
	class Viewport;
}
namespace PTSD
{
	class CameraImplementation
	{
	private:
		Ogre::SceneNode* mNode;
		Ogre::Camera* mCamera;
		Ogre::RenderWindow* mWindow;
		Ogre::Viewport* mViewPort;
	public:
		CameraImplementation(Vec3Placeholder v);
		~CameraImplementation();
		
		void lookAt(Vec3Placeholder pt);
		void translate(Vec3Placeholder v);
		void setPosition(Vec3Placeholder pos);
	};
};
