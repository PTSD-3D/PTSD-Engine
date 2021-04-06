#include <string>
#include <functional>

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
		CEGUI::OgreRenderer* renderer;
		CEGUI::Window* mRoot;
		CEGUI::WindowManager* windowMngr;
		CEGUI::System* system;
		Vector2D lastMousePosition;

		static UIImplementation* mInstance;
	public:
		UIImplementation() = default;
		~UIImplementation() = default;

		static UIImplementation* getInstance() {
			if (mInstance == nullptr)
				mInstance = new UIImplementation();
			return mInstance;
		}

		int init(Ogre::RenderWindow* mRenderWindow);
		void initLogger();
		bool render(double deltaTime);
		void shutdown();

		void loadScheme(std::string filename);
		void loadFont(std::string filename);
		void loadLayout(std::string filename);
		void loadResources();

		void createRoot();
		void createText(std::string name, std::string text, Vector2D position, Vector2D size);
		void createStaticImage(std::string name, std::string source, Vector2D position, Vector2D size);
		void createButton(std::string name, std::string text, Vector2D position, Vector2D size);
		void setMouseCursor(std::string name);
		void setMouseCursorVisible(bool active);
		void setMouseInitialPosition(Vector2D mousePosition);
		void setEvent(std::string name, std::function<bool(const CEGUI::EventArgs&)> function);
		void setText(std::string name, std::string text);
		void setStaticImage(std::string name, std::string image);
		void setLayoutVisible(std::string name, bool visible);

		CEGUI::PushButton* getPushButton(std::string name);

		void injectMousePosition(Vector2D mousePosition);
		void injectMouseLeftClick();

		void test();
	};
}