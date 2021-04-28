local eng = reqEngine

reqEngine.initialize({globals = true});

eng.Component.create("playerMove", {"x","y","z","r","jump"})

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
		local vr = entity:get("playerMove").r;

		local mouseDirection = getMouseRelativePosition()
		rot = vec3:new(0, -mouseDirection.x, 0) * vr
		local tr = entity.Transform

		tr:rotate(rot);
		if keyPressed(PTSDKeys.A) then
			dir = tr:getRight()*vx*dt
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.W) then
			dir = tr:getForward()*vz*dt
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.S) then
			dir = tr:getForward()*-vz*dt
			tr:translate(dir)
		end
		if keyPressed(PTSDKeys.D) then
			dir = tr:getRight()*-vx*dt
			tr:translate(dir)
		end
		--local rb = entity.Rigidbody
		--if rb.isgrounded()		Needs to check if the rb is on the ground, we can use a downwards raycast or the collision normals to see if it's the ground
		if keyPressed(PTSDKeys.Space) then
			--rb.addForce(0, jump, 0);
		end
	end
end

manager = eng.EntityManager()

reqNamespace.loadScene(manager, sampleScene)

--manager:addEntity(player)

manager:addSystem(MoveSystem())