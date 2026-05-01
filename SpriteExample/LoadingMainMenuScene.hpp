#pragma once
#ifndef LOADING_MAIN_MENU_SCENE_HPP
#define LOADING_MAIN_MENU_SCENE_HPP

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "InputManager.hpp"
#include "Game.hpp"

class LoadingMainMenuScene : public Scene {
	public:
		LoadingMainMenuScene();

		~LoadingMainMenuScene() {}

		virtual void init() override final;

		virtual void draw() const override final {}

		virtual void update() override final {}
};

#endif