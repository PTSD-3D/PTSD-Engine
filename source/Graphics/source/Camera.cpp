#include "Camera.h"
#include "CameraImplementation.h"

/**
 * \brief Creates a camera in pos
 * \param pos position
 * \param dir lookAt
 */
PTSD::Camera::Camera(Vec3Placeholder v)
{
	mImplementation = std::make_unique<CameraImplementation>(v);
}


PTSD::Camera::~Camera() = default;

void PTSD::Camera::lookAt(Vec3Placeholder v)
{
	mImplementation->lookAt(v);
}

void PTSD::Camera::translate(Vec3Placeholder v)
{
	mImplementation->translate(v);
}

void PTSD::Camera::setPosition(Vec3Placeholder v)
{
	mImplementation->setPosition(v);
}

void PTSD::Camera::mouseRotate(Vector2D dir)
{
	
}

