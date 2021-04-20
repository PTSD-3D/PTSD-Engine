local eng = reqEngine

reqEngine.initialize({globals = true});

eng.Component.create("position", {"x", "y"}, {x = 0, y = 0})
eng.Component.create("velocity",{"vx","vy"})


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
		-- print(position.x)
		local tr = entity.Transform;
		local dir;
		if keyPressed(PTSDKeys.A) then
			dir = vec3:new(-1, 0, 0)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.W) then
			dir = vec3:new(0, 0, -1)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.S) then
			dir = vec3:new(0, 0, 1)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.D) then
			dir = vec3:new(1, 0, 0)
			tr.translate(dir)
		end
	end
end

manager = eng.EntityManager()

reqNamespace.loadScene(manager, sampleScene)

--manager:addEntity(player)

manager:addSystem(MoveSystem())