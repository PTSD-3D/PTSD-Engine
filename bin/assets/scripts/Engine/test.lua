local eng = reqEngine

reqEngine.initialize({globals = true});

eng.Component.create("playerMove", {"x","y","z"})

local MoveSystem = class("MoveSystem",System)

function MoveSystem:requires()
	return {"playerMove"}
end

local Command = class("Command")	--Base class
local MoveCommand = class("MoveCommand", Command)	--Base class

function MoveCommand:initialize(newDir)
	self.dir= newDir
end

function MoveCommand:execute( entity, delta )
	local tr = entity.Transform
	tr:translate(self.dir*delta)
end

local InputHandler = class("InputHandler")
local KeyboardInputHandler = class("KeyboardInputHandler", InputHandler)
function KeyboardInputHandler:initialize(a)
	self.commands = {
		up = MoveCommand:new(vec3:new(0,1,0)),
		down = MoveCommand:new(vec3:new(0,-1,0)), --2d3d
		
		left = MoveCommand:new(vec3:new(0,0,-1)),--3d
		right = MoveCommand:new(vec3:new(0,0,1)),--3d
		
		forward = MoveCommand:new(vec3:new(1,0,0)), --2d
		backward = MoveCommand:new(vec3:new(-1,0,0)) --2d
	}
	self.sideview = true
end
function KeyboardInputHandler:handleInput()
	if keyPressed(PTSDKeys.W) then
		return self.commands.up
	end
	if keyPressed(PTSDKeys.S) then
		return self.commands.down
	end
	
	if keyPressed(PTSDKeys.A) and self.sideview then
		return self.commands.backward
	end
	if keyPressed(PTSDKeys.A) and not self.sideview then
		return self.commands.left
	end

	if keyPressed(PTSDKeys.D) and self.sideview then
		return self.commands.forward
	end
	if keyPressed(PTSDKeys.D) and not self.sideview then
		return self.commands.right
	end
end

local ControllerInputHandler = class("ControllerInputHandler", InputHandler)
function ControllerInputHandler:initialize(deadzone)
	self.commands = {
		up = MoveCommand(vec3:new(0,1,0)), --2d3d
		down = MoveCommand(vec3:new(0,-1,0)), --2d3d

		left = MoveCommand(vec3:new(0,0,-1)),--3d
		right = MoveCommand(vec3:new(0,0,1)),--3d

		forward = MoveCommand(vec3:new(1,0,0)), --2d
		backward = MoveCommand(vec3:new(-1,0,0)) --2d
	}
	self.deadzone = deadzone
	self.sideview = true
	--[[
		subscribe to ChangeViewEvent to syncronize self.sideview
	]]
end
function ControllerInputHandler:handleInput()
	LOG("Handle Input - Controller")
	--2D control method
	if controllerLeftAxis().x > self.deadzone and self.sideview  then
		return self.commands.forward , controllerLeftAxis().x
	end
	if controllerLeftAxis().x < -self.deadzone and self.sideview then
		return self.commands.backward, controllerLeftAxis().x
	end
	--3D control method
	if controllerLeftAxis().x > self.deadzone and not self.sideview then
		return self.commands.right, controllerLeftAxis().x
	end
	if controllerLeftAxis().x < -self.deadzone and not self.sideview then
		return self.commands.left, controllerLeftAxis().x
	end
	----
	if controllerLeftAxis().y > self.deadzone then
		return self.commands.up, controllerLeftAxis().y
	end
	if controllerLeftAxis().y < -self.deadzone then
		return self.commands.down, controllerLeftAxis().y
	end
end

function MoveSystem:init()
		self.keyboardIH = KeyboardInputHandler:new("AAAAAAAAAAAAAA")
-- self.controllerIH = ControllerInputHandler(0.1)
end

function MoveSystem:update(dt)
	if(not self.a)then
		self.a=true
		self:init()
	end
	for _, entity in pairs(self.targets) do
		local vx = entity:get("playerMove").x;
		local vy = entity:get("playerMove").y;
		local vz = entity:get("playerMove").z;
		local speed = vec3:new(vx,vy,vz)
		local act = self.keyboardIH:handleInput()
		act:execute(entity, dt)
		-- local acc, offset = self.controllerIH:handleInput()	--Two variables for the first and second return
		-- acc:execute(entity, dt*speed*offset)
		-- LOG("HAHAHA4")
	end
end

manager = eng.EntityManager()

reqNamespace.loadScene(manager, sampleScene)

manager:addSystem(MoveSystem())