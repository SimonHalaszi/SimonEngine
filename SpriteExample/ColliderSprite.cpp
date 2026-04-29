#include "ColliderSprite.hpp"

ColliderSprite::ColliderSprite(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const Sprite* sprite
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	sprite_ = sprite;
}

void ColliderSprite::draw() {
	const Transform2D& transform = getWorldTransform();
	drawSpriteWithTransform(
		transform,
		*sprite_
	);
}