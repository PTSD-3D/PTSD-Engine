local namespace = require('namespace')

local ComponentRemovedEv = namespace.class("ComponentRemovedEv")

function ComponentRemovedEv:initialize(entity, componentName)
	self.entity = entity
	self.componentName = componentName
end

return ComponentRemovedEv