#include "PlatformerPlayer.hpp"

// Will be a child
#include "Axis.hpp"

PlatformerPlayer::PlatformerPlayer(std::string playerSpritesSheetKey) {
	localTransform_ = {
		{0.0f, 0.0f},
		{0.1f, 0.1f},
		0.0f,
		false,
		false
	};
	playerSpritesSheetKey_ = playerSpritesSheetKey;
	playerSpriteSheet_ = nullptr;
	tag_ = "Player";
}

void PlatformerPlayer::onStart() {
	playerSpriteSheet_ = &(SpriteSheetRegistry::getInstance().getSpriteSheet(playerSpritesSheetKey_));

	attachChild(std::make_unique<Axis>(
			Transform2D({ Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.0f, 0.0f }),
			0.0f,
			false,
			false, }),
			ColorRGB({ 1.0f, 0.0f, 0.0f }),
			ColorRGB({ 1.0f, 0.0f, 0.0f }),
			true,
			'x'
		)
	);
	attachChild(std::make_unique<Axis>(
			Transform2D({ Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.0f, 0.0f }),
			0.0f,
			false,
			false, }),
			ColorRGB({ 0.0f, 1.0f, 0.0f }),
			ColorRGB({ 0.0f, 1.0f, 0.0f }),
			true,
			'y'
		)
	);
	attachChild(std::make_unique<PlayerGroundChecker>(
			Transform2D({ Vector2D({ 0.0f, -1.0f }),
			Vector2D({ 1.0f, 0.10 }),
			0.0f,
			false,
			false, })
		)
	);

	jumpTimeInUpdateFrames_ = jumpTime_ * Game::getInstance().getCurrentScene()->getUpdateSpeed();
}

void PlatformerPlayer::draw() {
	Transform2D transform = getWorldTransform();

	if (drawHitbox_) {
		drawSquare(
			transform.position,
			transform.scale.x, transform.rotation,
			transform.mirror, transform.flip,
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f },
			ColorRGB{ 1.0f, 0.0f, 0.0f }
		);
	}

	if (moveX_) {
		// Drawing from a sprite sheet
		drawSprite(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			playerSpriteSheet_->getSpriteAt(
				Game::getInstance().getCurrentScene()->getAnimationFrame() % playerSpriteSheet_->spriteCount()
			)
		);
	}
	else {
		drawSprite(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			playerSpriteSheet_->getSpriteAt(0)
		);
	}

}

void PlatformerPlayer::update() {

	float physicsTime = 1.0f / Game::getInstance().getCurrentScene()->getUpdateSpeed();

	moveX_ = moveY_ = 0;

	// Gravity
	if (!PlayerGroundChecker::getGroundStatus() && !jumping_) {
		moveY_ -= gravitySpeed_ * physicsTime;
	}

	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_LEFT))) {
		moveX_ -= speed_ * physicsTime;
		localTransform_.mirror = true;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_RIGHT))) {
		moveX_ += speed_ * physicsTime;
		localTransform_.mirror = false;
	}
	if (InputManager::getInstance().isDown(32)) {
		if (!jumping_ && PlayerGroundChecker::getGroundStatus()) {
			jumping_ = true;
		}
	}
	if (InputManager::getInstance().isPressed('s')) {
		if (drawHitbox_) {
			drawHitbox_ = false;
		}
		else {
			drawHitbox_ = true;
		}
	}

	if (jumping_) {
		++jumpFrame_;
		moveY_ += jumpSpeed_ * physicsTime;
		if (jumpFrame_ >= jumpTimeInUpdateFrames_) {
			jumping_ = false;
			jumpFrame_ = 0;
		}
	}

	localTransform_.position.x += moveX_;
	localTransform_.position.y += moveY_;

	centerCameraOnPlayer();

	outDateWorldTransform();

	collisionCorrectionX_ = 0.0f;
	collisionCorrectionY_ = 0.0f;
}

void PlatformerPlayer::onCollision(CollisionObject2D& other) {
	AABB playerHitbox = getAABB();
	AABB otherHitbox = other.getAABB();

	float overlapLeft = playerHitbox.max.x - otherHitbox.min.x;
	float overlapRight = otherHitbox.max.x - playerHitbox.min.x;
	float overlapBottom = playerHitbox.max.y - otherHitbox.min.y;
	float overlapTop = otherHitbox.max.y - playerHitbox.min.y;

	if (other.getTag() == "Floor") {
		if (overlapTop > 0.0f && overlapTop < playerHitbox.max.y - playerHitbox.min.y) {
			float correction = overlapTop + collisionTolerance_;

			if (correction > collisionCorrectionY_) {
				localTransform_.position.y += (correction - collisionCorrectionY_);
				collisionCorrectionY_ = correction;
				outDateWorldTransform();
			}
		}
	}
	else if (other.getTag() == "Ceiling") {
		if (overlapBottom > 0.0f && overlapBottom < playerHitbox.max.y - playerHitbox.min.y) {
			float correction = -(overlapBottom + collisionTolerance_);

			if (correction < collisionCorrectionY_) {
				localTransform_.position.y += (correction - collisionCorrectionY_);
				collisionCorrectionY_ = correction;
				outDateWorldTransform();
			}

			if (jumping_) {
				jumping_ = false;
				jumpFrame_ = 0;
			}
		}
	}
	else if (other.getTag() == "LeftWall") {
		if (overlapRight > 0.0f && overlapRight < playerHitbox.max.x - playerHitbox.min.x) {
			float correction = overlapRight + collisionTolerance_;

			if (correction > collisionCorrectionX_) {
				localTransform_.position.x += (correction - collisionCorrectionX_);
				collisionCorrectionX_ = correction;
				outDateWorldTransform();
			}
		}
	}
	else if (other.getTag() == "RightWall") {
		if (overlapLeft > 0.0f && overlapLeft < playerHitbox.max.x - playerHitbox.min.x) {
			float correction = -(overlapLeft + collisionTolerance_);

			if (correction < collisionCorrectionX_) {
				localTransform_.position.x += (correction - collisionCorrectionX_);
				collisionCorrectionX_ = correction;
				outDateWorldTransform();
			}
		}
	}

	centerCameraOnPlayer();
}

void PlatformerPlayer::centerCameraOnPlayer() {
	Transform2D transform = getWorldTransform();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-transform.position.x, -transform.position.y, 0);
}