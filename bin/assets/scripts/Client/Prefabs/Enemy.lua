local pf = reqPrefab

-- Params holds required parameters to build an instance of this prefab. This will be populated with transform information from Blender via our script in /tools
function pf.Enemy(params)
	return {
		Components = {
			-- Example user defined components
			{ name = "playerMove", arguments = { 1, 1, 1 } }
			-- { name = "playerMove", arguments = { { x = 1, y = 0, z = 0 } } }
		},
		Transform = params.Transform,
		Mesh = { mesh = "Kirby.mesh", material = "Red" }
	}
end