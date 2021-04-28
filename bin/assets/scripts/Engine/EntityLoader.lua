local ns = reqNamespace;

--Loads a scene after the whole engine has been initialized
function ns.loadScene(manager, sceneTable)
	local physicsConfig = sceneTable.SceneConfig.PhysicsConfig
	setGravity(physicsConfig["Gravity"])
	LOG(tostring("Gravity set to: " .. physicsConfig["Gravity"]), LogLevel.Trace, 0)
	
	for _, entData in pairs(sceneTable.Entities) do
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
			entityObject.Transform = setTransform(entityObject.id,p,r,s)
		end

		if entData.Mesh then
			entityObject.Mesh = setMesh(entityObject.id, entData.Mesh.mesh,entData.Mesh.material )
		end

		if entData.Rigidbody then
			local size = entData.Rigidbody.size
			local s = vec3:new(size.x, size.y, size.z)

			local position = entData.Rigidbody.position
			local p = vec3:new(position.x, position.y, position.z)

			local rotation = entData.Rigidbody.rotation
			local r = vec4:new(rotation.x, rotation.y, rotation.z, rotation.w)

			entityObject.Rigidbody = setRigidbody(entityObject.id, s, entData.Rigidbody.mass, p, entData.Rigidbody.type, entData.Rigidbody.trigger, r)
		end
	 end
end