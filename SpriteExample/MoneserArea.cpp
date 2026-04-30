#include "MoneserArea.hpp"

MoneserArea::MoneserArea(
	const Transform2D& localTransform,
	const std::string& name,
	const std::string& tag,
	const Sprite* uiSpriteFight,
	const Sprite* uiSpriteTake
) {
	localTransform_ = localTransform;
	name_ = name;
	tag_ = tag;
	uiSpriteFight_ = uiSpriteFight;
	uiSpriteTake_ = uiSpriteTake;
}

void MoneserArea::onStart() {
	const Transform2D& transform = getWorldTransform();
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
	UISpriteElement* uiElement = getAttachedUIElement();
	if (uiElement) {
		uiElement->setDrawing(false);
	}
}

// Supposed Parent Type
#include "Moneser.hpp"

void MoneserArea::update() {
	UISpriteElement* uiElement = getAttachedUIElement();
	if (uiElement) {
		uiElement->setDrawing(false);
	}
	Moneser* parent = dynamic_cast<Moneser*>(getParent());
	if (parent) {
		if (parent->getHealth() <= 0.0f) {
			uiElement->changeSprite(uiSpriteTake_);
		}
	}
}

void MoneserArea::onCollision(CollisionObject2D& other) {
	if (other.getTag() == "Player") {
		UISpriteElement* uiElement = getAttachedUIElement();
		if (uiElement) {
			uiElement->setDrawing(true);
		}
	}
}

UISpriteElement* MoneserArea::getAttachedUIElement() {
	for (const auto& child : *getChildren()) {
		UISpriteElement* uiElement = dynamic_cast<UISpriteElement*>(child.get());
		if (uiElement) {
			return uiElement;
		}
	}
	return nullptr;
}