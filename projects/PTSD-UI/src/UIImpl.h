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

namespace PTSD {
	class UIImpl {
	private:



		UIImpl() = default;
		static UIImpl* mInstance;
	public:
		static UIImpl* getInstance() {
			if (mInstance == nullptr)
				mInstance = new UIImpl();
			return mInstance;
		}

		int Init();
		bool Render();
		void Shutdown();

		~UIImpl() = default;

	};
}