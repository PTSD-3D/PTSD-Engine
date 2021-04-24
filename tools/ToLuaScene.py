from string import Template
import bpy

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
            read_data = file.read()
            return clear_transform(read_data)
        #Prefab dosn't exits, make an empty entity
    except IOError:
        return ('''
        {
            Components= {
            }
        }
        ''')
        
#Given the blender object it populates the entity with its position, rotation and scale
def fill_component(o, entity):
    transform = Template("\n"+
'\t\t\t\t{name="position", arguments={$position}},\n'+
'\t\t\t\t{name="rotation", arguments={$rotation}},\n'+
'\t\t\t\t{name="scale", arguments={$scale}}$coma')
    coma = ""
    if entity.count("{")>2:
        coma=","
    transform = transform.safe_substitute(position=("{0},{1},{2}".format(o.location.x,o.location.y,o.location.z)),
    rotation=("{0},{1},{2}".format(o.rotation_euler[0],o.rotation_euler[1],o.rotation_euler[2])),
    scale=("{0},{1},{2}".format(o.scale[0],o.scale[1],o.scale[2])), coma=coma)
    start_of_components=find_nth(entity,"{", 2) #should point to the start of the components
    entity = entity[:start_of_components+1]+transform+entity[start_of_components+1:]
    return entity


#Writes the blender secne in our lua scene format
def write_scene():
    scene_name=bpy.path.basename(bpy.context.blend_data.filepath).split(".",1)[0]				#Name of the blender scene for
    objects = list(bpy.data.objects)			#Blender Objects on scene
    path_to_prefabs="/home/drathi/DEV/Uni-Tercero/P3/repo/PTSD-Engine/bin/assets/scripts/Client" 			#This is where we will eventually put our "prefabs" 
    path_to_scene = "/home/drathi/DEV/Uni-Tercero/P3/repo/PTSD-Engine/bin/assets/scripts/Client"		#This is where we want our lua scene file to be written
    lua_file = path_to_scene+"/"+scene_name+".lua" 		#This is the name of the lua scene file, right now takes the name of the blend file and changes the extension to lua
    
    f = open(lua_file, "w+")
    f.write("local Scene={\n")
    i = 0
    for o in objects:
            prefab_name = o.name.split(".",1)[0]
            prefab_string = "\t"+o.name.replace(".","_")+"="+fill_component(o,search_component(path_to_prefabs,prefab_name))
            if i < (len(objects)-1):
                    prefab_string = prefab_string+",\n"
            f.write(prefab_string)
    f.write("}\n return Scene\n")
    f.close()

write_scene()
