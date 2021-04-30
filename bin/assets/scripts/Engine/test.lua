local ns = reqNamespace

--eng.initialize{ globals = false }

--ns.Component.create("playerMove", { "x", "y", "z" })
--ns.Component.create("topo")

local MoveSystem = ns.class("MoveSystem", ns.System)
local dir = {
	-- 2d3d
	up = vec3:new(0, 1, 0),
	down = vec3:new(0, -1, 0),
	-- 3d
	left = vec3:new(0, 0, -1),
	right = vec3:new(0, 0, 1),
	-- 2d
	forward = vec3:new(1, 0, 0),
	backward = vec3:new(-1, 0, 0)
}
local sideview = true
local deadzone = 0.1

function MoveSystem:requires() return { "playerMove" } end
-- Base command class
local Command = ns.class("Command")
function Command:initialize() end
-- Command types
local Move = ns.class("Move", Command)
local Change = ns.class("Change", Command)
local Shoot = ns.class("Shoot", Command)
local Action = ns.class("Action", Command)

function Move:initialize(newDir) self.dir = newDir end

function Move:execute(entity, delta, speed)
	entity.Transform:translate(self.dir * delta * speed:magnitude())
end

function Action:execute()
	-- TODO Acción
	LOG"Secondary"
end

function Shoot:execute()
	-- TODO Disparar
	LOG"PEW"
end

function Change:execute()
	-- TODO Mover la camara de verdad
	sideview = not sideview
	LOG"Change"
end

LOG("Manager created correctly")
ns.loadScene(Manager, sampleScene)
LOG("Scene loaded correctly")
-- Showing component Added event working
local ents = Manager:getEntitiesWithComponent("playerMove")
if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")