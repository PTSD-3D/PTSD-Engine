#include <iostream>
#include "PTSDGraphics.h"
#include "GraphicsImpl.h"

namespace PTSD {
	Graphics* Graphics::m_instance = nullptr;
	int Graphics::Init() {
		m_impl = new GraphicsImpl();
		m_impl->Init();
		return 0;
	}

	void Graphics::renderFrame()
	{
		m_impl->renderFrame();
	}
}
