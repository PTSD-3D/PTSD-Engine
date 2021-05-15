package.path = "./assets/scripts/Client/?.lua;./assets/scripts/Engine/?.lua;./assets/scripts/Engine/Events/?.lua;./assets/scripts/Client/Prefabs/?.lua"

local eng = require('initEngine')
local ns = require('namespace')

local res, err = pcall(eng.initialize,{globals=false})
if not res then
	print(err)
end
Namespace = ns
require('EngineUtilities')

Manager = ns.EntityManager()

--Make sure EntityLoader exists
ns.call("Fail requiring 'EntityLoader '",require,'EntityLoader')
ns.call("Fail requiring 'ComponentsList '",require,'ComponentsList')
ns.call("Fail requiring 'SystemsList '",require,'SystemsList')
ns.call("Fail requiring 'UIcallbacks '",require,'UIcallbacks')

--Resource load
require('resourceLoader')
	--Load Sounds
if (ns.call("Error loading Sounds",ns.LoadSounds) ~= false) then LOG("Sounds loaded correctly") end
	--Load UI
if (ns.call("Error loading UI",ns.LoadUIElements) ~= false) then LOG("UI elements loaded correctly") end

LOG("Initialized script engine correctly")