#include "Coin.hpp"
#include "PlatformerPlayer.hpp"

Coin::Coin(Transform2D transform2D, std::string spriteFilePath, std::string spriteName) {
	localTransform_ = transform2D;
	sprite_ = nullptr;
	tag_ = "Coin";
	name_ = "Coin";
	TextureRegistry::getInstance().loadTexture(spriteFilePath);
	SpriteRegistry::getInstance().makeSprite(
		spriteName,
		TextureRegistry::getInstance().getTextureID(spriteFilePath),
		1, 1,
		{ 0, 0 }
	);
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName));
}

void Coin::onStart() {}

void Coin::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*sprite_
	);
}

void Coin::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	if (other.getTag() == "Player") {
		PlatformerPlayer::addToCoinCount(1);
		destroy();
	}
}