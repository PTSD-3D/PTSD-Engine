local prefabs = reqPrefab 
local sceneConfig = reqSceneConfigurations 
local Scene={
 Entities={	Enemy=prefabs.Enemy({
		Transform = {position={x=0.0,y=0.0,z=-37.56254196166992},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.098890542984009,y=2.098890542984009,z=2.098890781402588}}})},
		SceneConfig=sceneConfig.sampleScene({})
}
return Scene
