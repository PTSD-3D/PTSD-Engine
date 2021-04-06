#pragma once

namespace CEGUI {
	class EventArgs;
}

namespace PTSD {
	class UIImplementation;
	class Input;
	class Graphics;
	/**
	 * \brief Singleton UI Manager
	 */
	class UI {
	private:
		static UI* mInstance;
		UIImplementation* mImplementation = nullptr; //private implementation
		PTSD::Input* inputInstance = nullptr;;
		PTSD::Graphics* graphicsInstance = nullptr;;

	public:
		UI() = default;
		~UI() = default;

		static UI* getInstance()
		{
			if (mInstance == nullptr)
				mInstance = new UI();
			return mInstance;
		}

		int init();
		bool render();
		void inputUpdate();
		void registerForEvents();
		bool testCallback(const CEGUI::EventArgs& e);
		void shutdown();
	};
}