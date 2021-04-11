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
		TransformComponent* mParent = nullptr;
		std::vector<TransformComponent*> mChildren;
	public:
		TransformComponent();
		~TransformComponent() = default;

		void translate(Vec3Placeholder translation);
		void rotate(Ogre::Quaternion rotation);
		void scale(Vec3Placeholder scale);

		void setPosition(Vec3Placeholder position);
		void setRotation(Ogre::Quaternion rotation);
		void setScale(Vec3Placeholder scale);
		void setParent(TransformComponent* parent);

		Vec3Placeholder getPosition() const;
		Vec3Placeholder getRotation() const;
		Vec3Placeholder getScale() const;
		TransformComponent* getParent() const;
		std::vector<TransformComponent*> getChildren() const;
		Ogre::SceneNode* getNode() const;
	};
}