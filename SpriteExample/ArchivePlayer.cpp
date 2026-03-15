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
	tag_ = "Player";
}

void ArchivePlayer::onStart() {
	playerSpriteSheet_ = &(SpriteSheetRegistry::getInstance().getSpriteSheet(playerSpritesSheetName_));
}

void ArchivePlayer::draw() {
	Transform2D transform = getWorldTransform();

	if (drawHitbox_) {
		drawSquare(
			transform.position,
			transform.scale.x, transform.rotation,
			transform.mirror, transform.flip,
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f }
		);
	}
	
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
	if (InputManager::getInstance().isPressed('s')) {
		if (drawHitbox_) {
			drawHitbox_ = false;
		} else {
			drawHitbox_ = true;
		}
	}

	localTransform_.position.x += moveX_;
	localTransform_.position.y += moveY_;

	outDateWorldTransform();
}

void ArchivePlayer::onCollision(CollisionObject2D& other) {
	std::cout << "Player collided with object with tag " << other.getTag() << std::endl;
}