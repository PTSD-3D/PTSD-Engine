#pragma once
#include <string>
#include <functional>

#include "PTSDVectors.h"
#include "PTSDAssert.h"

namespace CEGUI {
	class EventArgs;
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
	class UIImplementation;
	class InputManager;
	class GraphicsManager;
	/**
	 * \brief Singleton UI Manager
	 */
	class UIManager {
	private:
		static UIManager* mInstance;

		CEGUI::OgreRenderer* renderer;
		CEGUI::Window* mRoot;
		CEGUI::WindowManager* windowMngr;
		CEGUI::System* system;
		Vector2D lastMousePosition;
		std::string mouseCursorName;

	public:
		UIManager() = default;
		~UIManager() = default;

		static UIManager* getInstance()
		{
			PTSD_ASSERT(mInstance != nullptr, "UIManager accessed before initialziation");
			return mInstance;
		}

		static int init();
		bool render();
		void inputUpdate();
		void registerForEvents();
		bool OnButtonClick(const CEGUI::EventArgs& e);
		void shutdown();
		void createRoot();

		void initLogger();
		void setupResources();
		void loadScheme(const std::string& filename);
		void loadFont(const std::string& filename);
		void loadLayout(const std::string& filename);
		void loadResources();

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