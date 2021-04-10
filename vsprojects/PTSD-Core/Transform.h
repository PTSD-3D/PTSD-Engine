#pragma once

#include <memory>
#include "PTSDVectors.h"

namespace Ogre {
	class SceneNode;
}
namespace PTSD
{
	class TransformImplementation;
	class Transform {
	private:
		std::unique_ptr<TransformImplementation> mImplementation;//private implementation w Bullet
	public:
		Transform();
		~Transform() = default;

		Vec3Placeholder* getPosition() const;
	};
}