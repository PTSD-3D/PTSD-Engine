local ns = require('namespace')

ns.LoadSounds()
LOG("Sounds loaded correctly")
ns.LoadUIElements()
LOG("UI elements loaded correctly")

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
setWindowVisible("PauseWindow", true)
setUIMouseCursor("TaharezLook/MouseArrow")

createButton("PushButton", "CEGUI es facilito",vec2:new(300, 200), vec2:new(200, 50))
setButtonFunction("PushButton","UICallback")

LOG("Test.lua completed")

function UICallback()
	setWindowVisible("TaiFighterWindow", true)
	setWindowVisible("PauseWindow", false)
	setWindowVisible("PushButton", false)
	setUIMouseCursorVisible(false);
end

function ShowPauseUI()
	setWindowVisible("TaiFighterWindow", false)
	setWindowVisible("PauseWindow", true)
	setWindowVisible("PushButton", true)
	setUIMouseCursorVisible(true);
end