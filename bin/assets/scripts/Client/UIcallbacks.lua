function ShowTaiFighterUI()
	setWindowVisible("TaiFighterWindow", true)
	setWindowVisible("PauseWindow", false)
	
	setWindowVisible("PushButton", false)
	setWindowVisible("ExitButton", false)

	changeText("Title","Payum")

	setUIMouseCursorVisible(false);
end

function ShowPauseUI()
	setWindowVisible("TaiFighterWindow", false)
	setWindowVisible("PauseWindow", true)

	setWindowVisible("PushButton", true)
	setWindowVisible("ExitButton", true)

	changeText("Title","TaiFighter")

	setUIMouseCursorVisible(true);
end

function ExitCallback()
	LOG("EXIT place holder")
end