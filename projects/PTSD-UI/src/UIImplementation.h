namespace CEGUI {
	class String;
	class System;
	class EventArgs;
	class OgreRenderer;
	class WindowManager;
	class PushButton;
	class EventArgs;
	class Window;
}

namespace Ogre {
	class RenderWindow;
}

namespace PTSD {
	class UIImplementation {
	private:
		CEGUI::OgreRenderer* renderer;

		UIImplementation() = default;
		static UIImplementation* mInstance;
	public:
		static UIImplementation* getInstance() {
			if (mInstance == nullptr)
				mInstance = new UIImplementation();
			return mInstance;
		}

		int Init(Ogre::RenderWindow* mRenderWindow);
		bool Render();
		void Shutdown();

		~UIImplementation() = default;

	};
}