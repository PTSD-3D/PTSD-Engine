local namespace = reqNamespace
namespace.class = reqMiddleclass

local Entity = namespace.class("Entity")

function Entity:initialize(name)
	self.components = {}
	self.eventManager = nil;
	self.alive = false
	self.name = name
end

--Adds specific component to entity of this type
--Can only have one of each type
function Entity:add(component)
	local name = component.class.name
	print(name)
	if not self.components[name] then
		self.components[name] = component
		if self.eventManager then
			self.eventManager:fireEvent(namespace.ComponentAdded(self,name))
		end
	end
end

function Entity:set(component)
	local name = component.class.name
	if self.components[name] == nil then
		self.add(component)
	else
		self.components[name] = component
	end
end

function Entity:addMultiple(componentList)
	for _, component in pairs(componentList) do
		self:add(component)
	end
end

--Remove component
function Entity:remove(name)
	if self.components[name] then
		self.components[name]  = nil
	end

	if self.eventManager then
		self.eventManager:fireEvent(namespace.ComponentRemoved(self,name))
	end
end

function Entity:get(name)
	return self.components[name]
end

--retrieve value nested in a component
--component.property.property
function Entity:getPath(path)
    local result = self.components
    for str in string.gmatch(path, "([^%.]+)") do
        if result[str] then
            result = result[str]
        else
            return nil
        end
    end
    return result
end

function Entity:has(name)
	return not not self.components[name]
end

function Entity:getComponents()
	return self.components
end

return Entity