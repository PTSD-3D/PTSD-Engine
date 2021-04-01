#include <OgreString.h>
#include "GraphicsImplementation.h"
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
#include <SDL_syswm.h>
#include <OgreFileSystemLayer.h>
#include <Ogre.h>
#include <OgrePlugin.h>
#include "Camera.h"

// OGRE initialization:
#ifdef WIN32
// #include <SDL_config_windows.h>
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
	GraphicsImplementation* GraphicsImplementation::mInstance = nullptr;
	/**
	 * \brief Redirects OGRE logging system to PTSD-Logger
	 */
	void GraphicsImplementation::setupLogging()
	{
		//PTSD Logging, before init we will redirect everything to our own logger
		Ogre::LogManager* logMgr = new Ogre::LogManager();
		Ogre::Log* log = Ogre::LogManager::getSingleton().createLog("logs/Ogre.log", true, false, true);
		log->addListener(new PTSDLogListener());
		Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("GET OUT OF MY SWAMP", Ogre::LML_WARNING);
	}

	/**
	 * \brief Creates an SDL window and hooks OGRE to it
	 */
	void GraphicsImplementation::setupWindow()
	{
		mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

		if (!mRoot->restoreConfig())
		{
			mRoot->showConfigDialog(nullptr);
		}

		//We create Root without a window
		mRoot->initialise(false);

		// We set up an SDL window
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			LOG("Unable to initialise SDL", LogLevel::Critical);
		Uint32 flags = SDL_WINDOW_RESIZABLE;
		#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
			flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
		#endif
		mSDLWindow = SDL_CreateWindow("PTSD Top Notch Engine", 25, 25, 800, 600, flags);

		SDL_SysWMinfo wmInfo;
		SDL_GetVersion(&wmInfo.version);

		if (!SDL_GetWindowWMInfo(mSDLWindow, &wmInfo))
		{
			LOG("Couldnt get window info", Critical);
		}

		Ogre::NameValuePairList misc;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
		misc["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
#else
		SDL_GL_CreateContext(mSDLWindow);
		if(!SDL_GL_GetCurrentContext())
			LOG("Cannot create SDL_GL context", Critical);
		misc["currentGLContext"] = Ogre::String("True");
#endif

		//We create/hook Ogre to the SDL window
		mRenderWindow = mRoot->createRenderWindow("PTSD Top Notch Engine", 800, 600, false, &misc);

		mRenderWindow->setActive(true);
		mRenderWindow->setVisible(true);
	}

	
	/**
	 * \brief Finds resources stated in resources.cfg
	 */
	void GraphicsImplementation::loadResources()
	{
		//TODO parametrization and configuration
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

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void GraphicsImplementation::testScene()
	{

		mSceneMgr = mRoot->createSceneManager();

		mCamera = new Camera({ 0,0,80 });

		Ogre::Entity* ogreEntt = mSceneMgr->createEntity("ogrehead.mesh");
		Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		ogreNode->attachObject(ogreEntt);

		mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

		Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		Ogre::Light* light = mSceneMgr->createLight("MainLight");
		lightNode->setPosition(20, 80, 50);
		lightNode->attachObject(light);
	}

	
	/**
	 * \brief Pumps messages, needed for render loop
	 */
	void GraphicsImplementation::msgPump()
	{
		
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			// Windows Message Loop (NULL means check all HWNDs belonging to this context)
			MSG  msg;
			while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
 #elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
				SDL_PumpEvents();
#endif
		
	}

	void GraphicsImplementation::init()
	{

		setupLogging();
		setupWindow();
		loadResources();
		testScene();

		LOG("Graphics system initialized");	
	}

	/**
	 * \brief Renders a frame!
	 * \return true on success
	 */
	bool GraphicsImplementation::renderFrame()
	{
		msgPump();

		if (mRenderWindow->isClosed())
		{
			LOG("Window is closed", LogLevel::Warning);
			return false;

		}

		if (!mRoot->renderOneFrame())
		{
			LOG("Couldnt render frame", Error);
			return false;

		}

		//LOG("Frame rendered", Trace);
		return true;
	}

	void GraphicsImplementation::shutdown()
	{
		delete mRoot;
	}
}
