from string import Template
import bpy
import math
from os import path,getcwd
def search_config_file(path, name):
    try:
        #Prefab exits, parse it and return it
        with open(path+"/"+name+"-config.lua") as file:
            t=(Template("sceneConfig.$funcName({})"));
            return t.safe_substitute(funcName=name), True
        #Prefab dosn't exits, make an empty entity
    except IOError:
        return ('''
        {
        PhysicsConfig={
            Gravity = 5
        }
    }''', False)


def write_config(f,path,name):
    f.write("\t\tSceneConfig=")
    ret = search_config_file(path,name)    
    
    f.write(ret[0])
    
    f.write("\n}\n")


#Utility function that finds nth repetition of the substring in the string and returns it position.
#used for the parsing of lua objects
def find_nth(string, substring, n):
   if (n == 1):
       return string.find(substring)
   else:
       return string.find(substring, find_nth(string, substring, n - 1) + 1)


#Reads input strings, finds "position/rotation/scale" and removes it. Lets asume for now
#none of our prefabs have those, just for simplicity :D
def clear_transform(read_data):
    return read_data

#Search for file with name.lua in path and returns its contents. We are assumming here the prefab is defined
#with the first element of the table been Componnets and then the possible Engine components.
#Follow this for now, it will be improve upon once we have a more robust definition of prefabs. This is just for the moment
def search_component(path, name):
    try:
        #Prefab exits, parse it and return it
        with open(path+"/"+name+".lua") as file:
            t=(Template("prefabs.$funcName({})"));
            return t.safe_substitute(funcName=name), True
        #Prefab dosn't exits, make an empty entity
    except IOError:
        return ('''
        {
            Components= {
            }
        }
        ''', False)
        
#Given the blender object it populates the entity with its position, rotation and scale
def fill_component(o, entity,is_prefab):
    transform = Template("\n\t\t"+'Transform = {position={$position},'+'rotation={$rotation},'+'scale={$scale}}$coma')
    coma = ""
    if not is_prefab:
        coma=","
    transform = transform.safe_substitute(position=("x={0},y={1},z={2}".format(-o.location.x,o.location.z,o.location.y)),
    rotation=("x={0},y={1},z={2}".format(-math.degrees(o.rotation_euler[0]),math.degrees(o.rotation_euler[2]),math.degrees(o.rotation_euler[1]))),
    scale=("x={0},y={1},z={2}".format(o.scale[0],o.scale[2],o.scale[1])), coma=coma)
    delimeter = 3 if is_prefab else 1
    before_components=find_nth(entity,"{", delimeter) #should point to the start of the components
    entity = entity[:before_components+1]+transform+entity[before_components+1:]
    return entity

#Chooses the target game from ToLuaScene.cfg, stores in PTSD-Engine/tools/
def load_game_path():
    __location__ = path.realpath(
    path.join(getcwd(), path.dirname(__file__)))
    with open(path.join(__location__,'ToLuaScene.config'),"r") as file:
       lines = file.readlines()
    selection = int(lines[0])+1
    print(selection)
    return lines[selection]


#Writes the blender secne in our lua scene format
def write_scene():
    scene_name="sampleScene"#bpy.path.basename(bpy.context.blend_data.filepath).split(".",1)[0]				#Name of the blender scene
    objects = list(bpy.data.objects)			#Blender Objects on scene
    # path_to_game = load_game_path()
    path_to_game=path.abspath('H:/Dev/Engines/Glock-The-Clock/GlockTheClock/')
    path_to_prefabs=path.join(path_to_game,'assets/scripts/Client/Prefabs')			#This is where we will eventually put our "prefabs" 
    path_to_scene = path.join(path_to_game,'assets/scripts/Client/')		#This is where we want our lua scene file to be written
    lua_file = path.join(path_to_scene,scene_name+'.lua')		#This is the name of the lua scene file, right now takes the name of the blend file and changes the extension to lua
    
    f = open(lua_file, "w+")
    f.write("local prefabs = require('Prefab') \nlocal sceneConfig = require('Prefab') \nlocal Scene={\n Entities={")
    i = 0
    for o in objects:
            prefab_name = o.name.split(".",1)[0]
            component_position=search_component(path_to_prefabs,prefab_name)
            prefab_string = "\t"+o.name.replace(".","_")+"="+fill_component(o,component_position[0],component_position[1])
            if i < (len(objects)-1):    
                prefab_string = prefab_string+",\n"
            f.write(prefab_string)
            i=i+1
    f.write("},\n")
    write_config(f,path_to_prefabs,scene_name)
    f.write("return Scene\n")
    f.close()

write_scene()