#include "AssetButton.hpp"

AssetButton::AssetButton() :
	viewportArea_(),
	color_(),
	text_(""),
	previewSprite_(nullptr)
{}

AssetButton::AssetButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& text,
	const Sprite* previewSprite
) :
	viewportArea_(viewportArea),
	color_(color),
	text_(text),
	previewSprite_(previewSprite)
{}

bool AssetButton::isInside(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(viewportArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

std::unique_ptr<GameObject2D> AssetButton::handleClick(const ViewportContext& context) const {
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInside(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			return AssetFactory::getInstance().createGameObject(text_);
		}
	}
	return nullptr;
}

void AssetButton::draw() const {
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

	drawSprite(
		{ viewportArea_.pos.x + 1.0f - (viewportArea_.scale.x / 13.0f), viewportArea_.pos.y},
		{ viewportArea_.scale.x / 13.0f, viewportArea_.scale.y },
		0.0f,
		false,
		false,
		*previewSprite_
	);

	drawText(
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y },
		text_,
		0.0f,
		{ 0.0f, 0.0f, 0.0f }
	);
}