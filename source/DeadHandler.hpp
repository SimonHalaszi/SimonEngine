#ifndef DEAD_HANDLER_HPP
#define DEAD_HANDLER_HPP

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "InputManager.hpp"
#include "SceneFactory.hpp"

class DeadHandler : public GameObject2D {
public:
	DeadHandler() {}

	void onStart() override {}
	void draw() override {}
	void update() override;
	void onDestruction() override {}
};

#endif
