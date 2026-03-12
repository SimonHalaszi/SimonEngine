#include "Axis.hpp"

Axis::Axis(Transform2D transform2D, ColorRGB color1, ColorRGB color2, bool willDrawAxis, char axis) {
	localTransform_ = transform2D;
	color1_ = color1;
	color2_ = color2;
	willDrawAxis_ = willDrawAxis;
	axis_ = axis;
}

void Axis::draw() {
	Transform2D transform = getWorldTransform();

	if (willDrawAxis_) {
		if (axis_ == 'x') {
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
		else if (axis_ =='y') {
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
	if (InputManager::getInstance().isPressed('a')) {
		if (willDrawAxis_) {
			willDrawAxis_ = false;
		}
		else {
			willDrawAxis_ = true;
		}
	}
}