#include "Axis.hpp"

Axis::Axis(
	const Transform2D& localTransform,
	const ColorRGB& color1,
	const ColorRGB& color2,
	const bool& willDrawAxis,
	const char& axis
) {
	localTransform_ = localTransform;
	color1_ = color1;
	color2_ = color2;
	willDrawAxis_ = willDrawAxis;
	axis_ = axis;
	if (axis == 'x' || axis == 'X') {
		name_ = "X-Axis";
		tag_ = "X-Axis";
	}
	else if (axis == 'y' || axis == 'X') {
		name_ = "Y-Axis";
		tag_ = "Y-Axis";
	}
	else {
		name_ = "Invalid-Axis";
		tag_ = "Invalid-Axis";
	}
}

void Axis::draw() {
	Transform2D transform = getWorldTransform();

	if (willDrawAxis_) {
		if (axis_ == 'x' || axis_ == 'X') {
			drawLine(
				transform.position, { transform.position.x + 0.25f, transform.position.y },
				color1_, color2_
			);
			drawTriangle(
				{ transform.position.x + 0.25f, transform.position.y },
				0.015f, 270.0f,
				false, false,
				color2_, color2_, color2_
			);
		}
		else if (axis_ =='y' || axis_ == 'Y') {
			drawLine(
				transform.position, { transform.position.x, transform.position.y + 0.25f },
				color1_, color2_
			);
			drawTriangle(
				{ transform.position.x, transform.position.y + 0.25f },
				0.015f, 0.0f,
				false, false,
				color2_, color2_, color2_
			);
		}
	}
}

void Axis::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	if (InputManager::getInstance().isPressed('a')) {
		if (willDrawAxis_) {
			willDrawAxis_ = false;
		}
		else {
			willDrawAxis_ = true;
		}
	}
}