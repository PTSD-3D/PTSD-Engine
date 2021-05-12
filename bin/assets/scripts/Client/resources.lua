local SoundType = {
	Sonido = 0,
	Musica = 1
}

local SoundChannel = {
	Ambiente = 0,
	Dialogo = 1,
	General = 2
}

local Resources = {
	PATHS = {
		Sound = "./assets/sounds/"
	},
	Sounds = {
		Oof = {
			path = "oof.mp3", id, tipo=SoundType.Sonido, soundChannel=SoundChannel.Dialogo, volume = 0.5
		},
		PTSD_Anthem = {
			path = "PTSD-Anthem.mp3", id, tipo = SoundType.Musica, volume = 0.3
		},		
		Clowning = {
			path = "clowning-around.mp3", id, tipo=SoundType.Musica, volume = 0.3
		}
	},
	UISchemes = {
		TaharezLookScheme = {
			path = "TaharezLook.scheme", type=UIFileType.Scheme
		}
	},
	UIFiles = {
		DejaVuSans = {
			path = "DejaVuSans-12.font", type=UIFileType.Font
		},		
		TaiFighterLayout = {
			path = "TaiFighter.layout", type=UIFileType.Layout
		},
		PauseLayout = {
			path = "Pause.layout", type=UIFileType.Layout
		}
	},
	Meshes = {
		--si
	}
}
return Resources