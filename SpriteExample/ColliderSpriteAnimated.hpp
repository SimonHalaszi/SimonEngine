#ifndef COLLIDER_SPRITE_ANIMATED_HPP
#define COLLIDER_SPRITE_ANIMATED_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "DrawFunctions.hpp"

class ColliderSpriteAnimated : public CollisionObject2D {
public:
	ColliderSpriteAnimated(
		const Transform2D& localTransform,
		const std::string& name,
		const std::string& tag,
		const SpriteSheet* spriteSheet
	);

	void onStart() override {}
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void establishFields() override {}

	void onCollision(CollisionObject2D& other) override {}

private:
	const SpriteSheet* spriteSheet_;
};

#endif