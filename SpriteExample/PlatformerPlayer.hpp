#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "SpriteSheetRegistry.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "SoundManager.hpp"

class PlatformerPlayer : public CollisionObject2D {
public:
	PlatformerPlayer(
		std::string playerSpriteSheetFilePath,
		std::string playerSpritesSheetKey
	);

	void onStart() override;
	void draw() override;
	void update() override;
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override;
	void establishFields() override;

	static void addToCoinCount(int i) { coinCount_ += i; }
	static int getCoinCount() { return coinCount_; }

private:

	const SpriteSheet* playerSpriteSheet_;

	std::string jumpingSoundFilepath_;

	bool drawHitbox_ = false;
	bool handleContact = true;
	bool onGround_ = false;
	bool hasGravity_ = true;
	
	float collisionTolerance_ = 0.001f;
	float speed_ = 1.0f;
	float moveX_ = 0.0f, moveY_ = 0.0f;
	float gravitySpeed_ = 1.0f;

	float jumpTime_ = 0.5f;
	int jumpTimeInUpdateFrames_ = 0;
	int jumpFrame_ = 0;
	bool jumping_ = false;
	float jumpSpeed_ = 2.0f;

	float collisionCorrectionX_ = 0.0f;
	float collisionCorrectionY_ = 0.0f;

	static int coinCount_;
};

#endif