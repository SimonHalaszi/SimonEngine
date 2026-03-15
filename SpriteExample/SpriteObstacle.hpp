#ifndef SPRITE_OBSTACLE_HPP
#define SPRITE_OBSTACLE_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"
#include "ColliderRectangle.hpp"

class SpriteObstacle : public CollisionObject2D {
public:
	SpriteObstacle(Transform2D transform2D, std::string spriteKey = "");

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override {}

private:
	const Sprite* sprite_;
	std::string spriteName_;
};

#endif