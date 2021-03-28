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

	/**
	 * \brief Renders a frame!
	 * \return True on success
	 */
	bool Graphics::renderFrame()
	{
		return m_impl->renderFrame();
	}
}
