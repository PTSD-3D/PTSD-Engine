local namespace = reqNamespace

local Entity = {}

function Entity:new(o)
	o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

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
		print("a1")
		self.components[name] = component
		if self.eventManager then
			self.eventManager:fireEvent(namespace.ComponeentAdded(self,name))
		end
		print("b1")
	end
	print("c1")
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
	if self.components[name] then
		print("found")
	end
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