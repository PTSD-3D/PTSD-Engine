#pragma once


#include <Vec3.h>

namespace Ogre
{
	class SceneNode;
	class Camera;
	class RenderWindow;
	class Viewport;
}
namespace PTSD
{
	class CameraImpl
	{
	private:
		Ogre::SceneNode* mNode;
		Ogre::Camera* mCamera;
		Ogre::RenderWindow* mWindow;
		Ogre::Viewport* mViewPort;
	public:
		CameraImpl(Vec3_placeholder v);
		~CameraImpl();
		
		void lookAt(Vec3_placeholder pt);
		void translate(Vec3_placeholder v);
		void setPosition(Vec3_placeholder pos);
	};
};
