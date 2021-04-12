#include "CameraImplementation.h"

#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "GraphicsImplementation.h"
#include <OgreViewport.h>
#include <Ogre.h>


namespace PTSD
{
	CameraImplementation::CameraImplementation(Vec3Placeholder v)
	{
		Ogre::SceneManager* mgr = GraphicsImplementation::getInstance()->getSceneMgr();
		mCamera = mgr->createCamera("mainCam");
		mNode = mgr->getRootSceneNode()->createChildSceneNode();
		mNode->setPosition({ v.x,v.y,v.z });
		cameraYawNode = mNode->createChildSceneNode();
		cameraPitchNode = cameraYawNode->createChildSceneNode();
		cameraRollNode = cameraPitchNode->createChildSceneNode();
		cameraRollNode->attachObject(mCamera);

		mCamera->setNearClipDistance(5);

		//TODO Window abstraction
		mWindow = GraphicsImplementation::getInstance()->getRenderWindow();
		mViewPort = GraphicsImplementation::getInstance()->getRenderWindow()->addViewport(mCamera);

		mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
	}

	CameraImplementation::~CameraImplementation()
	{
		
	}

	/**
	 * \brief looks to a world point
	 * \param pt point 
	 */
	void CameraImplementation::lookAt(Vec3Placeholder pt)
	{
		mNode->lookAt({pt.x,pt.y,pt.z},Ogre::Node::TS_WORLD);
	}

	/**
	 * \brief moves in world coordinates
	 * \param v movement vector 
	 */
	void CameraImplementation::translate(Vec3Placeholder v)
	{
		Ogre::Vector3 ogreVec = Ogre::Vector3(v.x, v.y, v.z);
		mNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * ogreVec, Ogre::SceneNode::TS_LOCAL);
	}

	/**
	 * \brief sets the world position of the camera
	 * \param pos position
	 */
	void CameraImplementation::setPosition(Vec3Placeholder pos)
	{
		mNode->setPosition({ pos.x,pos.y,pos.z });
	}

	void CameraImplementation::rotateMouse(Vector2D dir) {

		cameraPitchNode->pitch(Ogre::Degree(-dir.getY()));
		cameraYawNode->yaw(Ogre::Degree(-dir.getX()));

		// We don't want the camera to do a full 360º rotation on the x-axis. It needs to be locked at 180º
		float pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(this->cameraPitchNode->getOrientation().w)).valueDegrees());

		// Just to determine the sign of the angle we pick up above, the
		// value itself does not interest us.
		float pitchAngleSign = this->cameraPitchNode->getOrientation().x;

		// Limit the pitch between -90 degress and +90 degrees, Quake3-style.
		if (pitchAngle > 90.0f)
		{
			if (pitchAngleSign > 0)
				// Set orientation to 90 degrees on X-axis.
				this->cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
					Ogre::Math::Sqrt(0.5f), 0, 0));
			else if (pitchAngleSign < 0)
				// Sets orientation to -90 degrees on X-axis.
				this->cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
					-Ogre::Math::Sqrt(0.5f), 0, 0));
		}
	}
}
