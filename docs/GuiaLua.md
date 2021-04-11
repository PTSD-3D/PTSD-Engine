# Guía básica existencial PT:SD Lua
## Bindeo de funciones
Una funcion de c++ se pueda bindear de varias maneras
```lua
state["nombreDeFuncionEnLua"]= nombreDeFuncionEnCpp;
state.set("nombreDeFuncionEnLua",nombreDeFuncionEnCpp);
state.set_function("nombreDeFuncionEnLua",nombreDeFuncionEnCpp);
```
Si queremos que llame a una funcion de una instancia de un objeto especifico se settea de la siguiente manera
```lua
state.set_function("nombreDeFuncionEnLua",&ClaseCpp::nombreDeFuncionEnCpp,InstanciaDeClaseCpp);
```
---
## ECS

EntityManager se encarga de recibir el input y el deltaTime y pasárselo a las entidades.

Para registrar una entidad basta con llamar a `addEntity(entity)` del manager y se encarga de registarla en los sistemas debidos

### Para crear un componente nuevo en un archivo:
```lua 
local eng = reqEngine

NombreComponente = eng.Component.create("nombreComponente",{"atributo1","atributo2"},{atributo1=valorDefault,atributo2=valorDefault})
```

### Para crear un sistema nuevo en un archivo:
```lua
local eng = reqEngine

NombreSistema = class("NombreSistema",System)

function NombreSistema:requires()
	return {"nombreComponenteRequerido1","nombreComponenteRequerido2"}
end

function NombreSistema:update(args)
	for _, entity in pairs(self.targets) do --En todas las entidades a las que afecte hace x
		local comp1 = entity:get("nombreComponenteRequerido1")
		print(comp1.blah)
	end
end
```
cuando se quiera añadir al juego basta con hacer
```lua
manager:addSystem(NombreSistema())
```

### Para cargar uno de estos archivos creados:
```cpp
state.script_file("./assets/scripts/engine/x.lua");
```
así ya estara disponible en el estado general de lua para ser llamado

--- 
## Creación de escenas en lua

Para crear una escena se ha de crear un archivo lua de la escena y se creará una tabla con las entidades con sus componentes:
* Los componentes de Lua identificados por el nombre y añadiendos sus atributos 
* Los componentes según han sido especificados en C++ de la manera que indica cada uno de sus sistemas

```lua
local Scene = {}

Scene = {
	Entity1={
		Components = {
			{name="componentName1",arguments={101,102}},
			{name="componentName2",arguments={1,1}}
		},
		Mesh = {"ogrehead.mesh"}
	}
}

return Scene
```

---
## Credit where credit is due

Basado mucho en [lovetoys](https://github.com/lovetoys/lovetoys), libreria ECS de Lua.

La mayor parte de su documentacion nos sirve, por si tenéis alguna duda más a fondo.