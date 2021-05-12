package.path = "./assets/scripts/Client/?.lua;./assets/scripts/Engine/?.lua;./assets/scripts/Engine/Events/?.lua;./asse.luats/scripts/Client/Prefabs/?.lua"

local eng = require('initEngine')
local ns = require('namespace')

local res, err = pcall(eng.initialize,{globals=false})
if not res then
	print(err)
end
Namespace = ns
Manager = ns.EntityManager()

--Make sure EntityLoader exists
require('EntityLoader')
require('ComponentsList')
require('SystemsList')
require('UIcallbacks')

--Resource load
require('resourceLoader')

LOG("Initialized script engine correctly")