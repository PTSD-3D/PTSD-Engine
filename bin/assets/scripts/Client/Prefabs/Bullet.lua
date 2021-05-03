local pf = reqPrefab

-- Params holds required parameters to build an instance of this prefab. This will be populated with transform information from Blender via our script in /tools
function pf.Bullet(params)
	return {
		Components = {
			-- Example user defined components
			{ name = "bullet", arguments = {1,3,100} }
		},
		Transform = params.Transform,
		Mesh = { mesh = "Kirby.mesh", material = "body" },
		Rigidbody = {size=params.Transform.scale,mass=1,position=params.Transform.position,type=2,trigger=true,rotation=params.Transform.rotation}
	}
end