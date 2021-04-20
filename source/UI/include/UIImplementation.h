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
		std::string mouseCursorName;

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

		void loadScheme(const std::string& filename);
		void loadFont(const std::string& filename);
		void loadLayout(const std::string& filename);
		void loadResources();

		void createRoot();
		void createText(const std::string& name, const std::string& text, Vector2D position, Vector2D size);
		void createStaticImage(const std::string& name, const std::string& source, Vector2D position, Vector2D size);
		void createButton(const std::string& name, const std::string& text, Vector2D position, Vector2D size);
		void setMouseCursor(const std::string& name);
		void setMouseCursorVisible(bool active);
		void setMouseInitialPosition(Vector2D mousePosition);
		void setEvent(const std::string& name, std::function<bool(const CEGUI::EventArgs&)> function);
		void setText(const std::string& name, const std::string& text);
		void setStaticImage(const std::string& name, const std::string& image);
		void setLayoutVisible(const std::string& name, bool visible);

		CEGUI::Window* getWindow(const std::string name);
		CEGUI::PushButton* getPushButton(const std::string& name);

		void injectMousePosition(Vector2D mousePosition);
		void injectMouseLeftClick();

		void test();
	};
}