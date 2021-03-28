#pragma once
#ifdef _PTSDGRAPHICS
#define GRAPHICSAPI  __declspec(dllexport)   // export DLL information

#else
#define GRAPHICSAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class GraphicsImpl;

	class GRAPHICSAPI Graphics {
	private:
		static Graphics* m_instance;
		GraphicsImpl* m_impl = nullptr;
	public:
		static Graphics* getInstance()
		{
			if (m_instance == nullptr)
				m_instance = new Graphics();
			return m_instance;
		};
		int Init();
		void renderFrame();
		~Graphics() = default;
		Graphics() = default;
	};
}