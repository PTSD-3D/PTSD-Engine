local eng = reqEngine

reqEngine.initialize({globals = true});

local Position = eng.Component.create("position", {"x", "y"}, {x = 0, y = 0})
local Velocity = eng.Component.create("velocity",{"vx","vy"})

local player = eng.Entity()
player:initialize()

player:add(Position(30, 25))
player:add(Velocity(100,100))

print(player:get("position").x)

local MoveSystem = class("MoveSystem",System)

function MoveSystem:requires()
	return {"position","velocity"}
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local position = entity:get("position")
		local velocity = entity:get("velocity")
		position.x = position.x + velocity.vx*dt
		position.y = position.y + velocity.vy*dt
		print(position.x)
	end
end

manager = eng.EntityManager()

manager:addEntity(player)

manager:addSystem(MoveSystem())

print(player:get("position").x)

--manager:update(1)

--print(player:get("position").x)