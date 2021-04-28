local namespace = reqNamespace

local System = namespace.class("System")

function System:initialize()
	self.targets = {}
	self.active = true
end

--virtual methods to be redefined by other systems
function System:requires() return {} end

function System:onAddEntity(entity) end

function System:onRemoveEntity(entity) end

function System:addEntity(entity)
	self.targets[entity.id] = entity
	self:onAddEntity(entity)
end

function System:removeEntity(entity)
	if self.targets[entity.id] then
		self.targets[entity.id] = nil
		self:onRemoveEntity(entity)
	end
end

function System:componentRemoved(entity, component)
	self:removeEntity(entity)
end

function System:pickRequiredComponents(entity)
	local components = {}
	local requirements = self:requires()

	--TODO add utils
	if type(namespace.util.firstElement(requirements)) == "string" then
		for _, componentName in pairs(requirements) do
			table.insert(components, entity:get(componentName))
		end
	end
	return table.unpack(components)
end

return System