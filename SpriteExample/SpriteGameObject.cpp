#include "SpriteGameObject.hpp"

SpriteGameObject::SpriteGameObject(Transform2D transform2D, std::string spriteName, std::string tag) {
	localTransform_ = transform2D;
	spriteName_ = spriteName;
	sprite_ = nullptr;
	tag_ = tag;
}

void SpriteGameObject::onStart() {
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName_));
}

void SpriteGameObject::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*sprite_
	);
}