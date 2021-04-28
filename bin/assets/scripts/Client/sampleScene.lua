local Scene = {}

Scene = {
	SceneConfig = {
		PhysicsConfig={
			Gravity = 5
		}
	},
	Entities = {
		Entity1={
			--Components are Lua-only components
			--Table of tables, each subTable has name and arguments
			Components = {
			{name="playerMove", arguments={1,1,1}}
		},
			Transform = {position={x=0,y=0,z=-250},rotation={x=0,y=0,z=0},scale={x=1,y=1,z=1}},
			Mesh = {mesh="ogrehead.mesh", material="KirbyMat"},
			Rigidbody = {size={x=1,y=1,z=1},mass=1,position={x=0,y=0,z=0},type=0,trigger=false,rotation={x=0,y=0,z=0,w=1}}
		},
		Entity2={
			Components = {
				{name="playerMove", arguments={1,1,1}}
			},
			Transform = {position={x=-0,y=30,z=-100},rotation={x=-90,y=0,z=0},scale={x=1,y=1,z=1}},
			Mesh = {mesh="Kirby.mesh", material="KirbyMat"}
		}
	}
}

return Scene
