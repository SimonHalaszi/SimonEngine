#include "Utilities.hpp"

float degreesToRadians(float degrees) {
    return degrees * PI / 180.0;
}

Transform2D composeTransforms(const Transform2D& left, const Transform2D& right) {
    Transform2D world;

    // Combined scale
    world.scale.x = left.scale.x * right.scale.x;
    world.scale.y = left.scale.y * right.scale.y;

    // Combined rotation
    world.rotation = left.rotation + right.rotation;

    // Combined reflections
    world.mirror = left.mirror ^ right.mirror;
    world.flip = left.flip ^ right.flip;

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