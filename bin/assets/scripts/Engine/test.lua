local ns = reqNamespace

ns.LoadSounds()
LOG("Sounds loaded correctly")
local status, ret = pcall(ns.loadScene, Manager, sampleScene)
if status then
	LOG("Scene loaded correctly")
else
	local message = tostring("Fatal error loading scene: " .. ret)
	LOG(message, LogLevel.Error, 1)
end
-- Showing component Added event working
--local ents = Manager:getEntitiesWithComponent("playerMove")
--if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
createButton("PushButton", "CEGUI es facilito",vec2:new(300, 400), vec2:new(200, 50))
setButtonFunction("PushButton","UICallback")
LOG("Test.lua completed")

function UICallback()
	setWindowVisible("PrettyImage", false)
	setWindowVisible("PrettyText", false)
	setWindowVisible("PushButton", false)
	setWindowVisible("DemoWindow", false)
end