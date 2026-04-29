#ifndef MONESER_HPP
#define MONESER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "DrawFunctions.hpp"

// Children Game Object Types
#include "NonColliderSprite.hpp"

class Moneser : public CollisionObject2D {
public:
	Moneser(
		const Transform2D& localTransform,
		const std::string& name,
		const SpriteSheet* spriteSheet
	);

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void establishFields() override {}

	void onCollision(CollisionObject2D& other) override {}

private:
	const SpriteSheet* spriteSheet_;
};

#endif