#pragma once
#ifndef LOADING_GAME_SCENE_HPP
#define LOADING_GAME_SCENE_HPP

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "InputManager.hpp"
#include "Game.hpp"

class LoadingGameScene : public Scene {
public:
	LoadingGameScene();

	~LoadingGameScene() {}

	virtual void init() override final;

	virtual void draw() const override final {}

	virtual void update() override final;

};

#endif