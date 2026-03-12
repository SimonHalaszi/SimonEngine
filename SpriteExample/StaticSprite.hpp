#ifndef STATIC_SPRITE_HPP
#define STATIC_SPRITE_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"

class StaticSprite : public GameObject2D {
public:
	StaticSprite(Transform2D transform2D, std::string spriteName = "");

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}

private:
	const Sprite* sprite_;
	std::string spriteName_;
};

#endif