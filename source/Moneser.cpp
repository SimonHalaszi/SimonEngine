#include "Moneser.hpp"

Moneser::Moneser(
	const Transform2D& localTransform,
	const std::string& name,
	const float& power,
	const MoneserType& type,
	const SpriteSheet* spriteSheet,
	const Sprite* uiSpriteFight,
	const Sprite* uiSpriteTake,
	const Sprite* healthDisplay,
	const Sprite* healthBar
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = "Moneser";
	power_ = power;
	type_ = type;
	spriteSheet_ = spriteSheet;
	uiSpriteFight_ = uiSpriteFight;
	uiSpriteTake_ = uiSpriteTake;
	healthDisplay_ = healthDisplay;
	healthBar_ = healthBar;
	health_ = 100.0f;
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
		&SpriteRegistry::getInstance().getSprite("Shadow")
	)
	);
	attachChild(std::make_unique<MoneserArea>(
		Transform2D({
			Vector2D({0.0f, 0.0f}),
			Vector2D({2.0f, 2.0f}),
			0.0f,
			false, false
			}),
		(name_ + "Area"),
		"MoneserArea",
		uiSpriteFight_,
		uiSpriteTake_,
		healthDisplay_,
		healthBar_
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

void Moneser::establishFields() {
	attachIField(std::make_unique<FloatField>("Health", &health_));
}

// Player
#include "Player.hpp"
void Moneser::handleMove(Player* player) {
	// Player Moves First
	float playerDamageMult = getDamageMult(player->getCurrentType(), type_);
	health_ -= (player->getPower() * playerDamageMult);
	
	// If still alive Moneser responds
	if (health_ > 0.0f) {
		float moneserDamageMult = getDamageMult(type_, player->getCurrentType());
		player->setHealth((player->getHealth() - (power_ * moneserDamageMult)));
	}
}