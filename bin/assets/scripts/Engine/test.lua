local ns = reqNamespace

ns.LoadSounds()
LOG("Sounds loaded correctly")
ns.loadScene(Manager, sampleScene)
LOG("Scene loaded correctly")
-- Showing component Added event working
--local ents = Manager:getEntitiesWithComponent("playerMove")
--if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")