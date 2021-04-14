local ns = reqNamespace;

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

		if entData.Mesh ~= {} then
			--Add cpp mesh data to cpp entity
			--xd(entData.Mesh[1])
		end

		if entData.Rigidbody ~= {} then
			--Añadir el componente RigidBody jajasi
		end
	 end
end