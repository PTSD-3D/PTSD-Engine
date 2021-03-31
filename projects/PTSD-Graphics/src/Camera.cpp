#include "Camera.h"
#include "CameraImpl.h"

/**
 * \brief Creates a camera in pos
 * \param pos position
 * \param dir lookAt
 */
PTSD::Camera::Camera(Vec3_placeholder v)
{
	mImpl = std::make_unique<CameraImpl>(v);
}


PTSD::Camera::~Camera() = default;

void PTSD::Camera::lookAt(Vec3_placeholder v)
{
	mImpl->lookAt(v);
}

void PTSD::Camera::translate(Vec3_placeholder v)
{
	mImpl->translate(v);
}

void PTSD::Camera::setPosition(Vec3_placeholder v)
{
	mImpl->setPosition(v);
}

