#include "Utilities.hpp"

float degreesToRadians(float degrees) {
    return static_cast<float>(degrees * PI) / 180.0f;
}

Transform2D composeTransforms(const Transform2D& left, const Transform2D& right) {
    Transform2D world;

    // Combined scale
    world.scale.x = left.scale.x * right.scale.x;
    world.scale.y = left.scale.y * right.scale.y;

    // Combined reflections
    world.mirror = left.mirror ^ right.mirror;
    world.flip = left.flip ^ right.flip;

    // Odd reflection parity changes handedness, so child rotation direction is inverted.
    const bool parentInvertsRotation = left.mirror ^ left.flip;
    world.rotation = left.rotation + (parentInvertsRotation ? -right.rotation : right.rotation);

    // Start from child's local position
    Vector2D local = right.position;

    if (left.mirror) local.x = -local.x;
    if (left.flip)   local.y = -local.y;

    // Apply parent's scale
    local.x *= left.scale.x;
    local.y *= left.scale.y;

    // Apply parent's rotation
    float rad = degreesToRadians(left.rotation);
    float cosR = cos(rad);
    float sinR = sin(rad);

    Vector2D rotated;
    rotated.x = local.x * cosR - local.y * sinR;
    rotated.y = local.x * sinR + local.y * cosR;

    // Apply parent's translation
    world.position.x = left.position.x + rotated.x;
    world.position.y = left.position.y + rotated.y;

    return world;
}

bool checkAABBCollision(const AABB& a, const AABB& b) {
    return (a.min.x < b.max.x && a.max.x > b.min.x) &&
        (a.min.y < b.max.y && a.max.y > b.min.y);
}

WindowArea viewportAreaToWindowArea(const ViewportArea& viewport, const ViewportContext& context) {
    float adjustedX = viewport.pos.x - context.scrollOffsetX;
    float adjustedY = viewport.pos.y - context.scrollOffsetY;

    float normX = (adjustedX - context.orthoLeft) / (context.orthoRight - context.orthoLeft);
    float normY = (adjustedY - context.orthoBottom) / (context.orthoTop - context.orthoBottom);

    float normW = viewport.scale.x / (context.orthoRight - context.orthoLeft);
    float normH = viewport.scale.y / (context.orthoTop - context.orthoBottom);

    WindowArea window;
    window.pos.x = context.viewportX + normX * context.viewportWidth;
    window.pos.y = context.viewportY + normY * context.viewportHeight;

    window.scale.x = normW * context.viewportWidth;
    window.scale.y = normH * context.viewportHeight;

    return window;
}

bool isInsideViewportContext(int mouseX, int mouseY, const ViewportContext& context) {
    int flippedMouseY = ENGINE_WIN_H - mouseY;

    float left = static_cast<float>(context.viewportX);
    float right = static_cast<float>(context.viewportX + context.viewportWidth);
    float bottom = static_cast<float>(context.viewportY);
    float top = static_cast<float>(context.viewportY + context.viewportHeight);

    return (mouseX >= left && mouseX <= right &&
        flippedMouseY >= bottom && flippedMouseY <= top);
}
