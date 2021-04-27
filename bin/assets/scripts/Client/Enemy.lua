local pf = reqPrefab
--Params holds required parameters to build an instance of this prefab. This will be populated with transform information from Blender via our script in /tools
function pf.Enemy (params)
	return{
		Components{
			--Example user defined components
			{name="SimpleMove", arguments={{speed=1,int=0}}},
			{name="HP", arguments={MaxHP=10}}
		},
		Transform = params.Transform,
		Mesh = {mesh="Enemy.mesh", material="Enemy.mat"}
	}
end