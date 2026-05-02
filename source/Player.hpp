#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

#include "MoneserType.hpp"

// Children Game Object Types
#include "Axis.hpp"
#include "Camera.hpp"
#include "NonColliderSprite.hpp"
#include "Teleporter.hpp"
#include "DeadHandler.hpp"
#include "HealthBar.hpp"

class Player : public CollisionObject2D {
	public:
		Player(
			const Transform2D& localTransform,
			const std::string& name,
			const float& power,
			const SpriteSheet* sheetDown,
			const SpriteSheet* sheetSideways,
			const SpriteSheet* sheetUp,
			const Sprite* normIcon,
			const Sprite* grassIcon,
			const Sprite* fireIcon,
			const Sprite* waterIcon,
			const Sprite* healDisplay,
			const Sprite* goToMenuDisplay,
			const Sprite* healthDisplay,
			const Sprite* healthBar
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

		MoneserType getCurrentType() const { if (moveIndex_ != -1) { return moves_[moveIndex_]; } return MoneserType::Null; }

	private:
		Camera* getAttachedCamera();
		UISpriteElement* getAttachedUIElement(const std::string& name);
		void updateIconDisplay();
		bool hasType(const MoneserType& type);

		// Sprite Sheets
		const SpriteSheet* sheetSideways_;
		const SpriteSheet* sheetUp_;
		const SpriteSheet* sheetDown_;

		// Type Icons
		const Sprite* normIcon_;
		const Sprite* grassIcon_;
		const Sprite* fireIcon_;
		const Sprite* waterIcon_;

		// Displays
		const Sprite* healDisplay_;
		const Sprite* goToMenuDisplay_;
		const Sprite* healthDisplay_;
		const Sprite* healthBar_;

		// State
		float speed_;
		Vector2D frameMovement_;
		bool moving_;
		char direction_;

		bool teleportedAlready_;

		float health_;
		float power_;
		std::vector<MoneserType> moves_;
		int moveIndex_;
};

#endif