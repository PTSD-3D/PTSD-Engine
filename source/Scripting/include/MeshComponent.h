	#include "Component.h"

namespace Ogre{
	class OgreNode;
}

namespace PTSD{
	class MeshComponent: public Component
	{
	public:
		MeshComponent();
		MeshComponent(const std::string&);
		MeshComponent(const std::string&,const std::string&);
		void setMesh(const std::string& mesh);
		void setMaterial(const std::string& material);
		const std::string getMesh(){return mMesh_;};
		const std::string getMaterial(){return mMaterial_;};
	
	private:
		std::string mMaterial_;
		std::string mMesh_;
		Ogre::OgreNode* mNode_;
	};
}
