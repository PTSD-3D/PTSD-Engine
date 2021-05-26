#pragma once
#include "PTSDAssert.h"
#include <SDL_video.h>

class SDL_Window;

namespace Ogre {
	class Root;
	class RenderWindow;
	class Camera;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class FileSystemLayer;
	class Log;
	class LogManager;
}
class PTSDLogListener;
namespace PTSD {
	class Camera;

	/**
	 * \brief Singleton Rendering Manger
	 */
	class GraphicsManager {
	private:
		static GraphicsManager* mInstance;
		
		Ogre::Root* mRoot;
		Ogre::RenderWindow* mRenderWindow;
		SDL_Window* mSDLWindow;
		Ogre::SceneManager* mSceneMgr;
		//Ogre::Camera* mOgreCam;
		Ogre::Viewport* mViewPort;
		Ogre::FileSystemLayer* mFileSystemLayer;
		/*Time difference between the previous frame and the current frame in seconds*/
		double deltaTime;
		Uint32 lastRenderTime;

		Camera* mCamera;
		//Ogre::SceneNode* mLightNode, mCameraNode;
		Ogre::Log* mLog;
		Ogre::LogManager* mLogManager;
		PTSDLogListener* mLogListener;

		void setupLogging();
		void setupWindow();
		void setupMouse();
		void loadResources();
		void testScene();
		void msgPump();
	public:
		GraphicsManager() = default;

		~GraphicsManager() = default;

		static GraphicsManager* getInstance()
		{
			PTSD_ASSERT(mInstance != nullptr, "Renderer singleton accessed before init");
			return mInstance;
		}

		static int init();
		void shutdown();

		bool renderFrame();

		Ogre::Root* getRoot() const { return mRoot; }
		Ogre::SceneManager* getSceneMgr() const { return mSceneMgr; }
		Camera* getCam() const { return mCamera; }
		Ogre::RenderWindow* getRenderWindow() const { return mRenderWindow; }
		SDL_Window* getSDLWindow() const { return mSDLWindow; }
		float getWindowWidth() const;
		float getWindowHeight() const;
		double getDeltaTime() const { return deltaTime; }
		void setMouseLocked(bool locked);
		void setSceneSkybox(bool enabled, const std::string& material, float distance, bool renderFirst );
		void setSceneSkydome(bool enabled, const std::string& material, unsigned int curvature, unsigned int tiledRepetitions);
	};
}