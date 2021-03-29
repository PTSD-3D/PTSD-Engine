#include "CameraImpl.h"


#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "GraphicsImpl.h"
#include <OgreViewport.h>
#include <Ogre.h>


namespace PTSD
{
	CameraImpl::CameraImpl(Vec3_placeholder v)
	{
		Ogre::SceneManager* mgr = GraphicsImpl::getInstance()->getSceneMgr();
		mCamera = mgr->createCamera("mainCam");
		mNode = mgr->getRootSceneNode()->createChildSceneNode();
		mNode->setPosition({ v.x,v.y,v.z });
		mNode->attachObject(mCamera);
		mCamera->setNearClipDistance(5);

		//TODO Window abstraction
		mWindow = GraphicsImpl::getInstance()->getRenderWindow();
		mViewPort = GraphicsImpl::getInstance()->getRenderWindow()->addViewport(mCamera);

		mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
	}

	CameraImpl::~CameraImpl()
	{
		
	}

	/**
	 * \brief looks to a world point
	 * \param pt point 
	 */
	void CameraImpl::lookAt(Vec3_placeholder pt)
	{
		mNode->lookAt({pt.x,pt.y,pt.z},Ogre::Node::TS_WORLD);
	}

	/**
	 * \brief moves in world coordinates
	 * \param v movement vector 
	 */
	void CameraImpl::translate(Vec3_placeholder v)
	{
		mNode->translate({ v.x,v.y,v.z }, Ogre::Node::TS_WORLD);
	}

	/**
	 * \brief sets the world position of the camera
	 * \param pos position
	 */
	void CameraImpl::setPosition(Vec3_placeholder pos)
	{
		mNode->setPosition({ pos.x,pos.y,pos.z });
	}
}
