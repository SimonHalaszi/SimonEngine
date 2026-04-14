#include "IFieldButton.hpp"

IFieldButton::IFieldButton() :
	viewportArea_({0.0f, 0.0f, 0.0f, 0.0f}),
	color_({ 0.0f, 0.0f, 0.0f }),
	name_("")
{}

BoolIFieldButton::BoolIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	BoolField* field
) {

}

BoolIFieldButton::BoolIFieldButton() {

}

void BoolIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
	// Draw to button area a black rectangle and T or F based on bool value in white text
}

void BoolIFieldButton::handleClick(const ViewportContext& context) {
	// if inside buttonArea_ -> field->setValue(!field->getValue);
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(!field_->getValue());
		}
	}
}

bool BoolIFieldButton::isInsideButton(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(buttonArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

TextEntryIFieldButton::TextEntryIFieldButton() {	
	viewportArea_ = { 0.0f, 0.0f, 0.0f, 0.0f };
	color_ = { 0.0f, 0.0f, 0.0f };
	name_ = "";
}

void TextEntryIFieldButton::appendToBuffer(std::string newCharacters) {
	// InputManager will get a functionality to get a buffer of characters, add it to entryBuffer_ here
}

bool TextEntryIFieldButton::isInsideTextEntry(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(textEntryArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

bool TextEntryIFieldButton::isInsideButton(int mouseX, int mouseY, const ViewportContext& context) const {
	WindowArea windowArea = viewportAreaToWindowArea(buttonArea_, context);

	float left = windowArea.pos.x - windowArea.scale.x;
	float right = windowArea.pos.x + windowArea.scale.x;
	float bottom = windowArea.pos.y - windowArea.scale.y;
	float top = windowArea.pos.y + windowArea.scale.y;

	int flippedMouseY = ENGINE_WIN_H - mouseY;

	return (mouseX >= left && mouseX <= right &&
		flippedMouseY >= bottom && flippedMouseY <= top);
}

IntIFieldButton::IntIFieldButton() {

}

IntIFieldButton::IntIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name,
	IntField* field
) {

}

void IntIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
	// Draw to button area a black rectangle and the word "set"
	// Draw to button area a dark grey rectangle and entryBuffer_
}

void IntIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_int(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(std::stoi(entryBuffer_));
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
		}
		else {
			clickedTextEntryArea_ = false;
		}
	}
}

CharIFieldButton::CharIFieldButton() {

}

CharIFieldButton::CharIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name,
	CharField* field
) {

}

void CharIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
	// Draw to button area a black rectangle and the word "set"
	// Draw to button area a dark grey rectangle and entryBuffer_
}

void CharIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(entryBuffer_[0]) // Will probably go with that
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(entryBuffer_[0]);
			entryBuffer_ = field_->getValue();
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
		}
		else {
			clickedTextEntryArea_ = false;
		}
	}
}

FloatIFieldButton::FloatIFieldButton() {

}

FloatIFieldButton::FloatIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name,
	FloatField* field
) {

}

void FloatIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
	// Draw to button area a black rectangle and the word "set"
	// Draw to button area a dark grey rectangle and entryBuffer_
}

void FloatIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_float(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(std::stof(entryBuffer_));
			entryBuffer_ = field_->getValue();
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
		}
		else {
			clickedTextEntryArea_ = false;
		}
	}
}

StringIFieldButton::StringIFieldButton() {

}

StringIFieldButton::StringIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name,
	StringField* field
) {

}

void StringIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
	// Draw to button area a black rectangle and the word "set"
	// Draw to button area a dark grey rectangle and entryBuffer_
}

void StringIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue((entryBuffer_)
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(entryBuffer_);
			entryBuffer_ = field_->getValue();
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
		}
		else {
			clickedTextEntryArea_ = false;
		}
	}
}

Vector2DIFieldButton::Vector2DIFieldButton() {

}

Vector2DIFieldButton::Vector2DIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name
) {

}

void Vector2DIFieldButton::handleClick(const ViewportContext& context) {
	x_.handleClick(context);
	y_.handleClick(context);
}

void Vector2DIFieldButton::draw() const {
	x_.draw();
	y_.draw();
}

Transform2DIFieldButton::Transform2DIFieldButton() {

}

Transform2DIFieldButton::Transform2DIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	std::string name
) {

}

void Transform2DIFieldButton::handleClick(const ViewportContext& context) {
	pos_.handleClick(context);
	scale_.handleClick(context);
	rotation_.handleClick(context);
	mirror_.handleClick(context);
	flip_.handleClick(context);
}

void Transform2DIFieldButton::draw() const {
	pos_.draw();
	scale_.draw();
	rotation_.draw();
	mirror_.draw();
	flip_.draw();
}