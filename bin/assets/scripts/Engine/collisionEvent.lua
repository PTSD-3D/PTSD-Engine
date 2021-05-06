local namespace = reqNamespace

function p(a,b)
	print(namespace.Pepito)
	 namespace.Pepito:fireEvent(namespace.Collision(a,b,nil))
end