#include "SceneButton.hpp"
#include "Game.hpp"

SceneButton::SceneButton() {
	viewportArea_ = { 0.0f, 0.0f, 0.0f, 0.0f };
	color_ = { 0.0f, 0.0f, 0.0f },
	text_ = "";
}

SceneButton::SceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) :
	viewportArea_(viewportArea),
	color_(color),
	text_(text)
{}

bool SceneButton::isInside(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(viewportArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

void SceneButton::draw() const {
	drawRectangle(
		viewportArea_.pos,
		viewportArea_.scale,
		0.0f,
		false,
		false,
		color_,
		color_,
		color_,
		color_
	);
	drawText(
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y },
		text_,
		0.0f,
		{ 0.0f, 0.0f, 0.0f }
	);
}

GameOverScreenSceneButton::GameOverScreenSceneButton() : SceneButton() {}

GameOverScreenSceneButton::GameOverScreenSceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) : SceneButton(viewportArea, color, text) {}

#include "GameOverScreenScene.hpp"
void GameOverScreenSceneButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			Game::getInstance().changeScene(std::make_unique<GameOverScreenScene>());
		}
	}
}

GameWonScreenSceneButton::GameWonScreenSceneButton() : SceneButton() {}

GameWonScreenSceneButton::GameWonScreenSceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) : SceneButton(viewportArea, color, text) {
}

#include "GameWonScreenScene.hpp"
void GameWonScreenSceneButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			Game::getInstance().changeScene(std::make_unique<GameWonScreenScene>());
		}
	}
}

PlatformerSceneButton::PlatformerSceneButton() : SceneButton() {}

PlatformerSceneButton::PlatformerSceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) : SceneButton(viewportArea, color, text) {
}

#include "PlatformerScene.hpp"
void PlatformerSceneButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			Game::getInstance().changeScene(std::make_unique<PlatformerScene>());
		}
	}
}

TitleScreenSceneButton::TitleScreenSceneButton() : SceneButton() {}

TitleScreenSceneButton::TitleScreenSceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) : SceneButton(viewportArea, color, text) {
}

#include "TitleScreenScene.hpp"
void TitleScreenSceneButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			Game::getInstance().changeScene(std::make_unique<TitleScreenScene>());
		}
	}
}