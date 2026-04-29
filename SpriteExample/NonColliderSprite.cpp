#include "NonColliderSprite.hpp"

NonColliderSprite::NonColliderSprite(
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

void NonColliderSprite::draw() {
	const Transform2D& transform = getWorldTransform();
	drawSpriteWithTransform(
		transform,
		*sprite_
	);
}