#include <string>

#include "PTSDVectors.h"

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
		CEGUI::WindowManager* windowMngr;
		CEGUI::System* system;

		static UIImplementation* mInstance;
	public:
		~UIImplementation() = default;

		static UIImplementation* getInstance() {
			if (mInstance == nullptr)
				mInstance = new UIImplementation();
			return mInstance;
		}

		int init(Ogre::RenderWindow* mRenderWindow);
		bool render(double deltaTime);
		void shutdown();

		void loadScheme(std::string filename);
		void loadFont(std::string filename);
		void loadResources();

		void createRoot();
		void createWindowStaticImage(std::string name, std::string source, Vector2D position, Vector2D size);
		void setMouseCursor(std::string name);
		void setMouseCursorVisible(bool active);

		void injectMousePosition(Vector2D mousePosition);

		void test();
	};
}