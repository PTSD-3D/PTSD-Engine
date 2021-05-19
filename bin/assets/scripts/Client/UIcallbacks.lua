function showTaiFighterUI()
	setWindowVisible("TaiFighterWindow", true)
	setWindowVisible("PauseWindow", false)
	
	setWindowVisible("PushButton", false)
	setWindowVisible("ExitButton", false)

	changeText("Title","Payum")

	setUIMouseCursorVisible(false);
end

function showPauseUI()
	setWindowVisible("TaiFighterWindow", false)
	setWindowVisible("PauseWindow", true)

	setWindowVisible("PushButton", true)
	setWindowVisible("ExitButton", true)

	changeText("Title","TaiFighter")

	setUIMouseCursorVisible(true);
end

function exitCallback()
	LOG("EXIT place holder")
end