local eng = reqEngine

reqEngine.initialize({globals = true});

eng.Component.create("playerMove", {"x","y","z"})

local MoveSystem = class("MoveSystem",System)

local dir = {
		up = vec3:new(0,1,0),
		down = vec3:new(0,-1,0), --2d3d
		
		left = vec3:new(0,0,-1),--3d
		right = vec3:new(0,0,1),--3d
		
		forward = vec3:new(1,0,0), --2d
		backward = vec3:new(-1,0,0) --2d
}

local sideview = true
local deadzone= 0.1

function MoveSystem:requires()
	return {"playerMove"}
end

local Command = class("Command")	--Base class
local MoveCommand = class("MoveCommand", Command)	--Base class

function MoveCommand:initialize(newDir)
	self.dir= newDir
end

function MoveCommand:execute( entity, delta , speed )
	local tr = entity.Transform
	tr:translate(self.dir * delta * speed:magnitude())
end

function KeyboardHandleInput()
	local direction = vec3:new(0,0,0)

	if keyPressed(PTSDKeys.W) then
		direction = direction + dir.up
	end
	if keyPressed(PTSDKeys.S) then
		direction = direction + dir.down
	end
	
	if keyPressed(PTSDKeys.A) and sideview then
		direction = direction + dir.backward
	end
	if keyPressed(PTSDKeys.A) and not sideview then
		direction = direction + dir.left
	end

	if keyPressed(PTSDKeys.D) and sideview then
		direction = direction + dir.forward
	end
	if keyPressed(PTSDKeys.D) and not sideview then
		direction = direction + dir.right
	end

	return MoveCommand:new(direction:normalize())
end


function ControllerHandleInput()
	local axis = controllerLeftAxis(0)

	local direction = vec3:new(0,0,0)

	--2D control method
	if axis.x > deadzone and sideview  then
		direction = direction + dir.forward --, axis.x
	end
	if axis.x < -deadzone and sideview then
		direction = direction + dir.backward--, axis.x
	end
	--3D control method
	if axis.x > deadzone and not sideview then
		direction = direction + dir.right--, axis.x
	end
	if axis.x < -deadzone and not sideview then
		direction = direction + dir.left--, axis.x
	end
	----
	if axis.y < -deadzone then
		direction = direction + dir.up --, axis.y
	end
	if axis.y > deadzone then
		direction = direction + dir.down --, axis.y
	end
	
	return MoveCommand:new(direction:normalize())
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local vx = entity:get("playerMove").x;
		local vy = entity:get("playerMove").y;
		local vz = entity:get("playerMove").z;
		local speed = vec3:new(vx,vy,vz)

		local action = KeyboardHandleInput()
		if(action) then
			action:execute(entity, dt, speed)
		end
		action = ControllerHandleInput()	--Two variables for the first and second return
		if(action) then
			action:execute(entity, dt, speed)
		end
	end
end

manager = eng.EntityManager()

reqNamespace.loadScene(manager, sampleScene)

manager:addSystem(MoveSystem())