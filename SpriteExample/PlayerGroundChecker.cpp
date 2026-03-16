#include "PlayerGroundChecker.hpp"

#include "Game.hpp"

bool PlayerGroundChecker::onGround_ = false;

PlayerGroundChecker::PlayerGroundChecker(Transform2D transform2D) {
	localTransform_ = transform2D;
	tag_ = "PlayerGroundChecker";
}

void PlayerGroundChecker::draw() {
	if (draw_) {
		Transform2D transform = getWorldTransform();

		drawRectangle(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f }
		);
	}
}

void PlayerGroundChecker::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	onGround_ = false;
}

void PlayerGroundChecker::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	if (other.getTag() == "Floor") {
		onGround_ = true;
	}
}