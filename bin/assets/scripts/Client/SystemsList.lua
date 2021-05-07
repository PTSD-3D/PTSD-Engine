local ns = reqNamespace
local prefabs = reqPrefab

LOG("Loading systems...", LogLevel.Info, 1)

--Define new systems here

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

function MoveSystem:requires() return { "playerMove" } end

function MoveSystem:Move(entity,dir, delta, speed)
	entity.Transform:translate(dir * delta * speed:magnitude())
end

function MoveSystem:Shoot(entity, delta)
	LOG("PEW")
	local chan = playSound(Resources.Sounds.Oof.id)
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

-----------------------------------------------------------

local SoundSystem = ns.class("SoundSystem",ns.System)

function SoundSystem:requires()
	return {"boombox"}
end

function SoundSystem:onPlay(music)
	if music.channel == -1 then 
		--we play for the first time
		music.channel = playSound(music.sound.id)
	else
		resumeChannel(music.channel)
	end

end

function SoundSystem:onStop(music)
	pauseChannel(music.channel)
end

function SoundSystem:setVolume(music)
	setChannelVolume(music.channel,music.volume)
end

function SoundSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local music = entity:get("boombox")
		if keyJustPressed(PTSDKeys.Q) then
			--it just cant be initialized to false srry
			if music.isPlaying == nil then
				music.isPlaying = false
			end
			if music.isPlaying then
				music.isPlaying = false
				self:onStop(music)
			else
				music.isPlaying = true
				self:onPlay(music)				
			end
		end
		if music.channel == -1 then
			return
		end
		if keyJustPressed(PTSDKeys.R) and music.volume <= 1 then
			music.volume = music.volume + 0.1
			self:setVolume(music)
		elseif keyJustPressed(PTSDKeys.F) and music.volume > 0 then
			music.volume = music.volume - 0.1
			self:setVolume(music)
		end
	end
end

Manager:addSystem(SoundSystem())
-----------------------------------------------------------

local BulletSystem = ns.class("BulletSystem",ns.System)

function BulletSystem:requires() return {"bullet"} end

function BulletSystem:initialize()
		ns.System.initialize(self)
		Manager.eventManager:addListener("CollisionEv", self, self.Collision)
		self.factor = 1
		self.collided = {}
end

function BulletSystem:CheckCollided(ev)
	if not self.collided[ev.entityAID] then
		self.collided[ev.entityAID] = {}
	end
	if not self.collided[ev.entityBID] then
		self.collided[ev.entityABID] = {}
	end
end

function BulletSystem:CollisionTest(id)
	local ent = Manager:getEntity(id)
	ent.Mesh:setMaterial("Red")
	ent.Transform:translate(vec3:new(self.factor*10*math.random(-1,1),self.factor*10*math.random(-1,1),self.factor*10*math.random(-1,1)))
end

function BulletSystem:Collision(ev)
	self:CheckCollided(ev)
	if not (self.collided[ev.entityAID][ev.entityBID] and self.collided[ev.entityBID][ev.entityAID]) then
		ev:print()
		
		self:CollisionTest(ev.entityAID)
		self:CollisionTest(ev.entityBID)
		
		self.collided[ev.entityAID][ev.entityBID]  = true
		self.collided[ev.entityBID][ev.entityAID] = true
		
		self.factor = self.factor+1
	end
end
function BulletSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local bulletInfo = entity:get("bullet")
		if(bulletInfo.lifetime > 0) then
		local movement = vec3:new(bulletInfo.speed*dt,0,0)
		entity.Transform:translate(movement)
		bulletInfo.lifetime = bulletInfo.lifetime - 1
		end
	end
	self.collided = {}
end

Manager:addSystem(BulletSystem())

-----------------------------------------------------------
LOG("Systems load completed", LogLevel.Info, 1)


