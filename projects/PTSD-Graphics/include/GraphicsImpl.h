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
	class GraphicsImpl
	{
	private:
		Ogre::Root* mRoot;
		Ogre::RenderWindow* mRenderWindow;
		SDL_Window* mSDLWindow;
		Ogre::SceneManager* mSceneMgr;
		Ogre::Camera* mCamera;
		Ogre::Viewport* mViewPort;
		Ogre::FileSystemLayer* mFileSystemLayer;

		//TODO Camera class
		//TODO Light class
		//TODO Mesh class
		//Ogre::SceneNode* mLightNode, mCameraNode;

		void setupLogging();
		void setupWindow();
		void loadResources();
		void testScene();
		void msgPump();
	public:
		void Init();
		void Shutdown();

		bool renderFrame();

		GraphicsImpl() = default;
		~GraphicsImpl() = default;

	};
}