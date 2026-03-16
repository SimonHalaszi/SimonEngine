#include "Coin.hpp"
#include "PlatformerPlayer.hpp"

Coin::Coin(Transform2D transform2D, std::string spriteName, std::string tag) {
	localTransform_ = transform2D;
	spriteName_ = spriteName;
	sprite_ = nullptr;
	tag_ = tag;
}

void Coin::onStart() {
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName_));
}

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