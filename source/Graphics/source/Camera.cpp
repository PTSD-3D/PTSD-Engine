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

Ogre::SceneNode* PTSD::Camera::getNode() { return mNode; }

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

void PTSD::Camera::debugPos()
{
	std::cout << mNode->getPosition().x << "  " << mNode->getPosition().y << "  " << mNode->getPosition().z << "\n"; //Please delete me or implement using PTSDLog

}

void PTSD::Camera::mousePitch(float dir)
{
	cameraPitchNode->pitch(Ogre::Degree(-dir));

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

Vec3 PTSD::Camera::getOrientation()
{
	Ogre::Vector3 v = mCamera->getRealDirection();
	
	Vec3 vect = { v.x,v.y,v.z };
	
	/*Ogre::Quaternion q = mCamera->getRealOrientation();

	Ogre::Matrix3 mx2;
	q.ToRotationMatrix(mx2);
	Ogre::Radian x, y, z;
	mx2.ToEulerAnglesYXZ(y, x, z);
	Vec3 vect(x.valueAngleUnits(), y.valueAngleUnits(), z.valueAngleUnits());*/

	//std::cout << vect.x << " " << vect.y << " " << vect.z << std::endl;

	return vect;

	//mNode->getOrientation();


	//LOG("Entra getRay camera");
	//Vec3 coord;

	////coord.x = (((2.0f * x) / mWindow->getWidth()) - 1);
	////coord.y = -(((2.0f * y) / mWindow->getHeight()) - 1);
	//coord.x = x;
	//coord.y = y;
	//coord.z = 1.0f;

	//// Back project the ray from screen to the far clip plane
	//coord.x /= mCamera->getProjectionMatrix()[1][1];
	//coord.y /= mCamera->getProjectionMatrix()[2][2];
	//LOG("ProjM");

	////btMatrix3x3 matinv;
	////D3DXMatrixInverse(&matinv, NULL, &mCamera->getViewMatrix());

	//auto matinv = mCamera->getViewMatrix().inverse();
	//LOG("ViewMatInv");

	//float farClip = mCamera->getFarClipDistance();
	//coord = coord * farClip;

	//LOG("FarClip");

	//Vec3 newCoord;
	////VOut.x = VIn.x * M.11 + VIn.y * M.21 + VIn.z * M.31 + M.41
	////VOut.y = VIn.x * M.12 + VIn.y * M. 22 + VIn.z * M.32 + M.42
	////VOut.z = VIn.x * M.13 + VIn.y * M.23 + VIn.z * M.33 + M.43
	//newCoord.x = coord.x * matinv[1][1] + coord.y * matinv[2][1] + coord.z * matinv[3][1];
	//newCoord.y = coord.x * matinv[1][2] + coord.y * matinv[2][2] + coord.z * matinv[3][2];
	//newCoord.z = coord.x * matinv[1][3] + coord.y * matinv[2][3] + coord.z * matinv[3][3];

	//LOG("Termina camera");

}

