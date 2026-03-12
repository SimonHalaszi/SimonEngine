#include "RotatingColorChangingTriangle.hpp"

RotatingColorChangingTriangle::RotatingColorChangingTriangle(
	const Transform2D& transform2D,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR,
	const ColorRGB& colorT,
	const ColorRGB& colorBL2,
	const ColorRGB& colorBR2,
	const ColorRGB& colorT2
) {
	colorBL_ = colorBL;
	colorBR_ = colorBR;
	colorT_ = colorT;

	colorBL2_ = colorBL2;
	colorBR2_ = colorBR2;
	colorT2_ = colorT2;

	localTransform_ = transform2D;
	tag_ = "";
}

void RotatingColorChangingTriangle::draw() {
	Transform2D transform = getWorldTransform();

	drawTriangle(
		transform.position,
		transform.scale.x, transform.rotation,
		transform.mirror, transform.flip,
		colorBL_, colorBR_, colorT_
	);
}

void RotatingColorChangingTriangle::update() {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		std::swap(colorBL_, colorBL2_);
		std::swap(colorBR_, colorBR2_);
		std::swap(colorT_, colorT2_);
	}

	localTransform_.rotation += 20 * (1.0f / Game::getInstance().getCurrentScene()->getUpdateSpeed());
	if (localTransform_.rotation <= -360) {
		localTransform_.rotation = 0;
	}

	outDateWorldTransform();
}