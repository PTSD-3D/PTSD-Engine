local namespace = require('namespace')
local engine = {}

local function populateNamespace(ns)
    -- Requiring class
    ns.class = require('middleclass')

    -- Requiring all Events
    ns.ComponentAdded = require('ComponentAdded')
    ns.ComponentRemoved = require('ComponentRemoved')
    ns.Collision = require('Collision')
    ns.ChangeSceneEvent = require('ChangeSceneEvent')

    -- Requiring the engine
    ns.Entity = require('Entity')
    ns.EventManager = require('EventManager')
    ns.EntityManager = require('EntityManager')
    ns.System = require('System')
    ns.Component = require('Component')

  --Requiring constants
  ns.SkyboxTypes = {
    Skybox = 1,
    Skydome = 2
  }
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