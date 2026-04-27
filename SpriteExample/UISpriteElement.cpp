#include "UISpriteElement.hpp"

UISpriteElement::UISpriteElement(
    const Transform2D& transform2D,
    const std::string& tag,
    const std::string& name,
    const Sprite* sprite
) {
    localTransform_ = transform2D;
    tag_ = tag;
    name_ = name;
    sprite_ = sprite;
}

void UISpriteElement::draw() {
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

    drawSpriteWithTransform(
        renderTransform,
        *sprite_
    );

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}