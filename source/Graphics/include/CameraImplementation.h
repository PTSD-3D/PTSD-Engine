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

		//The node hierarchy is as follows: 
		// mNode -> cameraYawNode -> cameraPitchNode -> cameraRollNode -> mCamera

		//We use 3 separate nodes because if we apply a complex rotation directly to mNode it can cause
		//unwanted rotations in an axis we wouldn't like to rotate. (Rotate x and y and somehow it rotates z)
		//Therefore, it's recommended to keep them separate and use cameraYawNode only for Yaw operations, cameraPitchNode for Pitch and so on...

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
