local eng = reqEngine
local ns = reqNamespace

eng.initialize({globals = false});

eng.Component.create("playerMove", {"x","y","z"})

local MoveSystem = ns.class("MoveSystem",ns.System)

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
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.W) then
			dir = vec3:new(0, 0, -vz)
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.S) then
			dir = vec3:new(0, 0, vz)
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.D) then
			dir = vec3:new(vx, 0, 0)
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.Shift) then
			local material = entity.Mesh:getMaterial()
			if material == "KirbyMat" then
				material = "Red"
			else
				material="KirbyMat"
			end
			entity.Mesh:setMaterial(material);
		end
	end
end

Manager = eng.EntityManager()

ns.loadScene(Manager, sampleScene)

Manager:addSystem(MoveSystem())

LOG("Test.lua completed")