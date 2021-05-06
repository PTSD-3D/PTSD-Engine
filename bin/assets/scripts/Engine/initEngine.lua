local namespace = reqNamespace
local engine = {}


local function populateNamespace(ns)
    -- Requiring class
    ns.class = reqMiddleclass

    -- Requiring all Events
    ns.ComponentAdded = reqComponentAddedEvent
    ns.ComponentRemoved = reqComponentRemovedEvent
    ns.Collision = reqCollisionEvent

    -- Requiring the engine
    ns.Entity = reqEntity
    ns.EventManager = reqEventManager
    ns.EntityManager = reqEntityManager
    ns.System = reqSystem
    ns.Component = reqComponent
end

function engine.initialize(opts)
    LOG("Initializing engine...", LogLevel.Info, 0)
    if opts == nil then opts = {} end
    if not engine.initialized then
        engine.config = {
            globals = false
        }

        for name, val in pairs(opts) do
            engine.config[name] = val
        end

        populateNamespace(namespace)

        if engine.config.globals then
            populateNamespace(_G)
        end
        engine.initialized = true
        LOG("Engine initialized correctly")
    else
        LOG("Engine is already initialized", LogLevel.Warning, 0)
    end
end

return engine