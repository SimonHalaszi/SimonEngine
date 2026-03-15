#include "SpriteObstacle.hpp"

SpriteObstacle::SpriteObstacle(Transform2D transform2D, std::string spriteName) {
	localTransform_ = transform2D;
	spriteName_ = spriteName;
	sprite_ = nullptr;
	tag_ = "Obstacle";
}

void SpriteObstacle::onStart() {
	sprite_ = &(SpriteRegistry::getInstance().getSprite(spriteName_));

	// Fixed thickness in world space
	float halfThickness = 0.005f;

	// Convert fixed world-space thickness to local space ratios
	float thicknessRatioX = halfThickness / localTransform_.scale.x;
	float thicknessRatioY = halfThickness / localTransform_.scale.y;

	// Fixed inset distances for walls and vertical coverage
	float wallInsetFromEdge = 0.05f;  // How far walls are inset from top/bottom edges
	float ceilingFloorInsetFromEdge = 0.05f;  // How far ceiling/floor are inset from left/right edges

	// Convert fixed insets to local space ratios
	float wallInsetRatio = wallInsetFromEdge / localTransform_.scale.y;
	float ceilingFloorInsetRatio = ceilingFloorInsetFromEdge / localTransform_.scale.x;

	attachChild(std::make_unique<ColliderRectangle>(
		Transform2D{
			{0.0f, -(1.0f - thicknessRatioY)},
			{1.0f - ceilingFloorInsetRatio, thicknessRatioY},
			0.0f,
			false,
			false
		},
		"Ceiling"
	)
	);
	attachChild(std::make_unique<ColliderRectangle>(
		Transform2D{
			{0.0f, 1.0f - thicknessRatioY},
			{1.0f - ceilingFloorInsetRatio, thicknessRatioY},
			0.0f,
			false,
			false
		},
		"Floor"
	)
	);
	attachChild(std::make_unique<ColliderRectangle>(
		Transform2D{
			{-(1.0f - thicknessRatioX), 0.0f},
			{thicknessRatioX, 1.0f - wallInsetRatio},
			0.0f,
			false,
			false
		},
		"RightWall"
	)
	);
	attachChild(std::make_unique<ColliderRectangle>(
		Transform2D{
			{1.0f - thicknessRatioX, 0.0f},
			{thicknessRatioX, 1.0f - wallInsetRatio},
			0.0f,
			false,
			false
		},
		"LeftWall"
	)
	);
}

void SpriteObstacle::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*sprite_
	);
}