#include "SpriteGameObject.hpp"

SpriteGameObject::SpriteGameObject(Transform2D transform2D, std::string spriteFilePath, std::string spriteName, std::string tag) {
	localTransform_ = transform2D;
	sprite_ = nullptr;
	tag_ = tag;
	name_ = "SpriteGameObject";
	TextureRegistry::getInstance().loadTexture(spriteFilePath);
	SpriteRegistry::getInstance().makeSprite(
		spriteName,
		TextureRegistry::getInstance().getTextureID(spriteFilePath),
		1, 1,
		{ 0, 0 }
	);
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName));
}

void SpriteGameObject::onStart() {}

void SpriteGameObject::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*sprite_
	);
}