#include "DeadHandler.hpp"

void DeadHandler::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (InputManager::getInstance().isPressed('q')) {
		Game::getInstance().changeScene(SceneFactory::getInstance().createScene("MainMenuScene"));
	}
	if (InputManager::getInstance().isPressed('r')) {
		Game::getInstance().changeScene(SceneFactory::getInstance().createScene("GameScene"));
	}
}