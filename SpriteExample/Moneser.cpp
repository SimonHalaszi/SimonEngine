#include "Moneser.hpp"

Moneser::Moneser(
	const Transform2D& localTransform,
	const std::string& name,
	const SpriteSheet* spriteSheet
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = "Moneser";
	spriteSheet_ = spriteSheet;
}

void Moneser::onStart() {
	Transform2D shadowTransform = {
		Vector2D({0.0f, -1.0625f}),
		Vector2D({1.0f, 0.0625f}),
		0.0f,
		false,
		false
	};
	attachChild(std::make_unique<NonColliderSprite>(
		shadowTransform,
		"Shadow",
		"Shadow",
		&SpriteRegistry::getInstance().getSprite("shadow")
	)
	);
}

void Moneser::draw() {
	const Transform2D& transform = getWorldTransform();
	int animationFrame = Game::getInstance().getAnimationFrame();

	drawSpriteWithTransform(
		transform,
		(*spriteSheet_)[animationFrame % spriteSheet_->spriteCount()]
	);
}