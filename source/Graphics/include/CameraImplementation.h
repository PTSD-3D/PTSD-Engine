#pragma once
#include <PTSDVectors.h>

//The design I followed to implement the Camera rotation (3 nodes, one for each rotation axis)
//I found in http://wiki.ogre3d.org/Creating+a+simple+first-person+camera+system
//If we ever need to make some adjustments to the camera, this is probablly a good place to start.

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
		Ogre::SceneNode* cameraYawNode;
		Ogre::SceneNode* cameraPitchNode;
		Ogre::SceneNode* cameraRollNode;
		Ogre::Camera* mCamera;
		Ogre::RenderWindow* mWindow;
		Ogre::Viewport* mViewPort;
	public:
		CameraImplementation(Vec3Placeholder v);
		~CameraImplementation();
		
		void lookAt(Vec3Placeholder pt);
		void translate(Vec3Placeholder v);
		void setPosition(Vec3Placeholder pos);
		void rotateMouse(Vector2D dir);
	};
};
