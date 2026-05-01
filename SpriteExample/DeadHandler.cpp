#include "DeadHandler.hpp"

#include "LoadingGameScene.hpp"
#include "LoadingMainMenuScene.hpp"

void DeadHandler::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (InputManager::getInstance().isPressed('q')) {
		Game::getInstance().changeScene(std::make_unique<LoadingMainMenuScene>());
	}
	if (InputManager::getInstance().isPressed('r')) {
		Game::getInstance().changeScene(std::make_unique<LoadingGameScene>());
	}
}