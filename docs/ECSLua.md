# Guía básica existencial PT:SD Lua ECS

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
## Credit where credit is due

Basado mucho en [lovetoys](https://github.com/lovetoys/lovetoys), libreria ECS de Lua.

La mayor parte de su documentacion nos sirve, por si tenéis alguna duda más a fondo.