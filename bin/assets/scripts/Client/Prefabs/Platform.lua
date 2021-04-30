local pf = reqPrefab


--Params holds required parameters to build an instance of this prefab. This will be populated with transform information from Blender via our script in /tools
function pf.Platform (params)
	return{
		Components = {
			--Example user defined components
		},
		Transform = params.Transform,
		Mesh = {mesh="Cube.mesh", material="Red"}
        --Rigidbody = {size=params.Transform.scale,mass=1,position=params.Transform.position,type=1,trigger=false,rotation=params.Transform.rotation}
	}
end