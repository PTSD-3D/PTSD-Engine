local namespace = require('namespace')
local EventManager = namespace.class("EventManager")

function EventManager:initialize()
	--in each event a table of {listener, listenerFunction}
	self.eventListeners = {}
end

--Add eventListener to event
function EventManager:addListener(eventName, listener, listenerFunction)
	if not self.eventListeners[eventName] then
		self.eventListeners[eventName] = {}
	end

	if not listener.class or (listener.class and not listener.class.name) then
		LOG("EventManager error: The listener has to have a class name")
	end

	for _, registeredListener in pairs(self.eventListeners[eventName]) do
		if registeredListener[1].class == listener.class then
			LOG("EventManager: EventListener already exists")
			return
		end	
	end

	if type(listenerFunction) == 'function' then
		table.insert(self.eventListeners[eventName], {listener,listenerFunction})
	else
		LOG("EventManager error: Third argument must be a function, event: " .. eventName)
	end
end

function EventManager:removeListener(eventName, listener)
	if self.eventListeners[eventName] then
		for key, registeredListener in pairs(self.eventListeners[eventName]) do
			if registeredListener[1].class.name == listener then
				table.remove(self.eventListeners[eventName],key)
				return
			end
		end
	end
end

function EventManager:fireEvent(event)
	local name = event.class.name
	if self.eventListeners[name] then
		for _, listener in pairs(self.eventListeners[name]) do
			listener[2](listener[1],event)
		end
	end
end

return EventManager