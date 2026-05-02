#ifndef TELEPORTER_HPP
#define TELEPORTER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "DrawFunctions.hpp"
#include "Sprite.hpp"

// Children Game Object Types
#include "UISpriteElement.hpp"

class Teleporter : public CollisionObject2D {
public:
	Teleporter(
		const Transform2D& localTransform,
		const std::string& name,
		const Vector2D& toLocation,
		const Sprite* uiSprite
	);

	void onStart() override;
	void draw() override {}
	void update() override;
	void onDestruction() override {}
	void establishFields() override;

	void onCollision(CollisionObject2D& other);

	const Vector2D& getToLocation() const { return toLocation_; }
	UISpriteElement* getAttachedUIElement();

private:
	Vector2D toLocation_;
	const Sprite* uiSprite_;
};

#endif