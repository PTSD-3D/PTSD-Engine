#pragma once

#include <memory>
#include "PTSDVectors.h"

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
	class Camera {
	private:
		//The node hierarchy is as follows: 
		// mNode -> cameraYawNode -> cameraPitchNode -> cameraRollNode -> mCamera

		//We use 3 separate nodes because if we apply a complex rotation directly to mNode it can cause
		//unwanted rotations in an axis we wouldn't like to rotate. (Rotate x and y and somehow it rotates z)
		//Therefore, it's recommended to keep them separate and use cameraYawNode only for Yaw operations, cameraPitchNode for Pitch and so on...

		Ogre::SceneNode* mNode;

		Ogre::SceneNode* cameraYawNode;
		Ogre::SceneNode* cameraPitchNode;
		Ogre::SceneNode* cameraRollNode;
		Ogre::Camera* mCamera;
		Ogre::RenderWindow* mWindow;
		Ogre::Viewport* mViewPort;
	public:	
		Camera(Vec3 v);
		~Camera();
		
		void setNearClip(float clip);
		void setFarClip(float clip);
		void lookAt(Vec3 v);
		void translate(Vec3 v);
		void setPosition(Vec3 v);
		void mouseRotate(Vector2D dir);
		void debugPos();
		void setOrtho(float orthoZoom);
		void setPerspective();
		Ogre::SceneNode* getNode();
		Vec3 getDirection();
		Vec3 getPosition();
		Vec3 getOrientation();
		float getOrthoWindowHeight();
		float getOrthoWindowWidth();
	};
}