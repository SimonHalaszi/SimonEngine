#include "MainMenu.hpp"

MainMenu::MainMenu(
	const Transform2D& localTransform,
	const Sprite* main,
	const Sprite* controls,
	const Sprite* howTo
) {
	localTransform_ = localTransform;
	name_ = "MainMenu";
	tag_ = "MainMenu";
	main_ = main;
	controls_ = controls;
	howTo_ = howTo;
	sprite_ = main_;
}

#include "LoadingGameScene.hpp"

void MainMenu::update() {
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('c')) {
		if (controls_) {
			if ( sprite_ == main_) {
				changeSprite(controls_);
			}
		}
	}
	if (InputManager::getInstance().isPressed('h')) {
		if (howTo_) {
			if ( sprite_ == main_ ) {
				changeSprite(howTo_);
			}
		}
	}
	if (InputManager::getInstance().isPressed('q')) {
		Game::getInstance().safeGameExit();
	}
	if (InputManager::getInstance().isPressed('g')) {
		if (getSprite() == controls_ || getSprite() == howTo_) {
				changeSprite(main_);
		}
		else {
			Game::getInstance().changeScene(std::make_unique<LoadingGameScene>());
		}
	}
}