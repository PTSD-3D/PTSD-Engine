#pragma once
#include <SDL_video.h>

namespace Ogre
{
	class Root;
	class RenderWindow;
	class Camera;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class FileSystemLayer;
}

namespace PTSD
{
	class Camera;
	class GraphicsImplementation
	{
	private:
		Ogre::Root* mRoot;
		Ogre::RenderWindow* mRenderWindow;
		SDL_Window* mSDLWindow;
		Ogre::SceneManager* mSceneMgr;
		//Ogre::Camera* mOgreCam;
		Ogre::Viewport* mViewPort;
		Ogre::FileSystemLayer* mFileSystemLayer;
		double deltaTime;
		double lastRenderTime;

		//TODO Camera class
		Camera* mCamera;
		//TODO Light class
		//TODO Mesh class
		//Ogre::SceneNode* mLightNode, mCameraNode;

		void setupLogging();
		void setupWindow();
		void loadResources();
		void testScene();
		void msgPump();

		
		GraphicsImplementation() = default;
		static GraphicsImplementation* mInstance;

	public:
		~GraphicsImplementation() = default;

		static GraphicsImplementation* getInstance()
		{
			if (mInstance == nullptr)
				mInstance = new GraphicsImplementation();
			return mInstance;
		}
		void init();
		void shutdown();

		bool renderFrame();

		Ogre::Root* getRoot() const { return mRoot; }
		Ogre::SceneManager* getSceneMgr() const { return mSceneMgr; }
		Camera* getCamera() const { return mCamera; }
		Ogre::RenderWindow* getRenderWindow() const { return mRenderWindow; }
		double getDeltaTime() const { return deltaTime; }
	};
}