local eng = reqEngine

reqEngine.initialize({globals = true});

eng.Component.create("playerMove", {"x","y","z"})

local MoveSystem = class("MoveSystem",System)

function MoveSystem:requires()
	return {"playerMove"}
end

function MoveSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local dir;
		local vx = entity:get("playerMove").x;
		local vy = entity:get("playerMove").y;
		local vz = entity:get("playerMove").z;

		local tr = entity.Transform;
		if keyPressed(PTSDKeys.A) then
			dir = vec3:new(-vx, 0, 0)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.W) then
			dir = vec3:new(0, 0, -vz)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.S) then
			dir = vec3:new(0, 0, vz)
			tr.translate(dir)
		end
		if keyPressed(PTSDKeys.D) then
			dir = vec3:new(vx, 0, 0)
			tr.translate(dir)
		end
	end
end

manager = eng.EntityManager()

reqNamespace.loadScene(manager, sampleScene)

--manager:addEntity(player)

manager:addSystem(MoveSystem())