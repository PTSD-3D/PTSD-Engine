#pragma once
#include "PTSDVectors.h"
#include "GraphicsImplementation.h"
#include <OgreSceneManager.h>

namespace Ogre {
	class SceneNode;
}
namespace PTSD {
	class TransformImplementation {
	private:
		Ogre::SceneNode* mNode;
		TransformImplementation* mParent = nullptr;
		std::vector<TransformImplementation*> mChildren;
	public:
		TransformImplementation();
		~TransformImplementation() = default;

		void translate(Vec3Placeholder translation);
		void rotate(Ogre::Quaternion rotation);
		void scale(Vec3Placeholder scale);

		void setPosition(Vec3Placeholder position);
		void setRotation(Ogre::Quaternion rotation);
		void setScale(Vec3Placeholder scale);
		void setParent(TransformImplementation* parent);

		Vec3Placeholder getPosition() const;
		Vec3Placeholder getRotation() const;
		Vec3Placeholder getScale() const;
		TransformImplementation* getParent() const;
		std::vector<TransformImplementation*> getChildren() const;
		Ogre::SceneNode* getNode() const;
	};
}
