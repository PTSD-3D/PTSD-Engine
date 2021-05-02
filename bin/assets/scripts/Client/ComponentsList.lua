local ns = reqNamespace

--Define new components here
--ns.Component.create("compName",{"attrib1","attrib2"},{attrib1=defaultValue,attrib2=defaultValue})

LOG("Loading components...", LogLevel.Info, 1)

ns.Component.create("playerMove",{"x","y","z"})
ns.Component.create("topo")
ns.Component.create("bulletDamage",{"damage"},{damage=0})

LOG("Components load completed", LogLevel.Info, 1)