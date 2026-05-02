#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <string>

#include "UISpriteElement.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class HealthBar : public UISpriteElement {
public:
	HealthBar(
		const Transform2D& localTransform,
		const std::string& name,
		const Sprite* healthBar,
		const float& health
	);

	void onStart() override {}
	void update() override;
	void onDestruction() override {}
	void establishFields() override {}

private:
	const float& health_;
};

#endif
