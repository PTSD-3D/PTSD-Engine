local ns = require('namespace')

function ns.spawnEntity(manager, entData)
	local entityObject = ns.Entity()
	entityObject:initialize()
	-- Loads all components
	if entData.Components ~= {} then
		for _, compDetails in pairs(entData.Components) do
			entityObject:add(ns.Component.all[compDetails["name"]](table.unpack(compDetails["arguments"])))
		end
	end
	manager:registerEntity(entityObject)
	--print(entityObject)
	if entData.Transform then
		local location = entData.Transform.position
		local p = vec3:new(location.x, location.y, location.z)
		local rotation = entData.Transform.rotation
		local r = vec3:new(rotation.x, rotation.y, rotation.z)
		local scale = entData.Transform.scale
		local s = vec3:new(scale.x, scale.y, scale.z)
		entityObject.Transform = setTransform(entityObject.id, p, r, s)
		if entData.Mesh then
			entityObject.Mesh = setMesh(entityObject.id, entData.Mesh.mesh, entData.Mesh.material)
		end
		if entData.Rigidbody then
			local size = entData.Rigidbody.size
			local s = vec3:new(size.x, size.y, size.z)
			local position = entData.Rigidbody.position
			local p = vec3:new(position.x, position.y, position.z)
			local rotation = entData.Rigidbody.rotation
			local r = vec3:new(rotation.x, rotation.y, rotation.z)
			entityObject.Rigidbody = setRigidbody(entityObject.id, s, entData.Rigidbody.mass, p, entData.Rigidbody.type, entData.Rigidbody.trigger, r)
		end
	end
	--[[
		Entity is added to manager after adding components to prevent
		firing componentAdded event various times--
	]]
	manager:addEntity(entityObject)
end

-- Calls engine functions based on config table
function ns.processSceneConfig(config)
	local physicsConfig = config.PhysicsConfig
	if  physicsConfig then
		setGravity(physicsConfig.Gravity)
		LOG(tostring("Gravity set to: " .. physicsConfig.Gravity), LogLevel.Trace, 0)
	end

	local graphicsConfig = config.GraphicsConfig
	if graphicsConfig then
		--Mouse
		local lockMouse = graphicsConfig.LockMouse
		setMouseLocked(lockMouse)
		if lockMouse then LOG("Mouse locked") else LOG("Mouse not locked") end
		--Skybox
		if graphicsConfig.Skybox then
			local skybox = graphicsConfig.Skybox
			if skybox.type == ns.SkyboxTypes.Skybox  then
				setSkybox(skybox.enable, skybox.material, skybox.distance, skybox.renderFirst or true) --Default value of true
			elseif skybox.type == ns.SkyboxTypes.Skydome then
				setSkydome(skybox.enable, skybox.material, skybox.curvature, skybox.repetitions)
			else
				-- setSkyplane(skybox.enable, skybox.material, skybox.curvature, skybox.repetitions)
				LOG("not supported skybox type", LogLevel.Error)
			end
			--* Skybox (enable,material,distance, renderFirst)
			--* Skydome (enable, material, curvature {recomended: 2-65}, tiled repetitions)
			--* Skyplane (enable, plane, material, units, tiled repetitions)
		end
	end
end

-- Loads a scene after the whole engine has been initialized
function ns.loadScene(manager, sceneTable)
	ns.processSceneConfig(sceneTable.SceneConfig)
	for _, entData in pairs(sceneTable.Entities) do
		local entityObject = ns.Entity()
		entityObject:initialize()
		-- Loads all components
		if entData.Components ~= {} then
			for _, compDetails in pairs(entData.Components) do
				if not ns.Component.all[compDetails.name] then error(string.format("Attempting to add not existing component '%s' ",compDetails.name)) end
				entityObject:add(ns.Component.all[compDetails["name"]](table.unpack(compDetails["arguments"])))
			end
		end
		--[[
			Entity is added to manager after adding components to prevent
			firing componentAdded event various times--
		]]
		ns.spawnEntity(manager, entData)
	end
end