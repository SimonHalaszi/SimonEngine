#include "UITextElement.hpp"

UITextElement::UITextElement(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor) {
	localTransform_ = transform2D;
	tag_ = "UITextElement";
	text_ = text;
	textColor_ = textColor;
	rectangleColor_ = rectangleColor;
}

void UITextElement::draw() {
	if (!drawElement_) {
		return;
	}

	// These are NOT relative to WorldSpace but ScreenSpace
	glPushMatrix();
	glLoadIdentity();

	drawRectangle(
		localTransform_.position,
		localTransform_.scale,
		localTransform_.rotation,
		localTransform_.mirror,
		localTransform_.flip,
		rectangleColor_,
		rectangleColor_,
		rectangleColor_,
		rectangleColor_
	);

	int textWidthPixels = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text_.c_str());
	int textHeightPixels = 18;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int viewportWidth = viewport[2];
	int viewportHeight = viewport[3];
	float textWidthNormalized = (float)textWidthPixels / (float)viewportWidth;
	float textHeightNormalized = (float)textHeightPixels / (float)viewportHeight;
	Vector2D centeredTextPos = localTransform_.position;
	centeredTextPos.x -= textWidthNormalized;
	centeredTextPos.y -= textHeightNormalized * 0.5f;

	drawText(
		centeredTextPos,
		text_,
		0.1f,
		textColor_
	);

	glPopMatrix();
}