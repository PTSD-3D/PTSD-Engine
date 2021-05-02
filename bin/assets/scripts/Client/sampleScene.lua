local prefabs = reqPrefab
local sceneConfig = reqSceneConfigurations
local Scene = {
	Entities = {
		Entity1={
			--Components are Lua-only components
			--Table of tables, each subTable has name and arguments
			Components = {
			{name="playerMove", arguments={100,3,1000}}
		},
			Transform = {position={x=0,y=0,z=-50},rotation={x=0,y=180,z=0},scale={x=1,y=1,z=1}},
			Mesh = {mesh="ogrehead.mesh", material="KirbyMat"},
			Rigidbody = {size={x=1,y=1,z=1},mass=1,position={x=0,y=0,z=0},type=0,trigger=false,rotation={x=0,y=0,z=0,w=1}}
		},
		Entity2={
			Components = {
			},
			Transform = {position={x=0,y=0,z=-300},rotation={x=-90,y=0,z=0},scale={x=10,y=10,z=10}},
			Mesh = {mesh="Kirby.mesh", material="KirbyMat"}
		}
	},
	SceneConfig = sceneConfig.sampleScene{}
}
return Scene