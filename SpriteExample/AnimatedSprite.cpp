#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(Transform2D transform2D, std::string spriteName) {
	localTransform_ = transform2D;
	spriteSheetName_ = spriteName;
	spriteSheet_ = nullptr;
	frame_ = Game::getInstance().getCurrentScene()->getAnimationFrame();
}

void AnimatedSprite::onStart() {
	spriteSheet_ = &(SpriteSheetRegistry::getInstance().getSpriteSheet(spriteSheetName_));
}

void AnimatedSprite::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		(*spriteSheet_)[frame_ % spriteSheet_->spriteCount()]
	);
}

void AnimatedSprite::update() {
	frame_ = Game::getInstance().getCurrentScene()->getAnimationFrame();
}