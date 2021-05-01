local eng = reqEngine
local ns = reqNamespace

function LoadSounds()
	for _, sound in pairs(Resources.Sounds) do
		sound.id = PTSDLoadSound(PATHS.Sound+sound.path,sound.tipo, sound.volume or 1)
	end
end