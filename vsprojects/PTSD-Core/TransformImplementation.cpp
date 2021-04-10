#include "TransformImplementation.h"

namespace PTSD {
	TransformImplementation::TransformImplementation() {
		mNode = GraphicsImplementation::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	}

	void TransformImplementation::translate(Vec3Placeholder translation) {
		mNode->translate(translation.x, translation.y, translation.z);
	}
	void TransformImplementation::rotate(Ogre::Quaternion rotation) {
		mNode->rotate(rotation);
	}
	void TransformImplementation::scale(Vec3Placeholder scale) {
		mNode->scale(scale.x, scale.y, scale.z);
	}


	void TransformImplementation::setPosition(Vec3Placeholder position) {
		mNode->setPosition(position.x, position.y, position.z);
	}
	void TransformImplementation::setRotation(Ogre::Quaternion rotation) {
		mNode->setOrientation(rotation);
	};
	void TransformImplementation::setScale(Vec3Placeholder scale) {
		mNode->setScale(scale.x, scale.y, scale.z);
	};
	void TransformImplementation::setParent(TransformImplementation* parent) {
		parent->getNode()->addChild(mNode);
		mParent = parent;
		parent->getChildren().push_back(this);
	};


	Vec3Placeholder TransformImplementation::getPosition() const {
		Ogre::Vector3 v = mNode->getPosition();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	//Vec3Placeholder TransformImplementation::getRotation() const {
	//	Vec3Placeholder v = Vec3Placeholder(mNode->getOrientation());
	//	return Vec3Placeholder(v.x,v.y,v.z);
	//}
	Vec3Placeholder TransformImplementation::getScale() const {
		Ogre::Vector3 v = mNode->getScale();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	TransformImplementation* TransformImplementation::getParent() const {
		return mParent;
	}
	std::vector<TransformImplementation*> TransformImplementation::getChildren() const {
		return mChildren;
	}
	Ogre::SceneNode* TransformImplementation::getNode() const {
		return mNode;
	}
}