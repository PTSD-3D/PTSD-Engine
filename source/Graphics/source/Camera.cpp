#include "Camera.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "GraphicsImplementation.h"
#include <OgreViewport.h>
#include <Ogre.h>

/**
 * \brief Creates a camera in pos
 * \param pos position
 */
PTSD::Camera::Camera(Vec3 pos)
{
	Ogre::SceneManager* mgr = GraphicsImplementation::getInstance()->getSceneMgr();
	mCamera = mgr->createCamera("mainCam");
	mNode = mgr->getRootSceneNode()->createChildSceneNode();
	mNode->setPosition({ pos.x,pos.y,pos.z });
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

PTSD::Camera::~Camera() = default;

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

/**
 * \brief rotates the camera in the x and y axis using mouse delta
 * \param dir rotation direction in angles
 */
void PTSD::Camera::mouseRotate(Vector2D dir)
{
	cameraPitchNode->pitch(Ogre::Degree(-dir.getY()));
	cameraYawNode->yaw(Ogre::Degree(-dir.getX()));

	// We don't want the camera to do a full 360º rotation on the x-axis. It needs to be locked at 180º
	float pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(cameraPitchNode->getOrientation().w)).valueDegrees());

	// Just to determine the sign of the angle we pick up above, the
	// value itself does not interest us.
	float pitchAngleSign = cameraPitchNode->getOrientation().x;

	// Limit the pitch between -90 degress and +90 degrees, Quake3-style.
	if (pitchAngle > 90.0f)
	{
		if (pitchAngleSign > 0)
			// Set orientation to 90 degrees on X-axis.
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
				Ogre::Math::Sqrt(0.5f), 0, 0));
		else if (pitchAngleSign < 0)
			// Sets orientation to -90 degrees on X-axis.
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
				-Ogre::Math::Sqrt(0.5f), 0, 0));
	}
}

