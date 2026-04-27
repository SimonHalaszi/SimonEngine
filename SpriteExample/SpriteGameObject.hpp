#ifndef SPRITE_GAME_OBJECT_HPP
#define SPRITE_GAME_OBJECT_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class SpriteGameObject : public GameObject2D {
public:
	SpriteGameObject(
		const Transform2D& transform2D,
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