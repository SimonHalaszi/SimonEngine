#ifndef NON_COLLIDER_SPRITE_ANIMATED_HPP
#define NON_COLLIDER_SPRITE_ANIMATED_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "DrawFunctions.hpp"

class NonColliderSpriteAnimated : public GameObject2D {
public:
	NonColliderSpriteAnimated(
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

private:
	const SpriteSheet* spriteSheet_;
};

#endif