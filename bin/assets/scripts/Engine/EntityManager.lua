--Main Entity Manager class

local EntityManager =  reqNamespace.class("EntityManager")

function EntityManager:initialize()
	self.entities = {}

	--List of systems organized by their requirements
	self.singleRequirements = {}
	self.allRequirements = {}

	--lists of entities organized by their components
	self.entityLists = {}

	--TODO eventManager

	self.systems = {}
	self.systems = {}
end

function EntityManager:addEntity(entity)
	-- Assign entity's id
	local nId = #self.entities + 1
	entity.id = nId
	self.entities[entity.id] = entity

	for _, component in pairs(entity.components) do
		local componentName = component.class.name


		--Add entity to each of the entityLists for each component, to be able to get it later
		if not self.entityLists[componentName] then 
			self.entityLists[componentName] = {}
		end
		self.entityLists[componentName][entity.id] = entity

		--Add Entity to relevant Systems if all requirements are ok
		if self.singleRequirements[componentName] then
			for _, system in pairs(self.singleRequirements[componentName]) do
				--Checks requirements and adds entity to the system
				self:checkRequirements(entity,system)
			end
		end
	end
end


function EntityManager:removeEntity(entity)
	if self.entities[entity.id] then
		--Remove the Entity from all Systems and the engine
		for _, component in pairs(entity.components) do
			local componentName = component.class.name
			if self.singleRequirements[componentName] then
				for _, system in pairs(self.singleRequirements[componentName]) do
					system:removeEntity(entity)
				end
			end
		end

		--Remove Entity from the entity lists
		for _, component in pairs(entity.components) do
			self.entityLists[component.class.name][entity.id] = nil
		end

		-- Set entity to dead for systems that have a reference saved to the entity
		self.entities[entity.id].alive = false

		-- Finally remove entity
		self.entities[entity.id] = nil
	end
end

function EntityManager:addSystem(system)
	local systemName = system.class.name

	if self.systems[systemName] and self.systems[systemName] ~= system then
		print("Error: System already added")
		return
	end

	--Add system to registry if not already present
	if not (self.systems[systemName]) then
		print("registering ".. systemName)
		self:registerSystem(system)
	end

	-- Checks if some of the already existing entities match the required components.
    for _, entity in pairs(self.entities) do
        self:checkRequirements(entity, system)
    end

	return system
end

function EntityManager:registerSystem(system)
	local systemName = system.class.name
	self.systems[systemName] = system
	table.insert(self.systems,system)

	--system:requires() returns a table of strings
	for index, req in pairs(system:requires()) do
		--Registering in singleRequirements
		if index == 1 then
			self.singleRequirements[req] = self.singleRequirements[req] or {}
			table.insert(self.singleRequirements[req], system)
		end
		--register at allRequirements
		self.allRequirements[req] = self.allRequirements[req] or {}
		table.insert(self.allRequirements[req],system)
	end
end

function EntityManager:stopSystem(name)
	if self.systems[name] then
		self.systems[name].active = false
	else
		print("Can't stop: System name not registered")
	end
end

function EntityManager:startSystem(name)
	if self.systems[name] then
		self.systems[name].active = true
	else
		print("Can't start: System name not registered")
	end
end

function EntityManager:toggleSystem(name)
	if self.systems[name] then
		self.systems[name].active = not self.systems[name].active
	else
		print("Can't toggle: System name not registered")
	end
end

function EntityManager:update(...)
	for _, system in ipairs(self.systems) do
		if system.active then
			system:update(...)
		end
	end
end

-- TODO Component added and removed events

-- Returns list with specific component.
function EntityManager:getEntitiesWithComponent(component)
	if self.entityLists[component] then
		return self.entityLists[component]
	else
		return {}
	end
end

function EntityManager:checkRequirements(entity, system) 
	local meetsRequirements = true
	
	for _, requirement in pairs(system:requires()) do
		if not entity.components[requirement] then
			meetsRequirements = false
			break
		end
	end
	if meetsRequirements == true then
		system:addEntity(entity)
	end
end

return EntityManager