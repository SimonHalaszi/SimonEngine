#include "TopPanel.hpp"

TopPanel::TopPanel() {
	float topPanelButtonWidth = 1.0f / 8.0f;
	float topPanelButtonHeight = 1.0f;

	// In top panel viewport - ONLY store viewport coordinates
	menuButton_ = VoidButton(
		{ { -1.0f + topPanelButtonWidth, 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight } },
		{ 1.0f, 1.0f, 1.0f },
		"Menu",
		[this]() { menuButtonAction(); }
	);

	helpButton_ = VoidButton(
		{ { -1.0f + (topPanelButtonWidth * 3), 0.0f },
		{ topPanelButtonWidth, topPanelButtonHeight } },
		{ 0.8f, 0.8f, 0.8f },
		"Help",
		[this]() { helpButtonAction(); }
	);

	float globalPanelButtonWidth = 1.0f / 8.0f;
	float globalPanelButtonHeight = 1.0f / (ENGINE_WIN_H / TOP_PANEL_H);

	// In global viewport - ONLY store viewport coordinates
	menuDropButtons_.push_back(
		VoidButton(
			{ { -1.0f + globalPanelButtonWidth, 1.0f - (globalPanelButtonHeight * 3) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },
			{ 0.8f, 0.8f, 0.8f },
			"Quit",
			[this]() { quitButtonAction(); }
		)
	);

	helpDropButtons_.push_back(
		VoidButton(
			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 3) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },
			{ 1.0f, 1.0f, 1.0f },
			"Controls",
			[this]() { controlsButtonAction(); }
		)
	);

	helpDropButtons_.push_back(
		VoidButton(
			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 5) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },
			{ 0.8f, 0.8f, 0.8f },
			"About",
			[this]() { aboutButtonsAction(); }
		)
	);

	helpDropButtons_.push_back(
		VoidButton(
			{ { -1.0f + (globalPanelButtonWidth * 3), 1.0f - (globalPanelButtonHeight * 7) },
			{ globalPanelButtonWidth, globalPanelButtonHeight } },
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

void TopPanel::quitButtonAction() {
	std::cout << "TopPanel::quitButtonAction() : Menu quit button has flagged for quitting" << std::endl;
	markedForQuiting_ = true;
}

void TopPanel::controlsButtonAction() {
	std::cout << "---------------------- Controls! ----------------------" << std::endl;
	std::cout << "----- From Anywhere -----" << std::endl;
	std::cout << "F1: Enter Game Mode from Editor" << std::endl;
	std::cout << "F2: Enter Editor Mode from Game, With current Game State" << std::endl;
	std::cout << "F3: Reset Game in Editor Mode" << std::endl;
	std::cout << "F4: Reset Game in Game Mode" << std::endl;
	std::cout << "M: Move to focused GameObject" << std::endl;
	std::cout << "Z: Reset zoom" << std::endl;
	std::cout << "R: Reset position" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "----- While Hovering Over Scene View -----" << std::endl;
	std::cout << "Scroll to zoom" << std::endl;
	std::cout << "Arrow keys to move" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "----- While Hovering Over Hierarchy -----" << std::endl;
	std::cout << "Scroll to, well, scroll" << std::endl;
	std::cout << "Click to focus GameObject" << std::endl;
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
	std::cout << "-------------------------------------------------------" << std::endl;
}