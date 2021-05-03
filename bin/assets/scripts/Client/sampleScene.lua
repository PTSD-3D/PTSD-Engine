local prefabs = reqPrefab 
local Scene={
 Entities={	
	Player=prefabs.Player({
		Transform = {position={x=0.0,y=0.0,z=-37.56254196166992},rotation={x=0.0,y=180.0,z=0.0},scale={x=1,y= 1,z=1}}
	}),
	Kerbo=prefabs.Kerbo({
		Transform = {position={x=0.0,y=0.0,z=-150},rotation={x=-90.0,y=90.0,z=0.0},scale={x=10,y= 10,z=10}}
	}),
},
		SceneConfig=prefabs.sampleScene({})
}
return Scene
