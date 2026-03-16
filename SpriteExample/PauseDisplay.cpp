#include "PauseDisplay.hpp"

#include "Game.hpp"

void PauseDisplay::onStart() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		drawElement_ = true;
	}
	else {
		drawElement_ = false;
	}
}

void PauseDisplay::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		drawElement_ = true;
	}
	else {
		drawElement_ = false;
	}
}