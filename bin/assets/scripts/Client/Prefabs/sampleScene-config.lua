local sceneConfig = reqPrefab
local ns = reqNamespace
--TODO require
function sceneConfig.sampleScene()
	return {
		PhysicsConfig = {
			Gravity = 0
		},
		GraphicsConfig = {
			LockMouse = false,
			Skybox = {
				type = 1, --ns.SkyboxTypes.Skybox
				enable = true,
				material = "KirbyMat",
				distance = 300
			}
		}
	}
end