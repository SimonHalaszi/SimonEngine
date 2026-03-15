#ifndef ARCHIVE_PLAYER_HPP
#define ARCHIVE_PLAYER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "SpriteSheet.hpp"
#include "SpriteSheetRegistry.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"

#include "Axis.hpp"

class ArchivePlayer : public CollisionObject2D {
	public:
		ArchivePlayer(std::string playerSpritesSheetFilepath = "");

		void onStart() override;
		void draw() override;
		void update() override;
		void onDestruction() override {}
		void onCollision(CollisionObject2D& other) override;

	private:
		const SpriteSheet* playerSpriteSheet_;
		std::string playerSpritesSheetName_;

		bool drawHitbox_ = false;
		
		float speed_ = 1.0f;
		float moveX_ = 0.0f, moveY_ = 0.0f;
};

#endif