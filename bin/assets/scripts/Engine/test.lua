local ns = require('namespace')

ns.LoadSounds()
LOG("Sounds loaded correctly")

local status, ret = pcall(ns.loadScene, Manager, require('sampleScene'))
print("f")
if status then
	print("uee")
	LOG("Scene loaded correctly")
else
	print(ret)
	local message = tostring("Fatal error loading scene: " .. ret)
	LOG(message, LogLevel.Error, 1)
end
-- Showing component Added event working
--local ents = Manager:getEntitiesWithComponent("playerMove")
--if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")