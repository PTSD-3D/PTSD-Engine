local namespace = require('namespace')
local ChangeSceneEvent = namespace.class("ChangeSceneEvent")

function ChangeSceneEvent:initialize(newSceneName)
	self.newSceneName = newSceneName
	LOG("Firing ChangeSceneEvent")
end

return ChangeSceneEvent