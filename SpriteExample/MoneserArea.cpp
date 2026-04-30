#include "MoneserArea.hpp"

MoneserArea::MoneserArea(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const Sprite* uiSpriteFight,
	const Sprite* uiSpriteTake,
	const Sprite* healthDisplay,
	const Sprite* healthBar
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	uiSpriteFight_ = uiSpriteFight;
	uiSpriteTake_ = uiSpriteTake;
	healthDisplay_ = healthDisplay;
	healthBar_ = healthBar;
}

// Supposed Parent Type
#include "Moneser.hpp"

void MoneserArea::onStart() {
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.0f, 0.8f}),
			Vector2D({0.3f, 0.1f}),
			0.0f,
			false, false
			}),
		"MoneserAreaUI",
		"MoneserAreaUI",
		uiSpriteFight_
	)
	);
	UISpriteElement* uiElement = getAttachedUIElement("MoneserAreaUI");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.8f, 0.8f}),
			Vector2D({0.1f, 0.1f}),
			0.0f,
			false, false
			}),
		"HealthUI",
		"HealthUI",
		healthDisplay_
	)
	);
	uiElement = getAttachedUIElement("HealthUI");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	attachChild(std::make_unique<HealthBar>(
		Transform2D({
			Vector2D({0.8f, 0.8f}),
			Vector2D({0.1f, 0.1f}),
			0.0f,
			false, false
			}),
		"HealthBar",
		healthBar_,
		getMoneser()->getHealthReference()
	)
	);
	uiElement = getAttachedUIElement("HealthBar");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
}

void MoneserArea::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	UISpriteElement* uiElement = getAttachedUIElement("HealthUI");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	uiElement = getAttachedUIElement("HealthBar");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	Moneser* parent = getMoneser();
	uiElement = getAttachedUIElement("MoneserAreaUI");
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	if (parent) {
		if (parent->getHealth() <= 0.0f) {
			if (uiElement) {
				uiElement->changeSprite(uiSpriteTake_);
			}
		}
	}
}

void MoneserArea::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (other.getTag() == "Player") {
		UISpriteElement* uiElement = getAttachedUIElement("MoneserAreaUI");
		if (uiElement) {
			uiElement->setDrawing(true);
		}
		uiElement = getAttachedUIElement("HealthUI");
		if (uiElement) {
			uiElement->setDrawing(true);
		}
		uiElement = getAttachedUIElement("HealthBar");
		if (uiElement) {
			uiElement->setDrawing(true);
		}
	}
}

UISpriteElement* MoneserArea::getAttachedUIElement(const std::string& name) {
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

Moneser* MoneserArea::getMoneser() {
	Moneser* parent = dynamic_cast<Moneser*>(getParent());
	if (parent) {
		return parent;
	}
	return nullptr;
}