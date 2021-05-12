#pragma once
#include <string>
#include <functional>

#include "PTSDVectors.h"
#include "PTSDAssert.h"

using namespace std;

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
	enum UIFileType
	{
		Scheme = 0,
		Font,
		Layout,
		NonType, // really, really not recommended
	};

	class ScriptManager;
	/**
	 * \brief Singleton UI Manager
	 */
	class UIManager {
	private:
		static UIManager* mInstance;

		ScriptManager* mScriptManager;

		CEGUI::OgreRenderer* renderer;
		CEGUI::Window* mRoot;
		CEGUI::WindowManager* windowMngr;
		CEGUI::System* system;
		Vector2D lastMousePosition;
		std::string mouseCursorName;

		unordered_map<string, string> umap;

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
		void shutdown();
		void createRoot();
		void initLogger();
		void setupResources();
		void setScriptManager(ScriptManager* sm) {mScriptManager = sm;}

		bool OnButtonClick(const CEGUI::EventArgs& e);

		void loadScheme(const std::string& filename);
		void loadFont(const std::string& filename);
		void loadLayout(const std::string& filename);
		void loadUIFile(const std::string& path, UIFileType type);

		void createText(const std::string& name, const std::string& text, Vector2D position, Vector2D size);
		void createStaticImage(const std::string& name, const std::string& source, Vector2D position, Vector2D size);
		void createButton(const std::string& name, const std::string& text, Vector2D position, Vector2D size);
		void setUIMouseCursor(const std::string& name);
		void setUIMouseCursorVisible(bool active);
		void setUIMouseInitialPosition(Vector2D mousePosition);
		void setText(const std::string& name, const std::string& text);
		void setStaticImage(const std::string& name, const std::string& image);
		void setWindowVisible(const std::string& name, bool visible);

		void setButtonFunction(const std::string& name, const std::string& functionName);

		CEGUI::Window* getWindow(const std::string name);
		CEGUI::PushButton* getPushButton(const std::string& name);

		void injectMousePosition(Vector2D mousePosition);
		void injectMouseLeftClick();
	};
}