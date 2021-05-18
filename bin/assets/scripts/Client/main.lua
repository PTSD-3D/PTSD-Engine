local ns = require('namespace')



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

createButton("PushButton", "CEGUI es facilito", "TaharezLook/Button", "DejaVuSans-24",vec2:new(300, 200), vec2:new(200, 50))
setButtonFunction("PushButton","showTaiFighterUI")

createButton("ExitButton", "Exit", "TaharezLook/Button", "DejaVuSans-12",vec2:new(300, 300), vec2:new(200, 50))
setButtonFunction("ExitButton","exitCallback")

showTaiFighterUI()

LOG("main.lua completed")