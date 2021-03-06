#include "Camera.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <Ogre.h>
#include "LogManager.h"
#include <fstream>
#include <iostream>
#include "GraphicsManager.h"
/**
 * \brief Creates a camera in pos
 * \param pos position
 */
PTSD::Camera::Camera(Vec3 pos)
{
	Ogre::SceneManager* mgr = GraphicsManager::getInstance()->getSceneMgr();
	mCamera = mgr->createCamera("mainCam");
	mNode = mgr->getRootSceneNode()->createChildSceneNode();
	mNode->setPosition({ pos.x,pos.y,pos.z });
	cameraYawNode = mNode->createChildSceneNode();
	cameraPitchNode = cameraYawNode->createChildSceneNode();
	cameraRollNode = cameraPitchNode->createChildSceneNode();
	cameraRollNode->attachObject(mCamera);

	mCamera->setNearClipDistance(5);

	//TODO Window abstraction
	mWindow = GraphicsManager::getInstance()->getRenderWindow();
	mViewPort = GraphicsManager::getInstance()->getRenderWindow()->addViewport(mCamera);
	mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
	mCamera->setAutoAspectRatio(true);
}

PTSD::Camera::~Camera(){
	//OgreRoot cleans this up
};

void PTSD::Camera::setNearClip(float clip)
{
	mCamera->setNearClipDistance(clip);
}

void PTSD::Camera::setFarClip(float clip)
{
	mCamera->setFarClipDistance(clip);
}

/**
 * \brief looks to a world point
 * \param pt point
 */
void PTSD::Camera::lookAt(Vec3 pt)
{
	mNode->lookAt({ pt.x,pt.y,pt.z }, Ogre::Node::TS_WORLD);
}

/**
 * \brief moves in world coordinates
 * \param v movement vector
 */
void PTSD::Camera::translate(Vec3 v)
{
	Ogre::Vector3 ogreVec = Ogre::Vector3(v.x, v.y, v.z);
	mNode->translate(cameraYawNode->getOrientation() * cameraPitchNode->getOrientation() * ogreVec, Ogre::SceneNode::TS_LOCAL);
}

/**
 * \brief sets the world position of the camera
 * \param pos position
 */
void PTSD::Camera::setPosition(Vec3 pos)
{
	mNode->setPosition({ pos.x,pos.y,pos.z });
}

Ogre::SceneNode* PTSD::Camera::getNode() { return mNode; }

/**
 * \brief rotates the camera in the x and y axis using mouse delta
 * \param dir rotation direction in angles
 */
void PTSD::Camera::mouseRotate(Vector2D dir)
{
	mCamera->pitch(Ogre::Degree(-dir.getY()));
	mCamera->yaw(Ogre::Degree(-dir.getX()));

	// We don't want the camera to do a full 360?? rotation on the x-axis. It needs to be locked at 180??
	float pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(mCamera->getOrientation().w)).valueDegrees());

	// Just to determine the sign of the angle we pick up above, the
	// value itself does not interest us.
	float pitchAngleSign = mCamera->getOrientation().x;

	// Limit the pitch between -90 degress and +90 degrees, Quake3-style.
	if (pitchAngle > 90.0f)
	{
		if (pitchAngleSign > 0)
			// Set orientation to 90 degrees on X-axis.
			mCamera->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
				Ogre::Math::Sqrt(0.5f), 0, 0));
		else if (pitchAngleSign < 0)
			// Sets orientation to -90 degrees on X-axis.
			mCamera->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
				-Ogre::Math::Sqrt(0.5f), 0, 0));
	}
}

void PTSD::Camera::debugPos()
{
	std::cout << mNode->getPosition().x << "  " << mNode->getPosition().y << "  " << mNode->getPosition().z << "\n"; //Please delete me or implement using PTSDLog

}


Vec3 PTSD::Camera::getDirection()
{
	Ogre::Vector3 v = mCamera->getRealDirection();
	Vec3 vect = { v.x,v.y,v.z };

	return vect;
}

Vec3 PTSD::Camera::getOrientation()
{
	Ogre::Quaternion quaternion = mCamera->getRealOrientation();
	
	Ogre::Matrix3 mx2;
	quaternion.ToRotationMatrix(mx2);
	Ogre::Radian x, y, z;
	mx2.ToEulerAnglesYXZ(y, x, z);
	Vec3 vect(x.valueAngleUnits(), y.valueAngleUnits(), z.valueAngleUnits());

	return vect;
}

void PTSD::Camera::setOrtho(float orthoZoom)
{
	Ogre::Real k = mViewPort->getActualWidth();
	mCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	mCamera->setOrthoWindow(mViewPort->getActualWidth() * orthoZoom, mViewPort->getActualHeight() * orthoZoom);
}

void PTSD::Camera::setPerspective()
{
	mCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
}

Vec3 PTSD::Camera::getPosition() {
	Ogre::Vector3 v = mCamera->getRealPosition();
	return { v.x, v.y, v.z };
}

float PTSD::Camera::getOrthoWindowHeight() {
	return mCamera->getOrthoWindowHeight();
}

float PTSD::Camera::getOrthoWindowWidth() {
	return mCamera->getOrthoWindowWidth();
}
