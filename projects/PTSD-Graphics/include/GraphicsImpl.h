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

		////TODO wrappers for Camera and Light
		//Ogre::SceneNode* mLightNode, mCameraNode;

		void setupWindow1();
		void setupWindow2();
		void locateResources();
		void testScene();
	public:
		GraphicsImpl() = default;
		~GraphicsImpl() = default;
		void Init();
		bool renderFrame();
		void Shutdown();
	};
}