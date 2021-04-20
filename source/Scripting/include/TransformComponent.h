#pragma once

#include <memory>
#include "PTSDVectors.h"
#include "GraphicsImplementation.h"
#include <OgreSceneManager.h>
#include "Component.h"

namespace Ogre {
	class SceneNode;
}
namespace PTSD {

	class TransformComponent : public Component {
	private:
		Ogre::SceneNode* mNode;

		//Methods to convert from and to quaternions and vec3
		Vec3Placeholder OgreQuatEuler(const Ogre::Quaternion& quaternion) const;
		Ogre::Quaternion EulerToOgreQuat(const Vec3Placeholder& degreesVector) const;

	public:
		TransformComponent();
		~TransformComponent() = default;

		void translate(Vec3Placeholder translation);
		void translate(float x, float y, float z);
		void rotate(Vec3Placeholder rotation); // It has a little problem with rounding +-(0.00001)
		void rotate(float x, float y, float z); // It has a little problem with rounding +-(0.00001)
		void scale(Vec3Placeholder scale);
		void scale(float x, float y, float z);

		void setPosition(Vec3Placeholder position);
		void setPosition(float x,float y, float z);
		void setRotation(Vec3Placeholder rotation);
		void setRotation(float x, float y, float z);
		void setScale(Vec3Placeholder scale);
		void setScale(float x, float y, float z);

		Vec3Placeholder getPosition() const;
		Vec3Placeholder getRotation() const;
		Vec3Placeholder getScale() const;
		Ogre::SceneNode* getNode() const;
	};
}