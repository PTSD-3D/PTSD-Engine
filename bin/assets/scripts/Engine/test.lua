local ns = reqNamespace

LOG("Starting scene load")
ns.loadScene(Manager, sampleScene)
LOG("Scene loaded correctly")
-- Showing component Added event working
--local ents = Manager:getEntitiesWithComponent("playerMove")
--if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")
