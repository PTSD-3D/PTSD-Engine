local namespace = require('namespace')
local ComponentAddedEv = namespace.class("ComponentAddedEv")

function ComponentAddedEv:initialize(entity, componentName)
	self.entity = entity
	self.componentName = componentName
	LOG("Firing ComponentAddedEvent ")
end

return ComponentAddedEv