#include "Player.hpp"

Player::Player(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const Sprite* sprite
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	sprite_ = sprite;
	speed_ = 1.0f;
}


void Player::onStart() {
	const Transform2D& transform = getWorldTransform();
	attachChild(std::make_unique<Axis>(
		transform,
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		false,
		'y'
	)
	);
	attachChild(std::make_unique<Axis>(
		transform,
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		false,
		'x'
	)
	);
	attachChild(std::make_unique<Camera>(
		transform
	)
	);
}

void Player::draw() {
	const Transform2D& transform = getWorldTransform();
	drawSpriteWithTransform(
		transform,
		*sprite_
	);
}

void Player::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	float stepSpeed = speed_ * (1.0f / Game::getInstance().getUpdateSpeed());

	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_UP))) {
		localTransform_.position.y += stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_DOWN))) {
		localTransform_.position.y -= stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_LEFT))) {
		localTransform_.position.x -= stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_RIGHT))) {
		localTransform_.position.x += stepSpeed;
	}

	updateWorldTransform();
}

void Player::onCollision(CollisionObject2D& other) {

}

void Player::establishFields() {
	attachIField(std::make_unique<FloatField>("Speed", &speed_));
}