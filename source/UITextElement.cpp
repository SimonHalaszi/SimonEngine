#include "UITextElement.hpp"

UITextElement::UITextElement(
    const Transform2D& transform2D,
    const std::string& tag,
    const std::string& name,
    const std::string& text,
    const ColorRGB& textColor,
    const ColorRGB& rectangleColorTL,
    const ColorRGB& rectangleColorTR,
    const ColorRGB& rectangleColorBL,
    const ColorRGB& rectangleColorBR
) {
	localTransform_ = transform2D;
    tag_ = tag;
    name_ = name;
	text_ = text;
	textColor_ = textColor;
    rectangleColorTL_ = rectangleColorTL;
    rectangleColorTR_ = rectangleColorTR;
    rectangleColorBL_ = rectangleColorBL;
    rectangleColorBR_ = rectangleColorBR;
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

    Transform2D renderTransform = localTransform_;

    renderTransform.position.x = (localTransform_.position.x + 1.0f) * 0.5f * vw;
    renderTransform.position.y = (localTransform_.position.y + 1.0f) * 0.5f * vh;

    renderTransform.scale.x = localTransform_.scale.x * 0.5f * vw;
    renderTransform.scale.y = localTransform_.scale.y * 0.5f * vh;

    drawRectangleWithTransform(
        renderTransform,
        rectangleColorTL_,
        rectangleColorTR_,
        rectangleColorBL_,
        rectangleColorBR_
    );

    drawTextCentered({ renderTransform.position.x, renderTransform.position.y }, text_, 20.0f, textColor_);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}