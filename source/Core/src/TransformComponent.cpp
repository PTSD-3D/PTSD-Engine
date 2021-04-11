#include "TransformComponent.h"

namespace PTSD {
	TransformComponent::TransformComponent() : Component(CmpId::Transform) {
		mNode = GraphicsImplementation::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	}

	void TransformComponent::translate(Vec3Placeholder translation) {
		mNode->translate(translation.x, translation.y, translation.z);
	}
	void TransformComponent::rotate(Ogre::Quaternion rotation) {
		mNode->rotate(rotation);
	}
	void TransformComponent::scale(Vec3Placeholder scale) {
		mNode->scale(scale.x, scale.y, scale.z);
	}


	void TransformComponent::setPosition(Vec3Placeholder position) {
		mNode->setPosition(position.x, position.y, position.z);
	}
	void TransformComponent::setRotation(Ogre::Quaternion rotation) {
		mNode->setOrientation(rotation);
	};
	void TransformComponent::setScale(Vec3Placeholder scale) {
		mNode->setScale(scale.x, scale.y, scale.z);
	};
	void TransformComponent::setParent(TransformComponent* parent) {
		parent->getNode()->addChild(mNode);
		mParent = parent;
		parent->getChildren().push_back(this);
	};


	Vec3Placeholder TransformComponent::getPosition() const {
		Ogre::Vector3 v = mNode->getPosition();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	//Vec3Placeholder Transform::getRotation() const {
	//	Vec3Placeholder v = Vec3Placeholder(mNode->getOrientation());
	//	return Vec3Placeholder(v.x,v.y,v.z);
	//}
	Vec3Placeholder TransformComponent::getScale() const {
		Ogre::Vector3 v = mNode->getScale();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	TransformComponent* TransformComponent::getParent() const {
		return mParent;
	}
	std::vector<TransformComponent*> TransformComponent::getChildren() const {
		return mChildren;
	}
	Ogre::SceneNode* TransformComponent::getNode() const {
		return mNode;
	}
}