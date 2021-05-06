local namespace = reqNamespace
local CollisionEv = namespace.class("CollisionEv")

function CollisionEv:initialize(entityAID, entityBID, manifold)
	self.entityAID = entityAID
	self.entityBID = entityBID
	self.manifold = {
		pointA = vec3:new(manifold.pointA),
		pointB = vec3:new(manifold.pointB)
	}
end

function CollisionEv:print()

	local vecA = tostring(self.manifold.pointA)
	local vecB = tostring(self.manifold.pointA)
	print("Entity ID A: " .. self.entityAID .. " Entity ID B: " .. self.entityBID .. " Manifold:{ PointA: " .. vecA .. " PointB: " .. vecB .. "}")
end

return CollisionEv