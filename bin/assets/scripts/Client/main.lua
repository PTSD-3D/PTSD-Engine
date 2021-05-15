local ns = require('namespace')

ns.LoadSounds()
LOG("Sounds loaded correctly")
if (ns.call("Error loading UI",ns.LoadUIElements) ~= false) then LOG("UI elements loaded correctly") end

local status, ret = pcall(ns.loadScene, Manager, require('sampleScene'))
if status then
	LOG("Scene loaded correctly")
else
	local message = tostring("Fatal error loading scene: " .. ret)
	LOG(message, LogLevel.Error, 1)
end
-- Showing component Added event working
--local ents = Manager:getEntitiesWithComponent("playerMove")
--if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end

-- UI Usage example
setUIMouseCursor("TaharezLook/MouseArrow")

setWindowVisible("TitleWindow", true)

createButton("PushButton", "CEGUI es facilito", "TaharezLook/Button",vec2:new(300, 200), vec2:new(200, 50))
setButtonFunction("PushButton","showTaiFighterUI")

createButton("ExitButton", "Exit", "TaharezLook/Button",vec2:new(300, 300), vec2:new(200, 50))
setButtonFunction("ExitButton","exitCallback")

showTaiFighterUI()

LOG("main.lua completed")