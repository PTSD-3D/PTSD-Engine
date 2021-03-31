# ECS

## Entity
```c++
namespace ECS
{
	using UUID = unsigned long long; 
	class Entity
	{
		public:
			void setComponent(std::string name, PTSD::Component*  component);
			Component* getComponent(std::string name);
			UUID getID();
		private:
			UUID id;
			std::unordered_map<std::string, PTSD::Component*> components;
	}
}
```
Our entity is a simple component container.

## Components
```c++
namespace ECS{
	class Component{
		public:
			Component() = default;
			virtual ~Component() = default
	};
}
```
Componente base básicamente vacío para que la entidad los pueda guardar todos juntos. (Polimorfismo)

## Ejemplo de componente sencillote

```c++
class Transform : public Component{
	public:
		Transform (): Component(), position(0), rotation(0), scale(1){};
		virtual ~Transform();

		//Repetir con los demás
		PTSD::Math::Vector3 getPosition();
		void setPosition(PTSD::Math::Vector3);
	private:
		PTSD::Math::Vector3 position;
		PTSD::Math::Vector3 rotation;
		PTSD::Math::Vector3 scale;
}
```
No tiene más. Se puede leer y escribir.

## Ejemplo de componente con cositas que hay que esconder

``` c++

// PTSDGraphics.h
class MeshComponent : public Component{
	public:
		MeshComponent (std::string mesh, std::string mat);
		virtual ~MeshComponent();

		std::string getMaterial();
		void setMaterial(UUID,std::string);
	private:
		std::string mesh;
		std::string material;
}


// PTSDGraphics.cpp
#include <EntityManager.h>
#include <Ogre.h>

void MeshComponent::setMaterial(unsigned int id,std::string material)
{
	Graphics::root()->getSceneManager()->getRootSceneNode()->getChild(id)->getAttachedObject(0)->setMaterial(material);
//Esto asume que solo tiene un objeto el nodo,
//si tuviera más habría que, por ejemplo, pasarlo por parámetro
}
```
Bastante sencillo.. podemos asumir que lua va a ser capaz de mandarnos el id cuando llame a los métodos del componente. Porque todas las entidades lo tendrán. Al final para el programador del juego este parametro se oculata. Pero hacerlo así nos ahorra guardarlo en todos los componentes.

### EntityManager
```c++
namespace ECS{
	class Entity;
	class EntityManager
	{
	public:
		Entity * getEntity(uuid id){return entities[id];}

		EntityManager* static get(){
			static EntityManger instance;
			return &instance;}
		private:
		std::unordered_map<uuid, Entity*>entities;
		}
	}
}

```

## Lua stuff

```c++
//ScriptManager.h
class ScriptManager
{
	public:
		void init();
		void update(); //calls update on all entities
		void lateUpdate(); //same with lateUpdate
		void fixedUpdate();
		void start();
		bool addComponent(uuid id, std::string component, std::unrodered_map<std::string, std::string>args); //Only called when it is a user defined component AKA a script
	//...
	private:
		sol::state lua;
};

//ScriptManager.cpp
bool ScriptManager::addComponent(uuid id, std::string component, std::unordered_map<std::string, std::string>args)
{
	return lua["entities"][id]["addScript"](component, args);
}

bool ScriptManager::init()
{
	/*
		Crea una tabla en lua con la lista de entidades.
		
	*/
}
```

