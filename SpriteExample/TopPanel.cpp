#include "TopPanel.hpp"

TopPanel::TopPanel(
	std::function<void()> saveCallback,
	std::function<void()> loadCallback
) : saveCallback_(std::move(saveCallback)), loadCallback_(std::move(loadCallback)) {
	float topPanelButtonWidth = 1.0f / 8.0f;
	float topPanelButtonHeight = 1.0f;

	ViewportArea menuButtonArea = {
		{ -1.0f + (topPanelButtonWidth), 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight }
	};

	ViewportArea helpButtonArea = {
		{ -1.0f + (topPanelButtonWidth * 3), 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight }
	};

	menuButton_ = VoidButton(
		menuButtonArea,
		{ 1.0f, 1.0f, 1.0f },
		"Menu",
		[this]() { menuButtonAction(); }
	);
	helpButton_ = VoidButton(
		helpButtonArea,
		{ 0.8f, 0.8f, 0.8f },
		"Help",
		[this]() { helpButtonAction(); }
	);

	float globalPanelButtonWidth = 1.0f / 8.0f;
	float globalPanelButtonHeight = 1.0f / float(ENGINE_WIN_H / TOP_PANEL_H);
	float centerDifferenceHeight = globalPanelButtonHeight * 2.0f;
	float centerDifferenceWidth = globalPanelButtonWidth * 2.0f;

	ViewportArea menuDropButtonArea = {
		{ -1.0f + globalPanelButtonWidth, 1.0f - (globalPanelButtonHeight + centerDifferenceHeight) },
		{ globalPanelButtonWidth, globalPanelButtonHeight }
	};

	menuDropButtons_.push_back(
		VoidButton(
			menuDropButtonArea,
			{ 0.6f, 0.9f, 0.6f },
			"Save",
			[this]() { saveButtonAction(); }
		)
	);

	menuDropButtonArea.pos.y -= centerDifferenceHeight;

	menuDropButtons_.push_back(
		VoidButton(
			menuDropButtonArea,
			{ 0.6f, 0.6f, 0.9f },
			"Load",
			[this]() { loadButtonAction(); }
		)
	);

	menuDropButtonArea.pos.y -= centerDifferenceHeight;

	menuDropButtons_.push_back(
		VoidButton(
			menuDropButtonArea,
			{ 0.9f, 0.6f, 0.6f },
			"Quit",
			[this]() { quitButtonAction(); }
		)
	);

	ViewportArea helpDropButtonArea = {
		{ -1.0f + (globalPanelButtonWidth + centerDifferenceWidth), 1.0f - (globalPanelButtonHeight + centerDifferenceHeight) },
		{ globalPanelButtonWidth, globalPanelButtonHeight }
	};

	helpDropButtons_.push_back(
		VoidButton(
			helpDropButtonArea,
			{ 1.0f, 1.0f, 1.0f },
			"Controls",
			[this]() { controlsButtonAction(); }
		)
	);

	helpDropButtonArea.pos.y -= centerDifferenceHeight;

	helpDropButtons_.push_back(
		VoidButton(
			helpDropButtonArea,
			{ 0.8f, 0.8f, 0.8f },
			"About",
			[this]() { aboutButtonsAction(); }
		)
	);

	helpDropButtonArea.pos.y -= centerDifferenceHeight;

	helpDropButtons_.push_back(
		VoidButton(
			helpDropButtonArea,
			{ 1.0f, 1.0f, 1.0f },
			"Support",
			[this]() { supportButtonAction(); }
		)
	);

	topPanelContext_.viewportX = 0;
	topPanelContext_.viewportY = OBJECTS_PANEL_H + HIERARCHY_PANEL_H;
	topPanelContext_.viewportWidth = TOP_PANEL_W;
	topPanelContext_.viewportHeight = TOP_PANEL_H;
	topPanelContext_.orthoLeft = -1.0f;
	topPanelContext_.orthoRight = 1.0f;
	topPanelContext_.orthoBottom = -1.0f;
	topPanelContext_.orthoTop = 1.0f;

	globalContext_.viewportX = 0;
	globalContext_.viewportY = 0;
	globalContext_.viewportWidth = ENGINE_WIN_W;
	globalContext_.viewportHeight = ENGINE_WIN_H;
	globalContext_.orthoLeft = -1.0f;
	globalContext_.orthoRight = 1.0f;
	globalContext_.orthoBottom = -1.0f;
	globalContext_.orthoTop = 1.0f;
}

void TopPanel::draw() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(
		topPanelContext_.orthoLeft,
		topPanelContext_.orthoRight,
		topPanelContext_.orthoBottom,
		topPanelContext_.orthoTop,
		-1.0,
		1.0
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(
		topPanelContext_.viewportX, 
		topPanelContext_.viewportY, 
		topPanelContext_.viewportWidth, 
		topPanelContext_.viewportHeight
	);

	// Background
	drawRectangle(
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		0.0f,
		false,
		false,
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f }
	);

	// Buttons in top panel view
	menuButton_.draw();
	helpButton_.draw();

	if (menuDropActive_ || helpDropActive_) {
		// Drop down buttons in global view
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(
			globalContext_.orthoLeft,
			globalContext_.orthoRight,
			globalContext_.orthoBottom,
			globalContext_.orthoTop,
			-1.0,
			1.0
		);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glViewport(
			globalContext_.viewportX,
			globalContext_.viewportY,
			globalContext_.viewportWidth,
			globalContext_.viewportHeight
		);

		if (menuDropActive_) {
			for (auto& button : menuDropButtons_) {
				button.draw();
			}
		}
		if (helpDropActive_) {
			for (auto& button : helpDropButtons_) {
				button.draw();
			}
		}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void TopPanel::update() {
	menuButton_.handleClick(topPanelContext_);
	helpButton_.handleClick(topPanelContext_);

	if (menuDropActive_ || helpDropActive_) {
		if (menuDropActive_) {
			for (auto& button : menuDropButtons_) {
				button.handleClick(globalContext_);
			}
		}
		if (helpDropActive_) {
			for (auto& button : helpDropButtons_) {
				button.handleClick(globalContext_);
			}
		}
	}
}

void TopPanel::menuButtonAction() { menuDropActive_ = !menuDropActive_; }

void TopPanel::helpButtonAction() { helpDropActive_ = !helpDropActive_; }

void TopPanel::saveButtonAction() {
	menuDropActive_ = false;
	if (saveCallback_) {
		saveCallback_();
	}
}

void TopPanel::loadButtonAction() {
	menuDropActive_ = false;
	if (loadCallback_) {
		loadCallback_();
	}
}

void TopPanel::quitButtonAction() {
	std::cout << "TopPanel::quitButtonAction() : Menu quit button has flagged for quitting" << std::endl;
	markedForQuiting_ = true;
}

void TopPanel::controlsButtonAction() {
	std::cout << "---------------------- Controls! ----------------------" << std::endl;
	std::cout << "----- From Anywhere -----" << std::endl;
	std::cout << "F1: Enter Scene mode from Editor" << std::endl;
	std::cout << "F2: Enter Editor mode from Scene, with current Scene state" << std::endl;
	std::cout << "F3: Reset Scene in Editor mode" << std::endl;
	std::cout << "F4: Reset Scene in Scene mode" << std::endl;
	std::cout << "F5: To delete focused GameObject" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "----- In Top Panel -----" << std::endl;
	std::cout << "Menu -> Save: Save changes made in editor mode (Can not be done after entering play mode)" << std::endl;
	std::cout << "Menu -> Load: Loads in the saved editor changes for this scene" << std::endl;
	std::cout << "Menu -> Quit: Safely quits the program" << std::endl;
	std::cout << "Help -> Controls: I wonder..." << std::endl;
	std::cout << "Help -> About: What im all about" << std::endl;
	std::cout << "Help -> Support: Support hotline" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "----- While Hovering Over Scene View -----" << std::endl;
	std::cout << "Scroll to zoom" << std::endl;
	std::cout << "Arrow keys to move" << std::endl;
	std::cout << "M: Move to focused GameObject" << std::endl;
	std::cout << "Z: Reset zoom" << std::endl;
	std::cout << "R: Reset position" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "----- While Hovering Over Hierarchy -----" << std::endl;
	std::cout << "Scroll to, well, scroll" << std::endl;
	std::cout << "Click on GameObject name to focus" << std::endl;
	std::cout << "Click on GameObject name again to focus its Hierarchy" << std::endl;
	std::cout << "Click off into space to unfocus" << std::endl;
	std::cout << "Arrow keys move focused GameObject up and down Hierarchy" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "----- While Hovering Over Assets -----" << std::endl;
	std::cout << "Scroll to, well, scroll" << std::endl;
	std::cout << "Click to make asset" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "----- While Hovering Over Scenes -----" << std::endl;
	std::cout << "Scroll to, well, scroll" << std::endl;
	std::cout << "Click to focus change scene" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "----- While Hovering Over Inspector -----" << std::endl;
	std::cout << "Scroll to, well, scroll" << std::endl;
	std::cout << "Click on text entry to start typing in it" << std::endl;
	std::cout << "Click off text entry to stop typing in it" << std::endl;
	std::cout << "Click on set to set field" << std::endl;
	std::cout << "Click on toggle to toggle bool fields" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
}

void TopPanel::aboutButtonsAction() {
	std::cout << "----------------- This is SimonEngine! ----------------" << std::endl;
	std::cout << "You are currently in Editor Mode! Where you can change the state of the Game" << std::endl;
	std::cout << "Press the 'Controls' button for help with controls!" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
}

void TopPanel::supportButtonAction() {
	std::cout << "-------------- So You Hate the Product? ---------------" << std::endl;
	std::cout << "Email Me! shalaszi@kent.edu" << std::endl;
	std::cout << "Or keep all your mean words to yourself" << std::endl;
	std::cout << std::endl;
	std::cout << "'Don't ask me questions (questions)'" << std::endl;
	std::cout << "That you don't want (want)" << std::endl;
	std::cout << "The answers to (to)' - Julian Casablancas" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
}