local namespace = require('namespace')
local CollisionEv = namespace.class("CollisionEv")

function CollisionEv:initialize(entityAID, entityBID, manifold)
	local function f(self, extra)
		local vecA = tostring(self.pointA)
		local vecB = tostring(self.pointB)
		print(string.format("%s{ %s , %s }",extra or "", vecA, vecB))
	end
	self.entityAID = entityAID
	self.entityBID = entityBID
	self.manifold = {
		pointA = vec3:new(manifold.pointA),
		pointB = vec3:new(manifold.pointB),
		print = f
	}
end

function CollisionEv:print()
	local vecA = tostring(self.manifold.pointA)
	local vecB = tostring(self.manifold.pointB)
	print("Entity ID A: " .. self.entityAID .. " Entity ID B: " .. self.entityBID .. " Manifold:{ PointA: " .. vecA .. " PointB: " .. vecB .. "}")
end

return CollisionEv