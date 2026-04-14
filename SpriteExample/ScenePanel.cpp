#include "ScenePanel.hpp"

ScenePanel::ScenePanel() {
	scenePanelTitle_.pos = { 0.0f, 1.0f - (1.0f / 4.0f) };
	scenePanelTitle_.scale = { 1.0f, 1.0f / 4.0f };

	scenePanelContext_.viewportX = OBJECTS_PANEL_W;
	scenePanelContext_.viewportY = 0;
	scenePanelContext_.viewportWidth = SCENE_PANEL_W;
	scenePanelContext_.viewportHeight = SCENE_PANEL_H;
	scenePanelContext_.scrollOffsetX = 0.0f;
	scenePanelContext_.scrollOffsetY = 0.0f;
	scenePanelContext_.orthoLeft = -1.0f;
	scenePanelContext_.orthoRight = 1.0f;
	scenePanelContext_.orthoBottom = -1.0f;
	scenePanelContext_.orthoTop = 1.0f;

	float areaOffset = ((1.0f / 4.0f) * 2);
	ViewportArea startArea = scenePanelTitle_;
	startArea.pos.y -= areaOffset;
	int i = 0;

	ColorRGB color1 = { 1.0f, 1.0f, 1.0f };
	ColorRGB color2 = { 0.8f, 0.8f, 0.8f };
	ColorRGB colors[2] = { color1, color2 };

	// Add scenes as needed

	sceneButtons_.push_back(
		std::make_unique<GameOverScreenSceneButton>(
			startArea,
			colors[i % 2],
			"GameOverScreen"
		)
	);
	startArea.pos.y -= areaOffset;
	++i;
	sceneButtons_.push_back(
		std::make_unique<GameWonScreenSceneButton>(
			startArea,
			colors[i % 2],
			"GameWonScreen"
		)
	);
	startArea.pos.y -= areaOffset;
	++i;
	sceneButtons_.push_back(
		std::make_unique<PlatformerSceneButton>(
			startArea,
			colors[i % 2],
			"PlatformerScene"
		)
	);
	startArea.pos.y -= areaOffset;
	++i;
	sceneButtons_.push_back(
		std::make_unique<TitleScreenSceneButton>(
			startArea,
			colors[i % 2],
			"TitleScreen"
		)
	);
}

void ScenePanel::draw() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(
		scenePanelContext_.orthoLeft,
		scenePanelContext_.orthoRight,
		scenePanelContext_.orthoBottom,
		scenePanelContext_.orthoTop,
		-1.0,
		1.0
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(
		scenePanelContext_.viewportX,
		scenePanelContext_.viewportY,
		scenePanelContext_.viewportWidth,
		scenePanelContext_.viewportHeight
	);

	// Draw Background
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

	glPushMatrix();
	glTranslatef(0, -scenePanelContext_.scrollOffsetY, 0);

	// Draw Asset Panel Buttons
	for (const auto& button : sceneButtons_) {
		button->draw();
	}

	glPopMatrix();

	// Draw Title
	drawRectangle(
		scenePanelTitle_.pos,
		scenePanelTitle_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ scenePanelTitle_.pos.x - scenePanelTitle_.scale.x, scenePanelTitle_.pos.y },
		"Scenes",
		0.0f,
		{ 1.0f, 1.0f, 1.0f }
	);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void ScenePanel::update() {
	// Dont bother doing input if we arent in hierarchy panel
	if (isInsideViewportContext(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), scenePanelContext_)) {
		float scrollSpeed = 0.1f;

		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
			scenePanelContext_.scrollOffsetY -= scrollSpeed;
		}
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
			scenePanelContext_.scrollOffsetY += scrollSpeed;
		}

		if (scenePanelContext_.scrollOffsetY > 0.0f) {
			scenePanelContext_.scrollOffsetY = 0.0f;
		}

		// Handle Clicking
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
			for (auto& button : sceneButtons_) {
				button->handleClick(scenePanelContext_);
			}
		}
	}
}