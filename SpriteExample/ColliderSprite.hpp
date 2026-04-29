#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class ColliderSprite : public CollisionObject2D {
public:
	ColliderSprite(
		const Transform2D& localTransform,
		const std::string& name,
		const std::string& tag,
		const Sprite* sprite
	);

	void onStart() override {}
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void establishFields() override {}

	void onCollision(CollisionObject2D& other) override {}

private:
	const Sprite* sprite_;
};

#endif