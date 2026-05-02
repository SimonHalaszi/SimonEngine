#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <string>

#include "UISpriteElement.hpp"

#include "InputManager.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"
#include "Game.hpp"

class MainMenu : public UISpriteElement {
	public:
		MainMenu(
			const Transform2D& localTransform,
			const Sprite* main,
			const Sprite* controls,
			const Sprite* howTo
		);

		void onStart() override {}
		void update() override;
		void onDestruction() override {}
		void establishFields() override {}
	private:
			const Sprite* main_;
			const Sprite* controls_;
			const Sprite* howTo_;
};


#endif