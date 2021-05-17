local ns = require('namespace')

local SoundSystem = ns.class("SoundSystem",ns.System)

function SoundSystem:requires()
	return {"boombox"}
end

function SoundSystem:onPlay(music)
	if music.channel == -1 then 
		--we play for the first time
		music.channel = playSound(music.sound.id)
	else
		resumeChannel(music.channel)
	end

end

function SoundSystem:onStop(music)
	pauseChannel(music.channel)
end

function SoundSystem:setVolume(music)
	setChannelVolume(music.channel,music.volume)
end

function SoundSystem:update(dt)
	for _, entity in pairs(self.targets) do
		local music = entity:get("boombox")
		if keyJustPressed(PTSDKeys.Q) then
			--it just cant be initialized to false srry
			if music.isPlaying == nil then
				music.isPlaying = false
			end
			if music.isPlaying then
				music.isPlaying = false
				self:onStop(music)
			else
				music.isPlaying = true
				self:onPlay(music)				
			end
		end
		if music.channel == -1 then
			return
		end
		if keyJustPressed(PTSDKeys.R) and music.volume <= 1 then
			music.volume = music.volume + 0.1
			self:setVolume(music)
		elseif keyJustPressed(PTSDKeys.F) and music.volume > 0 then
			music.volume = music.volume - 0.1
			self:setVolume(music)
		end
	end
end

Manager:addSystem(SoundSystem())