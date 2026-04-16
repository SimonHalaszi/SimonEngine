#include "IFieldButton.hpp"
#include <string>
#include <cctype>

IFieldButton::IFieldButton() :
	viewportArea_({0.0f, 0.0f, 0.0f, 0.0f}),
	color_({ 0.0f, 0.0f, 0.0f }),
	name_("")
{}

BoolIFieldButton::BoolIFieldButton(
	ViewportArea viewportArea,
	ColorRGB color,
	const std::string& name,
	BoolField* field
) {
	viewportArea_ = viewportArea;
	color_ = color;
	name_ = name;
	field_ = field;

	constexpr float LH = 1.0f / 16.0f;
	buttonArea_.pos = { 0.75f, viewportArea.pos.y };
	buttonArea_.scale = { 0.25f, LH };
}

BoolIFieldButton::BoolIFieldButton()
	: field_(nullptr)
{}

void BoolIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left	
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
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	// Draw to button area a black rectangle and T or F based on bool value in white text
	drawRectangle(
		buttonArea_.pos,
		buttonArea_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	std::string text = "F";
	if (field_->getValue()) {
		text = "T";
	}
	drawText(
		{ buttonArea_.pos.x, buttonArea_.pos.y },
		text,
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
}

bool BoolIFieldButton::handleClick(const ViewportContext& context) {
	// if inside buttonArea_ -> field->setValue(!field->getValue);
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(!field_->getValue());
			return true;
		}
	}
	return false;
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
	clickedTextEntryArea_ = false;
}

TextEntryIFieldButton::TextEntryIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& name
) {
	viewportArea_ = viewportArea;
	color_ = color;
	name_ = name;
	clickedTextEntryArea_ = false;

	float layerHeight = 1.0f / 16.0f;
	// Layer 1
	float valueRowY = viewportArea.pos.y - layerHeight;
	// Text entry: left 3/4 of the row
	textEntryArea_.pos = { -0.25f, valueRowY };
	textEntryArea_.scale = { 0.75f, layerHeight };
	// Set button: right 1/4 of the row
	buttonArea_.pos = { 0.75f, valueRowY };
	buttonArea_.scale = { 0.25f, layerHeight };
}

void TextEntryIFieldButton::appendToBuffer(std::string newCharacters) {
	entryBuffer_ += newCharacters;
}

void TextEntryIFieldButton::handleKeyPress(unsigned char key) {
	if (clickedTextEntryArea_) {
		if (key == '\b' && !entryBuffer_.empty()) {
			entryBuffer_.pop_back();
		}
		else if (std::isprint(static_cast<unsigned char>(key))) {
			entryBuffer_ += static_cast<char>(key);
		}
	}
}

void TextEntryIFieldButton::handleKeyInput(const std::string& typedChars) {
	for (unsigned char c : typedChars) {
		handleKeyPress(c);
	}
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

IntIFieldButton::IntIFieldButton()
	: field_(nullptr)
{}

IntIFieldButton::IntIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& name,
	IntField* field
) : TextEntryIFieldButton(viewportArea, color, name), field_(field)
{
	entryBuffer_ = std::to_string(field_->getValue());
}

void IntIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	// Draw to button area a black rectangle and the word "set"
	drawRectangle(
		buttonArea_.pos,
		buttonArea_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ buttonArea_.pos.x, buttonArea_.pos.y },
		"set",
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
	// Draw to button area a dark grey rectangle and entryBuffer_
	drawRectangle(
		textEntryArea_.pos,
		textEntryArea_.scale,
		0.0f,
		false,
		false,
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f }
	);
	drawText(
		{ textEntryArea_.pos.x - textEntryArea_.scale.x, textEntryArea_.pos.y },
		entryBuffer_,
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
}

bool IntIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_int(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(std::stoi(entryBuffer_));
			entryBuffer_ = std::to_string(field_->getValue());
			clickedTextEntryArea_ = false;
			return true;
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
			return false;
		}
		else {
			clickedTextEntryArea_ = false;
			return false;
		}
	}
	return false;
}

CharIFieldButton::CharIFieldButton()
	: field_(nullptr)
{}

CharIFieldButton::CharIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& name,
	CharField* field
) : TextEntryIFieldButton(viewportArea, color, name), field_(field)
{
	entryBuffer_ = std::string(1, field_->getValue());
}

void CharIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	// Draw to button area a black rectangle and the word "set"
	drawRectangle(
		buttonArea_.pos,
		buttonArea_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ buttonArea_.pos.x, buttonArea_.pos.y },
		"set",
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
	// Draw to button area a dark grey rectangle and entryBuffer_
	drawRectangle(
		textEntryArea_.pos,
		textEntryArea_.scale,
		0.0f,
		false,
		false,
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f }
	);
	drawText(
		{ textEntryArea_.pos.x - textEntryArea_.scale.x, textEntryArea_.pos.y },
		entryBuffer_,
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
}

bool CharIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(entryBuffer_[0]) // Will probably go with that
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(entryBuffer_[0]);
			entryBuffer_ = std::to_string(field_->getValue());
			clickedTextEntryArea_ = false;
			return true;
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
			return false;
		}
		else {
			clickedTextEntryArea_ = false;
			return false;
		}
	}
	return false;
}

FloatIFieldButton::FloatIFieldButton()
	: field_(nullptr)
{}

FloatIFieldButton::FloatIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string name,
	FloatField* field
) : TextEntryIFieldButton(viewportArea, color, name), field_(field)
{
	entryBuffer_ = std::to_string(field_->getValue());
}

void FloatIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	// Draw to button area a black rectangle and the word "set"
	drawRectangle(
		buttonArea_.pos,
		buttonArea_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ buttonArea_.pos.x, buttonArea_.pos.y },
		"set",
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
	// Draw to button area a dark grey rectangle and entryBuffer_
	drawRectangle(
		textEntryArea_.pos,
		textEntryArea_.scale,
		0.0f,
		false,
		false,
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f }
	);
	drawText(
		{ textEntryArea_.pos.x - textEntryArea_.scale.x, textEntryArea_.pos.y },
		entryBuffer_,
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
}

bool FloatIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_float(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(std::stof(entryBuffer_));
			entryBuffer_ = std::to_string(field_->getValue());
			clickedTextEntryArea_ = false;
			return true;
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
			return false;
		}
		else {
			clickedTextEntryArea_ = false;
			return false;
		}
	}
	return false;
}

StringIFieldButton::StringIFieldButton()
	: field_(nullptr)
{}

StringIFieldButton::StringIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& name,
	StringField* field
) : TextEntryIFieldButton(viewportArea, color, name), field_(field)
{
	entryBuffer_ = field_->getValue();
}

void StringIFieldButton::draw() const {
	// Draw to entire viewport area a color rectangle and name in top left
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	// Draw to button area a black rectangle and the word "set"
	drawRectangle(
		buttonArea_.pos,
		buttonArea_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ buttonArea_.pos.x, buttonArea_.pos.y },
		"set",
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
	// Draw to button area a dark grey rectangle and entryBuffer_
	drawRectangle(
		textEntryArea_.pos,
		textEntryArea_.scale,
		0.0f,
		false,
		false,
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f },
		{ 0.20f, 0.20f, 0.20f }
	);
	drawText(
		{ textEntryArea_.pos.x - textEntryArea_.scale.x, textEntryArea_.pos.y },
		entryBuffer_,
		0,
		{ 1.0f, 1.0f, 1.0f }
	);
}

bool StringIFieldButton::handleClick(const ViewportContext& context) {
	// Handle click
	// if inside buttonArea_ -> field->setValue((entryBuffer_)
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
		if (isInsideButton(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			field_->setValue(entryBuffer_);
			entryBuffer_ = field_->getValue();
			clickedTextEntryArea_ = false;
			return true;
		}
		else if (isInsideTextEntry(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), context)) {
			clickedTextEntryArea_ = true;
			return false;
		}
		else {
			clickedTextEntryArea_ = false;
			return false;
		}
	}
	return false;
}

Vector2DIFieldButton::Vector2DIFieldButton() {
}

Vector2DIFieldButton::Vector2DIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string name,
	Vector2DField* field
) {
	viewportArea_ = viewportArea;
	color_ = color;
	name_ = name;

	float layerHeight = 1.0f / 16.0f;
	float topY = viewportArea.pos.y + viewportArea.scale.y;
	float cursor = topY - 2.0f * layerHeight;

	ColorRGB subColor = color_;
	subColor.red -= 0.2f;
	subColor.green -= 0.2f;
	subColor.blue -= 0.2f;

	// X FloatIFieldButton: 2 layers
	float subFieldHalfHeight = 2.0f * layerHeight;
	ViewportArea xArea = { { 0.0f, cursor - subFieldHalfHeight }, { 1.0f, subFieldHalfHeight } };
	x_ = FloatIFieldButton(xArea, subColor, "    x", &field->getXField());
	cursor -= 2.0f * subFieldHalfHeight;

	// Y FloatIFieldButton: 2 layers
	ViewportArea yArea = { { 0.0f, cursor - subFieldHalfHeight }, { 1.0f, subFieldHalfHeight } };
	y_ = FloatIFieldButton(yArea, subColor, "    y", &field->getYField());
}

bool Vector2DIFieldButton::handleClick(const ViewportContext& context) {
	bool x, y;
	
	x = x_.handleClick(context);
	y = y_.handleClick(context);

	return x || y;
}

void Vector2DIFieldButton::handleKeyInput(const std::string& typedChars) {
	x_.handleKeyInput(typedChars);
	y_.handleKeyInput(typedChars);
}

void Vector2DIFieldButton::draw() const {
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	x_.draw();
	y_.draw();
}

Transform2DIFieldButton::Transform2DIFieldButton() {
}

Transform2DIFieldButton::Transform2DIFieldButton(
	const ViewportArea& viewportArea,
	const ColorRGB& color,
	const std::string& name,
	Transform2DField* field
) {
	viewportArea_ = viewportArea;
	color_ = color;
	name_ = name;

	float layerHeight = 1.0f / 16.0f;
	float topY = viewportArea.pos.y + viewportArea.scale.y;
	float cursor = topY - 2.0f * layerHeight; // skip layer 0 (name label)


	ColorRGB subColor = color_;
	subColor.red -= 0.2f;
	subColor.green -= 0.2f;
	subColor.blue -= 0.2f;

	// Position Vector2D: 5 layers
	float vec2HalfHeight = 5.0f * layerHeight;
	ViewportArea posArea = { { 0.0f, cursor - vec2HalfHeight }, { 1.0f, vec2HalfHeight } };
	pos_ = Vector2DIFieldButton(posArea, subColor, "    pos", &field->getPosField());
	cursor -= 2.0f * vec2HalfHeight;

	// Scale Vector2D: 5 layers
	ViewportArea scaleArea = { { 0.0f, cursor - vec2HalfHeight }, { 1.0f, vec2HalfHeight } };
	scale_ = Vector2DIFieldButton(scaleArea, subColor, "    scale", &field->getScaleField());
	cursor -= 2.0f * vec2HalfHeight;

	// Rotation Float: 2 layers
	float floatHalfHeight = 2.0f * layerHeight;
	ViewportArea rotArea = { { 0.0f, cursor - floatHalfHeight }, { 1.0f, floatHalfHeight } };
	rotation_ = FloatIFieldButton(rotArea, subColor, "    rotation", &field->getRotationField());
	cursor -= 2.0f * floatHalfHeight;

	// Mirror Bool: 1 layer
	float boolHalfHeight = layerHeight;
	ViewportArea mirrorArea = { { 0.0f, cursor - boolHalfHeight }, { 1.0f, boolHalfHeight } };
	mirror_ = BoolIFieldButton(mirrorArea, subColor, "    mirror", &field->getMirrorField());
	cursor -= 2.0f * boolHalfHeight;

	// Flip Bool: 1 layer
	ViewportArea flipArea = { { 0.0f, cursor - boolHalfHeight }, { 1.0f, boolHalfHeight } };
	flip_ = BoolIFieldButton(flipArea, subColor, "    flip", &field->getFlipField());
}

bool Transform2DIFieldButton::handleClick(const ViewportContext& context) {
	bool pos, scale, rotation, mirror, flip;
	
	pos = pos_.handleClick(context);
	scale = scale_.handleClick(context);
	rotation = rotation_.handleClick(context);
	mirror = mirror_.handleClick(context);
	flip = flip_.handleClick(context);

	return pos || scale || rotation || mirror || flip;
}

void Transform2DIFieldButton::handleKeyInput(const std::string& typedChars) {
	pos_.handleKeyInput(typedChars);
	scale_.handleKeyInput(typedChars);
	rotation_.handleKeyInput(typedChars);
}

void Transform2DIFieldButton::draw() const {
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
		{ viewportArea_.pos.x - viewportArea_.scale.x, viewportArea_.pos.y + viewportArea_.scale.y - (1.0f / 16.0f) },
		name_,
		0,
		{ 0.0f, 0.0f, 0.0f }
	);
	pos_.draw();
	scale_.draw();
	rotation_.draw();
	mirror_.draw();
	flip_.draw();
}