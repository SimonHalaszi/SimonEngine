#include "NonColliderSpriteAnimated.hpp"

NonColliderSpriteAnimated::NonColliderSpriteAnimated(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const SpriteSheet* spriteSheet
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	spriteSheet_ = spriteSheet;
}

void NonColliderSpriteAnimated::draw() {
	const Transform2D& transform = getWorldTransform();
	int animationFrame = Game::getInstance().getAnimationFrame();

	drawSpriteWithTransform(
		transform,
		(*spriteSheet_)[animationFrame % spriteSheet_->spriteCount()]
	);
}