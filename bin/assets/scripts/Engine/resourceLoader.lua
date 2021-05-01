local eng = reqEngine
local ns = reqNamespace

function ns.LoadSounds()
	for key, sound in pairs(Resources.Sounds) do
		print(key)
		print(sound)
		local path = Resources.PATHS.Sound .. sound.path
		print(path)
		Status,Error = pcall(PTSDLoadSound, path,sound.tipo, sound.volume or 1)
		if not Status then
			print (Error)
		else
			--local soundId = PTSDLoadSound(PATHS.Sound .. sound.path,sound.tipo, sound.volume or 1)
			print(Error)
			Resources.Sounds[key].id = Error
		end
	end
end