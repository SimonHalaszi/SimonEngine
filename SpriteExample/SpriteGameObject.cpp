#include "SpriteGameObject.hpp"

SpriteGameObject::SpriteGameObject(
	const Transform2D& transform2D,
	const std::string& name,
	const std::string& tag,
	const Sprite* sprite
) {
	localTransform_ = transform2D;
	name_ = name;
	tag_ = tag;
	sprite_ = sprite;
}

void SpriteGameObject::draw() {
	Transform2D transform = getWorldTransform();

	drawSpriteWithTransform(
		transform,
		*sprite_
	);
}