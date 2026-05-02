#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "InputManager.hpp"
#include "Game.hpp"

class GameScene : public Scene {
public:
	GameScene();

	~GameScene() {}

	virtual void init() override final;

	virtual void draw() const override final {}

	virtual void update() override final;

};

#endif