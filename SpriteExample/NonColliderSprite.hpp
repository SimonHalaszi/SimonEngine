#ifndef NON_COLLIDER_SPRITE_HPP
#define NON_COLLIDER_SPRITE_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class NonColliderSprite : public GameObject2D {
public:
	NonColliderSprite(
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

private:
	const Sprite* sprite_;
};

#endif