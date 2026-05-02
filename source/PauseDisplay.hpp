#ifndef PAUSE_DISPLAY_HPP
#define PAUSE_DISPLAY_HPP

#include <string>

#include "UISpriteElement.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"

class PauseDisplay : public UISpriteElement {
public:
	PauseDisplay(
		const Transform2D& localTransform,
		const std::string& name,
		const Sprite* sprite
	);

	void onStart() override {}
	void update() override;
	void onDestruction() override {}
	void establishFields() override {}
};

#endif
