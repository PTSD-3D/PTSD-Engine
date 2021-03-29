#pragma once
#ifdef _PTSDGRAPHICS
#define GRAPHICSAPI  __declspec(dllexport)   // export DLL information

#else
#define GRAPHICSAPI  __declspec(dllimport)   // import DLL information

#endif 

namespace PTSD {
	class GRAPHICSAPI Graphics {
	private:
	public:
		static int Init();
		~Graphics() {}
		Graphics() {}
	};
}