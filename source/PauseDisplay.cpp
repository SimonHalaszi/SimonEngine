#include "PauseDisplay.hpp"

PauseDisplay::PauseDisplay(
	const Transform2D& localTransform,
	const std::string& name,
	const Sprite* sprite
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = "PauseDisplay";
	sprite_ = sprite;
	drawElement_ = false;
}

void PauseDisplay::update() {
	if (Game::getInstance().isPauseFlagged()) {
		drawElement_ = true;
	}
	else {
		drawElement_ = false;
	}
}