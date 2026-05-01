#include "Player.hpp"
#include <cmath>

Player::Player(
	const Transform2D& localTransform,
	const std::string& name,
	const float& power,
	const SpriteSheet* sheetDown,
	const SpriteSheet* sheetSideways,
	const SpriteSheet* sheetUp,
	const Sprite* normIcon,
	const Sprite* grassIcon,
	const Sprite* fireIcon,
	const Sprite* waterIcon,
	const Sprite* healDisplay,
	const Sprite* goToMenuDisplay,
	const Sprite* healthDisplay,
	const Sprite* healthBar
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = "Player";
	power_ = power;
	sheetDown_ = sheetDown;
	sheetSideways_ = sheetSideways;
	sheetUp_ = sheetUp;

	normIcon_ = normIcon;
	grassIcon_ = grassIcon;
	fireIcon_ = fireIcon;
	waterIcon_ = waterIcon;

	healDisplay_ = healDisplay;
	goToMenuDisplay_ = goToMenuDisplay;

	healthDisplay_ = healthDisplay;
	healthBar_ = healthBar;

	speed_ = 1.0f;
	frameMovement_ = Vector2D({ 0.0f, 0.0f });
	moving_ = false;
	teleportedAlready_ = false;
	direction_ = 'd';
	health_ = 100.0f;
	moves_ = {};
	moveIndex_ = -1;
}

void Player::onStart() {
	const Transform2D& transform = getWorldTransform();
	attachChild(std::make_unique<Camera>(
		transform
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
		&SpriteRegistry::getInstance().getSprite("Shadow")
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
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.0f, 0.8f}),
			Vector2D({0.3f, 0.1f}),
			0.0f,
			false, false
			}),
		"HealDisplay",
		"HealDisplay",
		healDisplay_
	)
	);
	UISpriteElement* healDisplay = getAttachedUIElement("HealDisplay");
	if (healDisplay) {
		healDisplay->setDrawing(false);
	}
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.0f, -0.8f}),
			Vector2D({0.3f, 0.1f}),
			0.0f,
			false, false
			}),
		"GoToMenuDisplay",
		"GoToMenuDisplay",
		goToMenuDisplay_
	)
	);
	UISpriteElement* goToMenuDisplay = getAttachedUIElement("GoToMenuDisplay");
	if (goToMenuDisplay) {
		goToMenuDisplay->setDrawing(false);
	}
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({-0.8f, -0.8f}),
			Vector2D({0.1f, 0.1f}),
			0.0f,
			false, false
			}),
		"HealthUI",
		"HealthUI",
		healthDisplay_
	)
	);
	attachChild(std::make_unique<HealthBar>(
		Transform2D({
			Vector2D({-0.8f, -0.8f}),
			Vector2D({0.1f, 0.1f}),
			0.0f,
			false, false
			}),
		"HealthBar",
		healthBar_,
		health_
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

	if (health_ <= 0.0f) {
		destroy();
		SoundManager::getInstance().playSound2D("audio/Ouch.mp3");
		return;
	}

	UISpriteElement* healDisplay = getAttachedUIElement("HealDisplay");
	if (healDisplay) {
		healDisplay->setDrawing(false);
	}
	UISpriteElement* goToMenuDisplay = getAttachedUIElement("GoToMenuDisplay");
	if (goToMenuDisplay) {
		goToMenuDisplay->setDrawing(false);
	}

	teleportedAlready_ = false;
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
	if (InputManager::getInstance().isPressed('r')) {
		if (moveIndex_ != -1) {
			++moveIndex_;
			moveIndex_ = moveIndex_ % moves_.size();
			updateIconDisplay();
		}
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

#include "Moneser.hpp"
#include "MainMenuScene.hpp"

void Player::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (health_ <= 0.0f) {
		return;
	}

	if (other.getTag() == "RestArea") {
		if (InputManager::getInstance().isPressed('e')) {
			health_ = 100.0f;
			SoundManager::getInstance().playSound2D("audio/Yawn.mp3");
		}
		if(InputManager::getInstance().isPressed('q')) {
			if (moves_.size() == 4) {
				Game::getInstance().changeScene(std::make_unique<MainMenuScene>());
			}
		}

		UISpriteElement* healDisplay = getAttachedUIElement("HealDisplay");
		if (healDisplay) {
			healDisplay->setDrawing(true);
		}
		if (moves_.size() == 4) {
			UISpriteElement* goToMenuDisplay = getAttachedUIElement("GoToMenuDisplay");
			if (goToMenuDisplay) {
				goToMenuDisplay->setDrawing(true);
			}
		}
	}

	// Handle battles and taking
	if (other.getTag() == "MoneserArea") {
		if (InputManager::getInstance().isPressed('e')) {
			MoneserArea* moneserArea = dynamic_cast<MoneserArea*>(&other);
			if (moneserArea) {
				Moneser* moneser = moneserArea->getMoneser();
				if (moneser->getHealth() > 0.0f) {
					moneser->handleMove(this);
				}
				else {
					if (!hasType(moneser->getType())) {
						moves_.push_back(moneser->getType());
					}
					if (moveIndex_ == -1) {
						moveIndex_ = 0;
						attachChild(std::make_unique<UISpriteElement>(
							Transform2D({
								Vector2D({-0.8f, 0.8f}),
								Vector2D({0.1f, 0.1f}),
								0.0f,
								false, false
								}),
							"IconDisplay",
							"IconDisplay",
							normIcon_
						)
						);
						updateIconDisplay();
					}
					moneser->destroy();
					SoundManager::getInstance().playSound2D("audio/LetsGo.mp3");
				}
			}
		}
	}

	// Teleporter Collision Handling
	if (other.getTag() == "Teleporter" && getCurrentType() != MoneserType::Null) {
		if (InputManager::getInstance().isPressed('e')) {
			Teleporter* teleporter = dynamic_cast<Teleporter*>(&other);
			if (teleporter && !teleportedAlready_) {
				teleportedAlready_ = true;
				localTransform_.position = teleporter->getToLocation();
				SoundManager::getInstance().playSound2D("audio/Door.mp3");
				updateWorldTransform();
				// Camera doesnt get this update. So manually push it, or else desync
				Camera* camera = getAttachedCamera();
				if (camera) {
					camera->rootUpdate();
				}
				return;
			}
			else {
				return;
			}
		}
	}

	// Standard Collision Handling
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

		if (resolveX) {
			if (frameMovement_.x == 0.0f) {
				float playerCenterX = (playerAABB.min.x + playerAABB.max.x) * 0.5f;
				float otherCenterX = (otherAABB.min.x + otherAABB.max.x) * 0.5f;
				frameMovement_.x = (playerCenterX > otherCenterX) ? -1.0f : 1.0f;
			}
			localTransform_.position.x += (frameMovement_.x > 0.0f) ? -(overlapX) : (overlapX);
			frameMovement_.x = 0.0f;
		}
		else {
			if (frameMovement_.y == 0.0f) {
				float playerCenterY = (playerAABB.min.y + playerAABB.max.y) * 0.5f;
				float otherCenterY = (otherAABB.min.y + otherAABB.max.y) * 0.5f;
				frameMovement_.y = (playerCenterY > otherCenterY) ? -1.0f : 1.0f;
			}
			localTransform_.position.y += (frameMovement_.y > 0.0f) ? -(overlapY) : (overlapY);
			frameMovement_.y = 0.0f;
		}

		updateWorldTransform();
		// Camera doesnt get this update. So manually push it, or else desync
		Camera* camera = getAttachedCamera();
		if (camera) {
			camera->rootUpdate();
		}
		return;
	}
}

void Player::onDestruction() {
	std::string youDiedFilePath = "image/YouDied.png";
	std::string youDiedKey = "YouDied";
	GLuint texID = TextureRegistry::getInstance().loadTexture(youDiedFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		youDiedKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	Scene* currentScene = Game::getInstance().modifyCurrentScene();
	currentScene->addRootGameObject2D(
		std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.0f, -0.8f}),
			Vector2D({0.3f, 0.1f}),
			0.0f,
			false, false
			}),
		"DeadUI",
		"DeadUI",
		sprite
	)
	);
	currentScene->addRootGameObject2D(
		std::make_unique<DeadHandler>()
	);
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

UISpriteElement* Player::getAttachedUIElement(const std::string& name) {
	for (const auto& child : *getChildren()) {
		UISpriteElement* uiElement = dynamic_cast<UISpriteElement*>(child.get());
		if (uiElement) {
			if (uiElement->getName() == name) {
				return uiElement;
			}
		}
	}
	return nullptr;
}

void Player::updateIconDisplay() {
	UISpriteElement* iconDisplay = getAttachedUIElement("IconDisplay");
	if (iconDisplay) {
		if (moves_[moveIndex_] == MoneserType::Norm) {
			iconDisplay->changeSprite(normIcon_);
		}
		else if (moves_[moveIndex_] == MoneserType::Grass) {
			iconDisplay->changeSprite(grassIcon_);
		}
		else if (moves_[moveIndex_] == MoneserType::Fire) {
			iconDisplay->changeSprite(fireIcon_);
		}
		else if (moves_[moveIndex_] == MoneserType::Water) {
			iconDisplay->changeSprite(waterIcon_);
		}
	}
}

bool Player::hasType(const MoneserType& type) {
	for (const auto& typeIn : moves_) {
		if (typeIn == type) {
			return true;
		}
	}
	return false;
}