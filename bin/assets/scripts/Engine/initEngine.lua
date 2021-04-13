local engine = reqNamespace

local function populateNamespace(ns)
    -- Requiring class
    ns.class = reqMiddleclass

    -- Requiring all Events
    --ns.ComponentAdded = require(folderOfThisFile .. "src.events.ComponentAdded")
    --ns.ComponentRemoved = require(folderOfThisFile .. "src.events.ComponentRemoved")

    -- Requiring the engine
    ns.Entity = reqEntity
    ns.EntityManager = reqEntityManager
    ns.System = reqSystem
    --ns.EventManager = require(folderOfThisFile .. "src.EventManager")
    ns.Component = reqComponent
end

function engine.initialize(opts)
    if opts == nil then opts = {} end
    if not engine.initialized then
        engine.config = {
            globals = false
        }

        for name, val in pairs(opts) do
            engine.config[name] = val
        end

        populateNamespace(engine)

        if engine.config.globals then
            populateNamespace(_G)
        end
        engine.initialized = true
    else
        print('Engine is already initialized.')
    end
end

return engine