local eng = reqEngine
local ns = reqNamespace

eng.initialize{ globals = false }

eng.Component.create("playerMove", { "x", "y", "z" })
eng.Component.create("topo")

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

function KeyboardHandleInput()	--Read the input from a keyboard/mouse and sends a commad
	local direction = vec3:new(0, 0, 0)
	-- Up and down
	if keyPressed(PTSDKeys.W) then direction = direction + dir.up end
	if keyPressed(PTSDKeys.S) then direction = direction + dir.down end
	-- 2D control
	if keyPressed(PTSDKeys.A) and sideview then direction = direction + dir.backward end
	if keyPressed(PTSDKeys.D) and sideview then direction = direction + dir.forward end
	-- 3D control
	if keyPressed(PTSDKeys.A) and not sideview then direction = direction + dir.left end
	if keyPressed(PTSDKeys.D) and not sideview then direction = direction + dir.right end
	-- Actions (shoot, change, something)
	if keyJustPressed(PTSDKeys.J) or mouseRightClick() then return Action() end
	if keyJustPressed(PTSDKeys.H) or mouseLeftClick() then return Shoot() end
	if keyJustPressed(PTSDKeys.Space) then return Change() end
	return Move(direction:normalize())
end

function ControllerHandleInput()	--Read the input from a gamepad and sends a commad
	local axis = controllerLeftAxis(0)
	local direction = vec3:new(0, 0, 0)
	-- Up and down
	if axis.y < -deadzone then direction = direction + dir.up end
	if axis.y > deadzone then direction = direction + dir.down end
	-- 2D control
	if axis.x > deadzone and sideview then direction = direction + dir.forward end
	if axis.x < -deadzone and sideview then direction = direction + dir.backward end
	-- 3D control
	if axis.x > deadzone and not sideview then direction = direction + dir.right end
	if axis.x < -deadzone and not sideview then direction = direction + dir.left end
	-- Actions
	if controllerButtonJustPressed(0, PTSDControllerButtons.B) or controllerRightTrigger(0) > deadzone then return Action() end
	if controllerButtonJustPressed(0, PTSDControllerButtons.A) or controllerLeftTrigger(0) > deadzone then return Shoot() end
	if controllerButtonJustPressed(0, PTSDControllerButtons.Y) then return Change() end
	return Move(direction:normalize())
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local vx = entity:get"playerMove".x
		local vy = entity:get"playerMove".y
		local vz = entity:get"playerMove".z
		local speed = vec3:new(vx, vy, vz)
		local action = KeyboardHandleInput()
		if action then action:execute(entity, dt, speed) end
		action = ControllerHandleInput()
		if action then action:execute(entity, dt, speed) end
	end
end

LOG("Loading manager")
Manager = eng.EntityManager()
LOG("Manager created correctly")
ns.loadScene(Manager, sampleScene)
LOG("Scene loaded correctly")
Manager:addSystem(MoveSystem())
-- Showing component Added event working
local ents = Manager:getEntitiesWithComponent"playerMove"
if ents ~= {} then ents[1]:add(ns.Component.all["topo"]()) end
LOG("Test.lua completed")