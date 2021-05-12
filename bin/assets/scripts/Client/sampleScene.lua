local prefabs = require('Prefab')

local Scene={
	Entities={
		Enemy=prefabs.Enemy({
			Transform = {position={x=0.0,y=0.0,z=-37.56254196166992},rotation={x=-90.0,y=90.0,z=0.0},scale={x=1,y= 4.60,z=1}}})
		},
	SceneConfig=prefabs.sampleScene({})
}

return Scene
