local ns = require('namespace')
local prefabs = require('Prefab')
local resources = require('resources')

local MoveSystem = ns.class("MoveSystem",ns.System)

--data
MoveSystem.sideview = true
MoveSystem.deadzone = 0.1
MoveSystem.dirs = {
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

function MoveSystem:onAddEntity(entity)
	print(resources.Sounds.Clowning.id)

	--I know this shouldn't be here but it's just a test.
 	playMusic(resources.Sounds.Clowning.id, true)
	changeMusic(resources.Sounds.PTSD_Anthem.id, false)
	pauseMusic()
	--If this doesn't explode it's a good sign
end

function MoveSystem:requires() return { "playerMove" } end

function MoveSystem:Move(entity,dir, delta, speed)
	entity.Transform:translate(dir * delta * speed:magnitude())
end

function MoveSystem:Shoot(entity, delta)
	LOG("PEW")
	local chan = playSound(resources.Sounds.Oof.id)
	setChannelVolume(chan,1)
	ns.spawnEntity(Manager,prefabs.Bullet({
		Transform = {
			position={x=entity.Transform.position.x,y=entity.Transform.position.y,z=entity.Transform.position.z},
			rotation={x=0.0,y=0.0,z=0.0},
			scale={x=1,y= 1,z=1}}}
	))
end

function MoveSystem:Action()
	LOG("Secondary")
end

function MoveSystem:Change()
	self.sideview = not self.sideview
	LOG("Changing view")
end

--Read the input from a keyboard/mouse and sends a commad
function MoveSystem:KeyboardHandleInput(entity,dt,speed)
	--Movement
	local direction = vec3:new(0, 0, 0)
	-- Up and down
	if keyPressed(PTSDKeys.W) then direction = direction + self.dirs.up end
	if keyPressed(PTSDKeys.S) then direction = direction + self.dirs.down end
	-- 2D control
	if keyPressed(PTSDKeys.A) and self.sideview then direction = direction + self.dirs.backward end
	if keyPressed(PTSDKeys.D) and self.sideview then direction = direction + self.dirs.forward end
	-- 3D control
	if keyPressed(PTSDKeys.A) and not self.sideview then direction = direction + self.dirs.left end
	if keyPressed(PTSDKeys.D) and not self.sideview then direction = direction + self.dirs.right end

	self:Move(entity, direction,dt,speed)

	-- Actions (shoot, change, something)
	if keyJustPressed(PTSDKeys.J) or mouseButtonJustPressed(PTSDMouseButton.Right) then
		self:Action()
	end
	if keyJustPressed(PTSDKeys.H) or  mouseButtonJustPressed(PTSDMouseButton.Left) then
		self:Shoot(entity, dt)
	end
	if keyJustPressed(PTSDKeys.Space) then
		self:Change()
	end
	-- UI Pause input
	if keyJustPressed(PTSDKeys.P) then
		showPauseUI();
	end
end

--Read the input from a gamepad and sends a commad
function MoveSystem:ControllerHandleInput(entity,dt,speed)
	local axis = controllerLeftAxis(0)
	local direction = vec3:new(0, 0, 0)
	-- Up and down
	if axis.y < -self.deadzone then direction = direction + self.dirs.up end
	if axis.y > self.deadzone then direction = direction + self.dirs.down end
	-- 2D control
	if axis.x > self.deadzone and self.sideview then direction = direction + self.dirs.forward end
	if axis.x < -self.deadzone and self.sideview then direction = direction + self.dirs.backward end
	-- 3D control
	if axis.x > self.deadzone and not self.sideview then direction = direction + self.dirs.right end
	if axis.x < -self.deadzone and not self.sideview then direction = direction + self.dirs.left end
	self:Move(entity, direction,dt,speed)

	
	-- Actions (shoot, change, something)
	if controllerButtonJustPressed(0, PTSDControllerButtons.B) or controllerRightTrigger(0) > self.deadzone then
		self:Action()
	end
	if controllerButtonJustPressed(0, PTSDControllerButtons.A) or controllerLeftTrigger(0) > self.deadzone then
		self:Shoot(entity, dt)
	end
	if controllerButtonJustPressed(0, PTSDControllerButtons.Y) then
		self:Change()
	end
	
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local playerMoveCom = entity:get("playerMove")
		local vx = playerMoveCom.x
		local vy = playerMoveCom.y
		local vz = playerMoveCom.z
		local speed = vec3:new(vx, vy, vz)
		self:KeyboardHandleInput(entity,dt,speed)
		self:ControllerHandleInput(entity,dt,speed)
	end
end

Manager:addSystem(MoveSystem())