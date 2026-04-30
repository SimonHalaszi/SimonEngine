#ifndef MONESER_HPP
#define MONESER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "DrawFunctions.hpp"

#include "MoneserType.hpp"

// Children Game Object Types
#include "NonColliderSprite.hpp"
#include "MoneserArea.hpp"

class Moneser : public CollisionObject2D {
public:
	Moneser(
		const Transform2D& localTransform,
		const std::string& name,
		const float& power,
		const MoneserType& type,
		const SpriteSheet* spriteSheet,
		const Sprite* uiSpriteFight,
		const Sprite* uiSpriteTake
	);

	void onStart() override;
	void draw() override;
	void update() override {}
	void onDestruction() override {}
	void establishFields() override;

	void onCollision(CollisionObject2D& other) override {}

	float getHealth() const { return health_; }
	void setHealth(const float& health) { health_ = health; }

	float getPower() const { return power_; }
	void setPower(const float& power) { power_ = power; }

	MoneserType getType() const { return type_; }
	void setType(const MoneserType& type) { type_ = type; }

	void handleMove(class Player* player);

private:
	const SpriteSheet* spriteSheet_;
	const Sprite* uiSpriteFight_;
	const Sprite* uiSpriteTake_;
	
	float health_;
	float power_;
	MoneserType type_;
};

#endif