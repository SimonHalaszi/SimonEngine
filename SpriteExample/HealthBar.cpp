#include "HealthBar.hpp"

HealthBar::HealthBar(
	const Transform2D& localTransform,
	const std::string& name,
	const Sprite* healthBar,
	const float& health
) : health_(health) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = "HealthBar";
	sprite_ = healthBar;

	float tempHealth = health_;
	float scaledHealth = ((health_ / 100.0f) * 0.1f);
	localTransform_.scale = { 0.1f - scaledHealth, 0.1f };
}

void HealthBar::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	float tempHealth = health_;
	float scaledHealth = ((health_ / 100.0f) * 0.1f);
	localTransform_.scale = { 0.1f - scaledHealth, 0.1f };
	updateWorldTransform();
}