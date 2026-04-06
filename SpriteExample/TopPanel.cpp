#include "TopPanel.hpp"

TopPanel::TopPanel() {
	float buttonWindowWidth = TOP_PANEL_W / 8.0f;
	float buttonWindowHeight = TOP_PANEL_H;

	float topPanelButtonWidth = 1.0f / 8.0f;
	float topPanelButtonHeight = 1.0f;

	// In top panel viewport
	menuButton_ = VoidButton(
		{ { 0.0f, 0.0f },
		{ buttonWindowWidth, buttonWindowHeight } },

		{ { -1.0f + topPanelButtonWidth, 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight } },

		{1.0f, 1.0f, 1.0f},

		"Menu",
		[this]() { menuButtonAction(); }
	);
	helpButton_ = VoidButton(
		{ { 0.0f + buttonWindowWidth, 0.0f },
		{ buttonWindowWidth, buttonWindowHeight } },

		{ { -1.0f + (topPanelButtonWidth * 3), 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight } },

		{ 0.8f, 0.8f, 0.8f },

		"Help",
		[this]() { helpButtonAction(); }
	);

	float globalPanelButtonWidth = 1.0f / 8.0f;
	float globalPanelButtonHeight = 1.0f / (ENGINE_WIN_H / TOP_PANEL_H);

	// In global viewport
	menuDropButtons_.push_back(
		VoidButton(
			{ { 0.0f, buttonWindowHeight },
			{ buttonWindowWidth, buttonWindowHeight } },

			{ { -1.0f + globalPanelButtonWidth, 1.0f - (globalPanelButtonHeight * 3) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },

			{ 0.8f, 0.8f, 0.8f },

			"Quit",
			[this]() { quitButtonAction(); }
		)
	);
	helpDropButtons_.push_back(
		VoidButton(
			{ { buttonWindowWidth, buttonWindowHeight },
			{ buttonWindowWidth, buttonWindowHeight } },

			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 3) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },

			{ 1.0f, 1.0f, 1.0f },

			"Controls",
			[this]() { controlsButtonAction(); }
		)
	);
	helpDropButtons_.push_back(
		VoidButton(
			{ { buttonWindowWidth, (buttonWindowHeight * 2) },
			{ buttonWindowWidth, buttonWindowHeight } },

			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 5) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },

			{ 0.8f, 0.8f, 0.8f },

			"About",
			[this]() { aboutButtonsAction(); }
		)
	);
	helpDropButtons_.push_back(
		VoidButton(
			{ { buttonWindowWidth, (buttonWindowHeight * 3) },
			{ buttonWindowWidth, buttonWindowHeight } },

			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 7) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },

			{ 1.0f, 1.0f, 1.0f },

			"Support",
			[this]() { supportButtonAction(); }
		)
	);
}

void TopPanel::draw() const {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glViewport(0, OBJECTS_PANEL_H + HIERARCHY_PANEL_H, TOP_PANEL_W, TOP_PANEL_H);

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

	menuButton_.draw();
	helpButton_.draw();

	// Drop in global viewport
	if (menuDropActive_ || helpDropActive_) {
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		glViewport(0, 0, ENGINE_WIN_W, ENGINE_WIN_H);

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
	}

	glPopMatrix();
}

void TopPanel::update() {
	menuButton_.handleClick();
	helpButton_.handleClick();
	if (menuDropActive_) {
		for (auto& button : menuDropButtons_) {
			button.handleClick();
		}
	}
	if (helpDropActive_) {
		for (auto& button : helpDropButtons_) {
			button.handleClick();
		}
	}
}

void TopPanel::menuButtonAction() { menuDropActive_ = !menuDropActive_;  }

void TopPanel::helpButtonAction() { helpDropActive_ = !helpDropActive_; }

// This must travel up to editor so that Game can read this and safely quit
void TopPanel::quitButtonAction() { 
	std::cout << "TopPanel::quitButtonAction() : Menu quit button has flagged for quitting" << std::endl;
	markedForQuiting_ = true; 
}

void TopPanel::controlsButtonAction() { 
	std::cout << "----- Controls! -----" << std::endl;
	std::cout << "F1: Enter Game Mode from Editor" << std::endl;
	std::cout << "F2: Enter Editor Mode from Game, With current Game State" << std::endl;
	std::cout << "F3: Reset Game in Editor Mode" << std::endl;
	std::cout << "F4: Reset Game in Game Mode" << std::endl;
	std::cout << "Point and Clicking Elsewhere" << std::endl;
	std::cout << "---------------------" << std::endl;
}

void TopPanel::aboutButtonsAction() { 
	std::cout << "----- This is SimonEngine! -----" << std::endl;
	std::cout << "You are currently in Editor Mode! Where you can change the state of the Game" << std::endl;
	std::cout << "Press the 'Controls' button for help with controls!" << std::endl;
	std::cout << "--------------------------------" << std::endl;
}

void TopPanel::supportButtonAction() {
	std::cout << "----- So You Hate the Product? -----" << std::endl;
	std::cout << "Email Me! shalaszi@kent.edu" << std::endl;
	std::cout << "------------------------------------" << std::endl;
}