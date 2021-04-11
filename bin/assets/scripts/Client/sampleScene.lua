local Scene = {}

Scene = {
	Entity1={
		--Components are Lua-only components
		--Table of tables, each subTable has name and arguments
		Components = {
			{name="position",arguments={101,102}},
			{name="velocity",arguments={1,1}}
		},
		Mesh = {"ogrehead.mesh"}
	}
}

return Scene