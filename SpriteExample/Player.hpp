#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

// Children Game Object Types
#include "Axis.hpp"
#include "Camera.hpp"
#include "NonColliderSprite.hpp"

class Player : public CollisionObject2D {
public:
	Player(
		const Transform2D& localTransform,
		const std::string& name,
		const std::string& tag,
		const SpriteSheet* sheetDown,
		const SpriteSheet* sheetSideways,
		const SpriteSheet* sheetUp
	);

	void onStart() override;
	void draw() override;
	void update() override;
	void onDestruction() override;
	void establishFields() override;

	void onCollision(CollisionObject2D& other) override;

private:
	const SpriteSheet* sheetSideways_;
	const SpriteSheet* sheetUp_;
	const SpriteSheet* sheetDown_;

	float speed_;
	Vector2D frameMovement_;
	bool moving_;
	char direction_;
	Camera* getAttachedCamera();
};

#endif