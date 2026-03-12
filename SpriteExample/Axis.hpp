#ifndef AXIS_HPP
#define AXIS_HPP

#include <iostream>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "DrawFunctions.hpp"
#include "Utilities.hpp"
#include "InputManager.hpp"

class Axis : public GameObject2D {
public:
	Axis(Transform2D transform2D, ColorRGB color1, ColorRGB color2, bool willDrawAxis, char axis);

	void onStart() override {}
	void draw() override;
	void update() override;
	void onDestruction() override {}

private:
	ColorRGB color1_;
	ColorRGB color2_;
	bool willDrawAxis_;
	char axis_;
};

#endif
