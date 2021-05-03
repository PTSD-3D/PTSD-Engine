local pf = reqPrefab

-- Params holds required parameters to build an instance of this prefab. This will be populated with transform information from Blender via our script in /tools
function pf.Kerbo(params)
	return {
		Components = {
		},
		Transform = params.Transform,
		Mesh = { mesh = "Kirby.mesh", material = "KirbyMat" }
	}
end