#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

#include "MoneserType.hpp"

// Children Game Object Types
#include "Axis.hpp"
#include "Camera.hpp"
#include "NonColliderSprite.hpp"
#include "Teleporter.hpp"

class Player : public CollisionObject2D {
	public:
		Player(
			const Transform2D& localTransform,
			const std::string& name,
			const float& power,
			const SpriteSheet* sheetDown,
			const SpriteSheet* sheetSideways,
			const SpriteSheet* sheetUp
		);

		void onStart() override;
		void draw() override;
		void update() override;
		void onDestruction() override;
		void establishFields() override;

		void onCollision(CollisionObject2D& other) override;

		float getHealth() const { return health_; }
		void setHealth(const float& health) { health_ = health; }

		float getPower() const { return power_; }
		void setPower(const float& power) { power_ = power; }

		MoneserType getCurrentType() const { if (partyIndex_ != -1) { return moves_[partyIndex_]; } return MoneserType::Null; }

	private:
		const SpriteSheet* sheetSideways_;
		const SpriteSheet* sheetUp_;
		const SpriteSheet* sheetDown_;

		float speed_;
		Vector2D frameMovement_;
		bool moving_;
		char direction_;
		Camera* getAttachedCamera();

		bool teleportedAlready_;

		float health_;
		float power_;
		std::vector<MoneserType> moves_;
		int partyIndex_;
};

#endif