#pragma once
#include "PTSDAssert.h"

namespace CEGUI {
	class EventArgs;
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
		UIImplementation* mImplementation = nullptr; //private implementation
		PTSD::InputManager* inputInstance = nullptr;;
		PTSD::GraphicsManager* graphicsInstance = nullptr;;

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
		bool testCallback(const CEGUI::EventArgs& e);
		void shutdown();
	};
}