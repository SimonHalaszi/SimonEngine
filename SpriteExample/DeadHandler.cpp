#include "DeadHandler.hpp"

#include "GameScene.hpp"
#include "MainMenuScene.hpp"

void DeadHandler::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (InputManager::getInstance().isPressed('q')) {
		Game::getInstance().changeScene(std::make_unique<MainMenuScene>());
	}
	if (InputManager::getInstance().isPressed('r')) {
		Game::getInstance().changeScene(std::make_unique<GameScene>());
	}
}