local ns = reqNamespace

--Define new systems here

LOG("Loading systems...", LogLevel.Info, 1)

local MoveSystem = ns.class("MoveSystem",ns.System)

--data
MoveSystem.sideview = true
MoveSystem.deadzone = 0.1

function MoveSystem:requires() return { "playerMove" } end

function MoveSystem:KeyboardHandleInput()	--Read the input from a keyboard/mouse and sends a commad
	print("owo")
	--[[
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
	]]--
end

function MoveSystem:ControllerHandleInput()	--Read the input from a gamepad and sends a commad
	--[[
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
	]]--
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local playerMoveCom = entity:get("playerMove")
		local vx = playerMoveCom.x
		local vy = playerMoveCom.y
		local vz = playerMoveCom.z
		local speed = vec3:new(vx, vy, vz)
		local action = self.KeyboardHandleInput()
		--if action then action:execute(entity, dt, speed) end
		action = self.ControllerHandleInput()
		--if action then action:execute(entity, dt, speed) end
	end
end

Manager:addSystem(MoveSystem())

-----------------------------------------------------------

LOG("Systems load completed", LogLevel.Info, 1)


