#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "SpriteSheetRegistry.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"

class AnimatedSprite : public GameObject2D {
public:
	AnimatedSprite(Transform2D transform2D, std::string spriteSheetName = "");

	void onStart() override;
	void draw() override;
	void update() override;
	void onDestruction() override {}

private:
	const SpriteSheet* spriteSheet_;
	std::string spriteSheetName_;

	int frame_;
};

#endif