local ns = require('namespace')
local resources = require('resources')
function ns.LoadSounds()
	LOG("PRELOADING SOUNDS")
	for key, sound in pairs(resources.Sounds) do
		local path = resources.PATHS.Sound .. sound.path
		--pcall(loadSound,arg1,arg2) is equivalent to loadSound(arg1,arg2)
		--We will use pcall because this may explode in the future
		Status,Error = pcall(PTSDLoadSound, path, sound.tipo, sound.soundChannel or 0, sound.volume or 1)
		if not Status then
			print (Error)
		else
			--local soundId = PTSDLoadSound(PATHS.Sound .. sound.path,sound.tipo, sound.volume or 1)
			resources.Sounds[key].id = Error
		end
	end
end