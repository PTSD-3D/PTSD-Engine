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
				{name="position",arguments={10000,100000}},
				{name="velocity",arguments={100,100}}
			},
			Mesh = {"ogrehead.mesh"}
		}
	}
}

return Scene