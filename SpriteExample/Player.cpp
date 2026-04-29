#include "Player.hpp"
#include <cmath>

Player::Player(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const SpriteSheet* sheetDown,
	const SpriteSheet* sheetSideways,
	const SpriteSheet* sheetUp
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	sheetDown_ = sheetDown;
	sheetSideways_ = sheetSideways;
	sheetUp_ = sheetUp;
	speed_ = 1.0f;
	frameMovement_ = Vector2D({ 0.0f, 0.0f });
	moving_ = false;
	direction_ = 'd';
}

void Player::onStart() {
	const Transform2D& transform = getWorldTransform();
	attachChild(std::make_unique<Camera>(
		transform
	)
	);
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

	Transform2D shadowTransform = {
		Vector2D({0.0f, -1.0625f}),
		Vector2D({0.75f, 0.0625f}),
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

void Player::draw() {
	const Transform2D& transform = getWorldTransform();

	int animationFrame;
	if (moving_) {
		animationFrame = Game::getInstance().getAnimationFrame();
	}
	else {
		animationFrame = 1;
	}
	
	if (direction_ == 'l' || direction_ == 'r') {
		if (sheetSideways_) {
			drawSpriteWithTransform(
				transform,
				(*sheetSideways_)[animationFrame % sheetSideways_->spriteCount()]
			);
			return;
		}
	}
	if (direction_ == 'u') {
		if (sheetUp_) {
			drawSpriteWithTransform(
				transform,
				(*sheetUp_)[animationFrame % sheetUp_->spriteCount()]
			);
			return;
		}
	}
	if (direction_ == 'd') {
		if (sheetDown_) {
			drawSpriteWithTransform(
				transform,
				(*sheetDown_)[animationFrame % sheetDown_->spriteCount()]
			);
			return;
		}
	}
}

void Player::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	frameMovement_ = Vector2D({ 0.0f, 0.0f });
	moving_ = false;

	float stepSpeed = speed_ * (1.0f / Game::getInstance().getUpdateSpeed());
	bool mirror = localTransform_.mirror;

	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_UP))) {
		frameMovement_.y += stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_DOWN))) {
		frameMovement_.y -= stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_RIGHT))) {
		frameMovement_.x += stepSpeed;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_LEFT))) {
		frameMovement_.x -= stepSpeed;
	}

	localTransform_.position.y += frameMovement_.y;
	localTransform_.position.x += frameMovement_.x;

	if (frameMovement_.y != 0.0f) {
		if (frameMovement_.y > 0.0f) {
			direction_ = 'u';
		}
		else {
			direction_ = 'd';
		}
		moving_ = true;
	}
	if (frameMovement_.x != 0.0f) {
		if (frameMovement_.x > 0.0f) {
			direction_ = 'r';
			localTransform_.mirror = false;
		}
		else {
			direction_ = 'l';
			localTransform_.mirror = true;
		}
		moving_ = true;
	}

	if ((frameMovement_.y != 0.0f || frameMovement_.x != 0.0f)) {
		updateWorldTransform();
	}
}

void Player::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (other.getTag() == "Collider" || other.getTag() == "Moneser") {
		AABB playerAABB = getAABB();
		AABB otherAABB = other.getAABB();

		float overlapX = std::min(playerAABB.max.x, otherAABB.max.x) - std::max(playerAABB.min.x, otherAABB.min.x);
		float overlapY = std::min(playerAABB.max.y, otherAABB.max.y) - std::max(playerAABB.min.y, otherAABB.min.y);
		if (overlapX <= 0.0f || overlapY <= 0.0f) {
			return;
		}

		bool resolveX = false;
		if (frameMovement_.x != 0.0f && frameMovement_.y == 0.0f) {
			resolveX = true;
		}
		else if (frameMovement_.x == 0.0f && frameMovement_.y != 0.0f) {
			resolveX = false;
		}
		else if (frameMovement_.x != 0.0f && frameMovement_.y != 0.0f) {
			float xRatio = overlapX / std::abs(frameMovement_.x);
			float yRatio = overlapY / std::abs(frameMovement_.y);
			resolveX = (xRatio < yRatio);
		}
		else {
			resolveX = (overlapX < overlapY);
		}

		auto pushX = [&](float moveX) {
			if (moveX == 0.0f) {
				float playerCenterX = (playerAABB.min.x + playerAABB.max.x) * 0.5f;
				float otherCenterX = (otherAABB.min.x + otherAABB.max.x) * 0.5f;
				moveX = (playerCenterX > otherCenterX) ? -1.0f : 1.0f;
			}
			localTransform_.position.x += (moveX > 0.0f) ? -(overlapX) : (overlapX);
			frameMovement_.x = 0.0f;
		};

		auto pushY = [&](float moveY) {
			if (moveY == 0.0f) {
				float playerCenterY = (playerAABB.min.y + playerAABB.max.y) * 0.5f;
				float otherCenterY = (otherAABB.min.y + otherAABB.max.y) * 0.5f;
				moveY = (playerCenterY > otherCenterY) ? -1.0f : 1.0f;
			}
			localTransform_.position.y += (moveY > 0.0f) ? -(overlapY) : (overlapY);
			frameMovement_.y = 0.0f;
		};

		if (resolveX) {
			pushX(frameMovement_.x);
		}
		else {
			pushY(frameMovement_.y);
		}

		updateWorldTransform();
		playerAABB = getAABB();
		overlapX = std::min(playerAABB.max.x, otherAABB.max.x) - std::max(playerAABB.min.x, otherAABB.min.x);
		overlapY = std::min(playerAABB.max.y, otherAABB.max.y) - std::max(playerAABB.min.y, otherAABB.min.y);
		if (overlapX > 0.0f && overlapY > 0.0f) {
			if (resolveX) {
				pushY(frameMovement_.y);
			}
			else {
				pushX(frameMovement_.x);
			}
		}

		if (frameMovement_.x == 0.0f && frameMovement_.y == 0.0f) {
			moving_ = false;
		}

		updateWorldTransform();
		// Camera doesnt get this update. So manually push it, or else desync
		if (Camera* camera = getAttachedCamera()) {
			camera->rootUpdate();
		}
	}
}

void Player::onDestruction() {

}

void Player::establishFields() {
	attachIField(std::make_unique<FloatField>("Speed", &speed_));
}

Camera* Player::getAttachedCamera() {
	for (const auto& child : *getChildren()) {
		Camera* camera = dynamic_cast<Camera*>(child.get());
		if (camera) {
			return camera;
		}
	}
	return nullptr;
}