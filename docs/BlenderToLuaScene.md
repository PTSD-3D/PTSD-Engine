# Blender to Lua Scene - Python script
Script para exportar posiciones de objetos en Blender a escenas en lua. Exporta los objetos tipo Enemy.001 como Enemy_001 y busca el "prefab" Enemy.lua en la ruta definida (si no lo encuentra lo crea sin ningún componente aparte del transform)  y lo instancia con la posicón/rotación/escala del objeto en la escena de Blender.

## Instroucciones
* Montar la escena con los objetos con nombres tipo: `<nombre_del_prefab>.000` `<nombre_del_prefab>.001` ...
* Copiar el script de python en /tools
* Pegar en la pestaña de scripting de Blender
* Sustituir variables de la última función **write_to_scene** según tus paths a "prefabs" y output de scene.lua. Mínimo cambiar:
	* _path_to_prefabs_ 
	* _path_to_scene_ 
* Ejecutar el script

## Notas

### Un ejemplo de "prefab" sería el siguiente:
`Enemy.lua`
```lua 
{
        Components= {
					{name="HP",arguments={10,10,5}}
				},
        Mesh={"enemy.mesh"}
}
```

### Nota sobre prefabs y transform
Mientras se vaya puliendo la importación de transform en archivos de escena se irá puliendo el script, y lo mismo sobre el tema de los prefabs.