#include "VoidButton.hpp"

VoidButton::VoidButton() :
	windowArea_(),
	viewportArea_(),
	color_(),
	text_(""),
	clicked_(false),
	buttonAction_()
{}

VoidButton::VoidButton(
	WindowArea windowArea,
	ViewportArea viewportArea,
	ColorRGB color,
	std::string text,
	std::function<void()> buttonAction
) :
	windowArea_(windowArea),
	viewportArea_(viewportArea),
	color_(color),
	text_(text),
	clicked_(false),
	buttonAction_(buttonAction)
{}

bool VoidButton::isInside(int mouseX, int mouseY) const {
	float leftBoundary = windowArea_.pos.x;
	float rightBoundary = windowArea_.pos.x + windowArea_.scale.x;
	float topBoundary = windowArea_.pos.y;
	float bottomBoundary = windowArea_.pos.y + windowArea_.scale.y;

	bool insideX = (mouseX >= leftBoundary && mouseX <= rightBoundary);
	bool insideY = (mouseY >= topBoundary && mouseY <= bottomBoundary);

	return insideX && insideY;
}

void VoidButton::handleClick() const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY())) {
			if (buttonAction_) {
				buttonAction_();
			}
		}
	}
}

void VoidButton::draw() const {
	drawRectangle(
		viewportArea_.pos,
		viewportArea_.scale,
		0.0f,
		false,
		false,
		color_,
		color_,
		color_,
		color_
	);

	drawText(
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y },
		text_,
		0.0f,
		{ 0.0f, 0.0f, 0.0f }
	);
}