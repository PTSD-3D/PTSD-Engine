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

function ns.LoadUIElements()
	LOG("PRELOADING UI FILES")

	if not resources.UISchemes then
		LOG("Not UISchemes defined in resources. [resourceLoader.lua 23] ",LogLevel.Warning, 1 )
		return false
	end

	--We must garantize the schemes to load first
	for key, UIScheme in pairs(resources.UISchemes) do
		local path = UIScheme.path
		local correct = ns.call(tostring("Error loading resource ["..key .. "] in " .. path .. "\n"), PTSDLoadUIFile, path, UIScheme.type)
		if correct == false then return false end;
	end

	for key, UILayout in pairs(resources.UILayouts) do
		local path = UILayout.path
		local correct = ns.call(tostring("Error loading layout ["..key .. "] in " .. path .. "\n"), PTSDLoadUIFile, path, UILayout.type)
		if correct == false then return false end;
	end
	return true
end