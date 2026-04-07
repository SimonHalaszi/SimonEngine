#include "UITextElement.hpp"

UITextElement::UITextElement(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor) {
	localTransform_ = transform2D;
	tag_ = "UITextElement";
	text_ = text;
	textColor_ = textColor;
	rectangleColor_ = rectangleColor;
	name_ = "UITextElement";
}

void UITextElement::draw() {
    if (!drawElement_) {
        return;
    }

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int vw = viewport[2];
    int vh = viewport[3];

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, vw, 0, vh, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float px = (localTransform_.position.x + 1.0f) * 0.5f * vw;
    float py = (localTransform_.position.y + 1.0f) * 0.5f * vh;

    float sx = localTransform_.scale.x * 0.5f * vw;
    float sy = localTransform_.scale.y * 0.5f * vh;

    drawRectangle(
        { px, py },
        { sx, sy }, 
        localTransform_.rotation,
        localTransform_.mirror,
        localTransform_.flip,
        rectangleColor_,
        rectangleColor_,
        rectangleColor_,
        rectangleColor_
    );

    drawTextCentered({ px, py }, text_, 20.0f, textColor_);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}