#include "Component.h"
#include "string.h"

namespace Ogre{class Entity;class SceneNode;}
namespace PTSD{
	class MeshComponent: public Component
	{
	public:
		MeshComponent();
		MeshComponent(const std::string&);
		MeshComponent(const std::string&,const std::string&);
		virtual void init() override;
		void setMesh(const std::string& mesh);
		void setMaterial(const std::string& material);
		const std::string getMesh(){return mMesh_;};
		const std::string getMaterial(){return mMaterial_;};
	
	private:
		Ogre::Entity* getEntity(); //helper function
		Ogre::SceneNode* sceneNode = nullptr;
		std::string mMaterial_;
		std::string mMesh_;
	};
}
