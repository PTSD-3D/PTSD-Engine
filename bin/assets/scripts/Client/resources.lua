local prefabs = reqPrefab
local sceneConfig = reqSceneConfigurations
local SoundType = {
	Sonido = 0,
	Musica = 1
}
local SoundChannel = {
	Ambiente = 0,
	Dialogo = 1
}

Resources = {
	Sounds = {
		_PATH = "./assets/sounds/",
		Oof = {
			Path = "oof.mp3", id, tipo=SoundType.Sonido
		},
		PTSD_Anthem = {
			Path = "PTSD-Anthem.mp3"
		},
		Clowning = {
			Path = "clowning-around.mp3", id, tipo=SoundType.Musica
		}
	},
	Meshes = {

	}
}
return Resources