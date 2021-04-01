#include <string>

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
	class RenderTarget;
}

namespace PTSD {
	class UIImplementation {
	private:
		UIImplementation() = default;
		CEGUI::OgreRenderer* renderer;
		CEGUI::Window* mRoot;

		static UIImplementation* mInstance;
	public:
		~UIImplementation() = default;

		static UIImplementation* getInstance() {
			if (mInstance == nullptr)
				mInstance = new UIImplementation();
			return mInstance;
		}

		int init(Ogre::RenderWindow* mRenderWindow);
		bool render();
		void shutdown();

		void loadScheme(std::string filename);
		void loadFont(std::string filename);

		void createRoot();

	};
}