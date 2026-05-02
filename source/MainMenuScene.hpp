#ifndef MAIN_MENU_SCENE_HPP
#define MAIN_MENU_SCENE_HPP

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "InputManager.hpp"
#include "Game.hpp"

class MainMenuScene : public Scene {
	public:
		MainMenuScene();

		~MainMenuScene() {}

		virtual void init() override final;

		virtual void draw() const override final {}

		virtual void update() override final {}
};

#endif