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
		mNode->attachObject(mCamera);
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
		mNode->translate({ v.x,v.y,v.z }, Ogre::Node::TS_WORLD);
	}

	/**
	 * \brief sets the world position of the camera
	 * \param pos position
	 */
	void CameraImplementation::setPosition(Vec3Placeholder pos)
	{
		mNode->setPosition({ pos.x,pos.y,pos.z });
	}
}
