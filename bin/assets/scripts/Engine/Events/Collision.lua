local namespace = reqNamespace
local CollisionEv = namespace.class("CollisionEv")

function CollisionEv:initialize(entityAID, entityBID, manifold)
	self.entityAID = entityAID
	self.entityBID = entityBID
	self.manifold = manifold
	LOG("Firing CollisionEv ")
end

return CollisionEv