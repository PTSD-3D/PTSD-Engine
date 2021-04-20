local ns = reqNamespace;

--Sets a Transform table to the entityObject to call functions without having to pass the id everytime
local function setLuaTransform(entityObject)
	function _translate(vec3)
		translate(entityObject.id, vec3)
	end
	function _rotate(vec3)
		rotate(entityObject.id, vec3)
	end
	function _scale(vec3)
		scale(entityObject.id, vec3)
	end
	entityObject.Transform = {translate = _translate, rotate = _rotate, scale = _scale}
end

--Loads a scene after the whole engine has been initialized
function ns.loadScene(manager, sceneTable)
	for _, entData in pairs(sceneTable) do
		local entityObject = ns.Entity()
		entityObject:initialize()

		--Loads all components
		if entData.Components ~= {} then
			for _, compDetails in pairs(entData.Components) do
				entityObject:add(ns.Component.all[compDetails["name"]](table.unpack(compDetails["arguments"])))
			end
		end

		--[[Entity is added to manager after adding components to prevent
		firing componentAdded event various times--]]
		manager:addEntity(entityObject)

			if entData.Transform then
				local location = entData.Transform.position
				local p = vec3:new(location.x, location.y, location.z)

				local rotation = entData.Transform.rotation
				local r = vec3:new(rotation.x, rotation.y, rotation.z)

				local scale = entData.Transform.scale
				local s = vec3:new(scale.x, scale.y, scale.z)
				print(entityObject.id)
				setTransform(entityObject.id,p,r,s)
				setLuaTransform(entityObject)
			end
			if entData.Mesh then
				setMeshComponent(entityObject.id, entData.Mesh.mesh,entData.Mesh.material )
		end
	 end
end