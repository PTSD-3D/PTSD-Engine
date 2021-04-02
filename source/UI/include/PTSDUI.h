#pragma once

namespace PTSD {
	class UIImplementation;

	class UI {
	private:
		static UI* mInstance;
		UIImplementation* mImplementation = nullptr; //private implementation

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
		void shutdown();
	};
}