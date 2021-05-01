local prefabs = reqPrefab 
local ns = reqNamespace
ns.LoadSounds()
print(Resources.Sounds.PTSD_Anthem.id)
local Scene={
	SceneConfig = {
		PhysicsConfig={
			Gravity = 5
		}
	},
	Entities={	Enemy=prefabs.Enemy({
			Transform = {position={x=0.0,y=0.0,z=-37.56254196166992},rotation={x=-90.0,y=90.0,z=0.0},scale={x=1,y= 4.60,z=1}}},Resources.Sounds.PTSD_Anthem.id)},
			SceneConfig=prefabs.sampleScene({})
}
return Scene
