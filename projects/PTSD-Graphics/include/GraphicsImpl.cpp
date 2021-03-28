#pragma once
#include <OgreString.h>
#include "GraphicsImpl.h"
#include "GraphicsLogger.hpp"
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_video.h>
#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <SDL_config_windows.h>
#include <SDL_syswm.h>
#include <OgreFileSystemLayer.h>
#include <Ogre.h>
#include <OgrePlugin.h>

// OGRE initialization:
#ifdef WIN32
//Necessary to tell the mouse events to go to this window
#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
// Necessary to get the Window Handle of the window
// OGRE created, so SDL can grab its input.
#include "windows.h"
#endif


namespace PTSD
{
	void GraphicsImpl::setupWindow1()
	{
		//TODO check one time config

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			LOG("Unable to initialise SDL", LogLevel::Critical);

		mSDLWindow = SDL_CreateWindow("PTSD Top Notch Engine", 25, 25, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		SDL_GL_CreateContext(mSDLWindow);

		SDL_SysWMinfo wmInfo;
		SDL_GetVersion(&wmInfo.version);

		if (!SDL_GetWindowWMInfo(mSDLWindow, &wmInfo))
		{
			Ogre::LogManager::getSingleton().logMessage(Ogre::String("Couldn't get WM info"));
		}

		mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
		//mRoot->setRenderSystem(mRoot->getRenderSystemByName("OpenGL Rendering Subsystem"));
		mRoot->restoreConfig();
		mRoot->initialise(false);

		Ogre::NameValuePairList misc;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
		HWND hwnd = wmInfo.info.win.window;
		Ogre::String winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.win.window);
		//unsigned long winGlContext = reinterpret_cast<unsigned long>(wmInfo.info.win.hdc);

		SDL_GLContext context = SDL_GL_GetCurrentContext();
		unsigned long winGlContext = (unsigned long)context;

		misc["externalWindowHandle"] = winHandle;
		misc["externalGLContext"] = Ogre::StringConverter::toString(winGlContext);
		misc["externalGLControl"] = Ogre::String("True");
#else
		misc["currentGLContext"] = Ogre::String("True");
#endif


		mRenderWindow = mRoot->createRenderWindow("PTSD Top Notch Engine", 800, 600, false, &misc);


	}

	void GraphicsImpl::setupWindow2()
	{
		// Initialise OGRE
		char tmp[64] = "HELP";
		mRenderWindow = mRoot->initialise(true, tmp);

		// Initialise SDL
#ifdef WIN32
   // Allow SDL to use the window OGRE just created

   // Old method: do not use this, because it only works
   //  when there is 1 (one) window with this name!
   // HWND hWnd = FindWindow(NULL, tmp);

   // New method: As proposed by Sinbad.
   //  This method always works.
		HWND hWnd;
		mRenderWindow->getCustomAttribute("WINDOW", &hWnd);

		// Set the SDL_WINDOWID environment variable
		//  Please note that later SDL converts the WINDOWID-string back into
		//  an unsigned long. So make sure you save a valid id by utilizing 
		//  %u instead of %d.
		sprintf(tmp, "SDL_WINDOWID=%u", (unsigned long)hWnd);
		_putenv(tmp);

		//if (!mRenderWindow->isFullScreen())
		//{
		//	// This is necessary to allow the window to move
		//	//  on WIN32 systems. Without this, the window resets
		//	//  to the smallest possible size after moving.
		//	mSDL->initialise(mWindow->getWidth(), mWindow->getHeight());
		//}
		//else
		//{
		//	mSDL->initialise(0, 0);
		//}
#else
		mSDL->initialise();
#endif
	}

	void GraphicsImpl::locateResources()
	{
		// load resource paths from config file
		mFileSystemLayer = new Ogre::FileSystemLayer("./assets/");
		Ogre::ConfigFile cf;

		std::string resourcesPath = mFileSystemLayer->getConfigFilePath("../resources.cfg");
		if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		{
			cf.load(resourcesPath);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				Ogre::FileSystemLayer::resolveBundlePath("./assets/"),
				"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		}

		Ogre::String sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());
	}

	void GraphicsImpl::testScene()
	{

		mSceneMgr = mRoot->createSceneManager();

		mCamera = mSceneMgr->createCamera("mainCam");
		//mCamera->setPosition(0, 0, 80);
		//mCamera->lookAt(0, 0, -300);
		mCamera->setNearClipDistance(5);
		mViewPort = mRenderWindow->addViewport(mCamera);
		mViewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
		mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));


		Ogre::Entity* ogreEntt = mSceneMgr->createEntity("ogrehead.mesh");
		Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		ogreNode->attachObject(ogreEntt);

		mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

		Ogre::Light* light = mSceneMgr->createLight("MainLight");
		//light->setPosition(20, 80, 50);
	}

	void GraphicsImpl::Init()
	{
		//PTSD Logging, before init we will redirect everything to our own logger
		Ogre::LogManager* logMgr = new Ogre::LogManager();
		Ogre::Log* log = Ogre::LogManager::getSingleton().createLog("logs/Ogre.log", true, false, true);
		log->addListener(new PTSDLogListener());
		Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("GET OUT OF MY SWAMP", Ogre::LML_WARNING);



		//Ogre Tutorial 6 approves
		//Ogre::ConfigFile cf;
		//cf.load("resources.cfg");
		//Ogre::String name, locType;
		//Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
		//while(secIt.hasMoreElements())
		//{
		//	Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		//	Ogre::ConfigFile::SettingsMultiMap::iterator it;
		//	for (it = settings->begin(); it != settings->end(); ++it)
		//	{
		//		locType = it->first;
		//		name = it->second;
		//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		//	}
		//}

		setupWindow1();
		locateResources();
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		testScene();

		PTSD::LOG("Graphics system initialized");	
	}

	bool GraphicsImpl::renderFrame()
	{
		//TODO message pump???
		if (mRenderWindow->isClosed()) 
			return false;

		if (!mRoot->renderOneFrame()) 
			return false;
	}

	void GraphicsImpl::Shutdown()
	{
		delete mRoot;
	}
}
