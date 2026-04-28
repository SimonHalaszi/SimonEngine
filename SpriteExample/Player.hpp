#ifndef SPRITE_GAME_OBJECT_HPP
#define SPRITE_GAME_OBJECT_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

// Children Game Object Types
#include "Axis.hpp"
#include "Camera.hpp"

class Player : public CollisionObject2D {
public:
	Player(
		const Transform2D& localTransform,
		const std::string& name,
		const std::string& tag,
		const Sprite* sprite
	);

	void onStart() override;
	void draw() override;
	void update() override;
	void onDestruction() override {}
	void establishFields() override;

	void onCollision(CollisionObject2D& other) override;

private:
	const Sprite* sprite_;

	float speed_;
};

#endif