local prefabs = reqPrefab
local sceneConfig = reqSceneConfigurations
local Scene = {
	SceneConfig = {
		PhysicsConfig={
			Gravity = 5
		}
	},
	Entities = {
		Enemy = prefabs.Enemy{
			Transform = {
				position = { x = -35.1012802124, y = -7.9060144424, z = 11.6276283264 },
				rotation = { x = 221.1516898526, y = -152.1657547071, z = 195.3355828656 },
				scale = { x = 2.098890543, y = 2.098890543, z = 2.0988907814 }
			}
		},
		Enemy_001 = prefabs.Enemy{
			Transform = {
				position = { x = 3.6457614899, y = 5.4532294273, z = -2.2724339962 },
				rotation = { x = -73.3971581794, y = 1.9531190601, z = -45.040504274 },
				scale = { x = 0.3224791288, y = 0.3224791884, z = 0.3224791288 }
			}
		},
		Enemy_002 = prefabs.Enemy{
			Transform = {
				position = { x = 0, y = 0, z = 0 },
				rotation = { x = -69.7976211661, y = 3.2747051693, z = -42.9677057855 },
				scale = { x = 1.8980841637, y = 1.8980841637, z = 1.8980841637 }
			}
		},
		Enemy_003 = prefabs.Enemy{
			Transform = {
				position = { x = -14.5135574341, y = 8.8633947372, z = -7.8755083084 },
				rotation = { x = -61.1043681264, y = 5.8524428946, z = -37.7620019775 },
				scale = { x = 1.0855004787, y = 1.0855004787, z = 1.085500598 }
			}
		},
		Enemy_004 = prefabs.Enemy{
			Transform = {
				position = { x = 13.214509964, y = 15.6598205566, z = 16.3075809479 },
				rotation = { x = -32.491903146, y = -25.2611848528, z = -52.2247567902 },
				scale = { x = 2.7305061817, y = 2.7305061817, z = 2.7305061817 }
			}
		}
	},
	SceneConfig = sceneConfig.sampleScene{}
}
return Scene