#include "StaticSprite.hpp"

StaticSprite::StaticSprite(Transform2D transform2D, std::string spriteName) {
	localTransform_ = transform2D;
	spriteName_ = spriteName;
	sprite_ = nullptr;
}

void StaticSprite::onStart() {
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName_));
}

void StaticSprite::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*sprite_
	);
}