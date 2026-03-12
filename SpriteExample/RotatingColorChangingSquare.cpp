#include "RotatingColorChangingSquare.hpp"

RotatingColorChangingSquare::RotatingColorChangingSquare(
	const Transform2D& transform2D,
	const ColorRGB& colorTL,
	const ColorRGB& colorTR,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR,
	const ColorRGB& colorTL2,
	const ColorRGB& colorTR2,
	const ColorRGB& colorBL2,
	const ColorRGB& colorBR2
) {
	colorTL_ = colorTL;
	colorTR_ = colorTR;
	colorBL_ = colorBL;
	colorBR_ = colorBR;

	colorTL2_ = colorTL2;
	colorTR2_ = colorTR2;
	colorBL2_ = colorBL2;
	colorBR2_ = colorBR2;

	localTransform_ = transform2D;
	tag_ = "";
}

void RotatingColorChangingSquare::draw() {
	Transform2D transform = getWorldTransform();

	drawSquare(
		transform.position,
		transform.scale.x, transform.rotation,
		transform.mirror, transform.flip,
		colorTL_, colorTR_, colorBL_, colorBR_
	);
}

void RotatingColorChangingSquare::update() {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		std::swap(colorTL_, colorTL2_);
		std::swap(colorTR_, colorTR2_);
		std::swap(colorBL_, colorBL2_);
		std::swap(colorBR_, colorBR2_);
	}

	localTransform_.rotation += 20 * (1.0f / Game::getInstance().getCurrentScene()->getUpdateSpeed());
	if (localTransform_.rotation >= 360) {
		localTransform_.rotation = 0;
	}

	outDateWorldTransform();
}