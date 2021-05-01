local ns = reqNamespace

ns.loadScene(Manager, sampleScene)
ns.LoadSounds()
LOG("Scene loaded correctly")
-- Showing component Added event working
local ents = Manager:getEntitiesWithComponent("playerMove")
if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")