local ns = reqNamespace;

--Loads a scene after the whole engine has been initialized
function ns.loadScene(sceneTable)
	for _, entData in pairs(sceneTable) do
		local entityObject = ns.Entity()
		entityObject:initialize()
		if entData.Components ~= {} then
			--TODO load lua components
		end

		--[[Entity is added to manager after adding components to prevent
		firing componentAdded event various times--]]
		ns.EntityManager:addEntity(entityObject)

		if entData.Mesh ~= {} then
			--Add cpp mesh data to cpp entity
			--xd(entData.Mesh[1])
		end
	 end
end