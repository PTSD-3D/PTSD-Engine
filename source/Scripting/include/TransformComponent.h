#pragma once

#include <memory>
#include "PTSDVectors.h"
#include "GraphicsImplementation.h"
#include <OgreSceneManager.h>
#include "Component.h"
#include "Camera.h"

namespace Ogre {
	class SceneNode;
}
namespace PTSD {

	class TransformComponent : public Component {
	private:
		Ogre::SceneNode* mNode;

		//Methods to convert from and to quaternions and vec3
		Vec3 OgreQuatEuler(const Ogre::Quaternion& quaternion) const;
		Ogre::Quaternion EulerToOgreQuat(const Vec3& degreesVector) const;

	public:
		TransformComponent();
		TransformComponent(Vec3 p, Vec3 r, Vec3 s);
		~TransformComponent() = default;

		void translate(Vec3 translation);
		void translate(float x, float y, float z);
		void rotate(Vec3 rotation); // It has a little problem with rounding +-(0.00001)
		void rotate(float x, float y, float z); // It has a little problem with rounding +-(0.00001)
		void scale(Vec3 scale);
		void scale(float x, float y, float z);

		void setPosition(Vec3 position);
		void setPosition(float x,float y, float z);
		void setRotation(Vec3 rotation);
		void setRotation(float x, float y, float z);
		void setScale(Vec3 scale);
		void setScale(float x, float y, float z);
		void setChildCamera();

		Vec3 getPosition() const;
		Vec3 getRotation() const;
		Vec3 getScale() const;
		Vec3 getForward() const;
		Vec3 getRight() const;
		Ogre::SceneNode* getNode() const;
	};
}