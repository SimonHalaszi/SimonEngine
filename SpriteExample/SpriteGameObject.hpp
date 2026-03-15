#ifndef SPRITE_GAME_OBJECT_HPP
#define SPRITE_GAME_OBJECT_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"

class SpriteGameObject : public GameObject2D {
public:
	SpriteGameObject(Transform2D transform2D, std::string spriteKey = "", std::string tag = "");

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}

private:
	const Sprite* sprite_;
	std::string spriteName_;
};

#endif