# Blender2Ogre
## Prerrequisitos
+ [Descargar el plugin](https://github.com/OGRECave/blender2ogre/releases/tag/v0.8.0)
+ [Tener Blender](https://github.com/OGRECave/blender2ogre/releases/tag/v0.8.0) 2.8 en adelante
+ [Tener Python](https://www.python.org/downloads/)

## Instalación del plugin
1. Buscar tu instalación de blender
2. Ir a la carpeta "Blender Foundation/Blender 2.*/2.*/scripts/addons/ copiar io_ogre del plugin
3. **Importante para Windows** en la linea 73 de config.py, indicar la dirección en la que está manualmente buscando OgreXMLConverter.exe en PTSD/dependencies/Ogre. **Asegurarse de poner dobles \\ y guardar como administrador los cambios**
4. Activa en plug-in en Preferences/Add-ons
---
## Workflow
1. Modelas y haces cositas chachis
2. **Te aseguras de que tienes seleccionada la malla a exportar**
3. Exportas en formato Ogre a una carpeta vacía
4. Te llevas los assets a su carpeta correspondiente en el motor
5. GG EZ
---
## Mas info en
https://github.com/OGRECave/blender2ogre
