#include "SceneButton.hpp"

SceneButton::SceneButton() :
	viewportArea_(),
	color_(),
	text_("")
{}

SceneButton::SceneButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text
) :
	viewportArea_(viewportArea),
	color_(color),
	text_(text)
{}

bool SceneButton::isInside(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(viewportArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

std::unique_ptr<Scene> SceneButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			return SceneFactory::getInstance().createScene(text_);
		}
	}
	return nullptr;
}

void SceneButton::draw() const {
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