#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include <string>
#include <iostream>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class Coin : public CollisionObject2D {
public:
	Coin(Transform2D transform2D, std::string spriteFilePath, std::string spriteName);

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override;

private:
	const Sprite* sprite_;
};

#endif