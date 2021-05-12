function ShowTaiFighterUI()
	setWindowVisible("TaiFighterWindow", true)
	setWindowVisible("PauseWindow", false)
	setWindowVisible("PushButton", false)
	setWindowVisible("ExitButton", false)
	setUIMouseCursorVisible(false);
end

function ShowPauseUI()
	setWindowVisible("TaiFighterWindow", false)
	setWindowVisible("PauseWindow", true)
	setWindowVisible("PushButton", true)
	setWindowVisible("ExitButton", true)
	setUIMouseCursorVisible(true);
end

function ExitCallback()
	LOG("EXIT place holder")
end