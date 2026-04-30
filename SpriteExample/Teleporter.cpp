#include "Teleporter.hpp"

Teleporter::Teleporter(
	const Transform2D& localTransform,
	const std::string& name,
	const Vector2D& toLocation,
	const Sprite* uiSprite
) {
	localTransform_ = localTransform;
	name_ = name;
	toLocation_ = toLocation;
	uiSprite_ = uiSprite;

	tag_ = "Teleporter";
}

void Teleporter::onStart() {
	const Transform2D& transform = getWorldTransform();
	attachChild(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({0.0f, 0.8f}),
			Vector2D({0.3f, 0.1f}),
			0.0f,
			false, false
			}),
		"TeleporterUI",
		"TeleporterUI",
		uiSprite_
	)
	);
	UISpriteElement* uiElement = getAttachedUIElement();
	if (uiElement) {
		uiElement->setDrawing(false);
	}
}

void Teleporter::update() {
	UISpriteElement* uiElement = getAttachedUIElement();
	if (uiElement) {
		uiElement->setDrawing(false);
	}
}


void Teleporter::establishFields() {
	attachIField(std::make_unique<Vector2DField>("To Location", &toLocation_));
}

void Teleporter::onCollision(CollisionObject2D& other) {
	if (other.getTag() == "Player") {
		UISpriteElement* uiElement = getAttachedUIElement();
		if (uiElement) {
			uiElement->setDrawing(true);
		}
	}
}

UISpriteElement* Teleporter::getAttachedUIElement() {
	for (const auto& child : *getChildren()) {
		UISpriteElement* uiElement = dynamic_cast<UISpriteElement*>(child.get());
		if (uiElement) {
			return uiElement;
		}
	}
	return nullptr;
}