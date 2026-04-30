#ifndef MONESER_AREA_HPP
#define MONESER_AREA_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"

// Children Game Object Types
#include "UISpriteElement.hpp"

class MoneserArea : public CollisionObject2D {
	public:
		MoneserArea(
			const Transform2D& localTransform,
			const std::string& name,
			const std::string& tag,
			const Sprite* uiSpriteFight,
			const Sprite* uiSpriteTake
		);

		void onStart() override;
		void draw() override {}
		void update() override;
		void onDestruction() override {}
		void establishFields() override {}

		void onCollision(CollisionObject2D& other) override;

	private:
		UISpriteElement* getAttachedUIElement();
		const Sprite* uiSpriteFight_;
		const Sprite* uiSpriteTake_;
};

#endif