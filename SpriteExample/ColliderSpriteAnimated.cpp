#include "ColliderSpriteAnimated.hpp"

ColliderSpriteAnimated::ColliderSpriteAnimated(
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

void ColliderSpriteAnimated::draw() {
	const Transform2D& transform = getWorldTransform();
	int animationFrame = Game::getInstance().getAnimationFrame();

	drawSpriteWithTransform(
		transform,
		(*spriteSheet_)[animationFrame % spriteSheet_->spriteCount()]
	);
}