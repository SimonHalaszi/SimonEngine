#include "ArchivePlayer.hpp"

ArchivePlayer::ArchivePlayer(std::string playerSpritesSheetName) {
	localTransform_ = {
		{0.0f, 0.0f},
		{0.25f, 0.25f},
		0.0f,
		false,
		false
	};
	playerSpritesSheetName_ = playerSpritesSheetName;
	playerSpriteSheet_ = nullptr;
}

void ArchivePlayer::onStart() {
	playerSpriteSheet_ = &(SpriteSheetRegistry::getInstance().getSpriteSheet(playerSpritesSheetName_));
}

void ArchivePlayer::draw() {
	Transform2D transform = getWorldTransform();
	
	if (moveX_ || moveY_) {
		// Drawing from a sprite sheet
		drawSprite(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			playerSpriteSheet_->getSpriteAt(
				Game::getInstance().getCurrentScene()->getAnimationFrame() % playerSpriteSheet_->spriteCount()
			)
		);
	}
	else {
		drawSprite(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			playerSpriteSheet_->getSpriteAt(0)
		);
	}
}

void ArchivePlayer::update() {
	float physicsTime = 1.0f / Game::getInstance().getCurrentScene()->getUpdateSpeed();
	
	moveX_ = moveY_ = 0;

	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_LEFT))) {
		moveX_ -= speed_ * physicsTime;
		localTransform_.mirror = true;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_RIGHT))) {
		moveX_ += speed_ * physicsTime;
		localTransform_.mirror = false;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_DOWN))) {
		moveY_ -= speed_ * physicsTime;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_UP))) {
		moveY_ += speed_ * physicsTime;
	}

	localTransform_.position.x += moveX_;
	localTransform_.position.y += moveY_;

	outDateWorldTransform();
}