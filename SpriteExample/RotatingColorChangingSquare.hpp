#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <string>
#include <algorithm>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "DrawFunctions.hpp"
#include "Utilities.hpp"
#include "InputManager.hpp"

class RotatingColorChangingSquare : public GameObject2D {
	public:
		RotatingColorChangingSquare(
			const Transform2D& transform2D,
			const ColorRGB& colorTL,
			const ColorRGB& colorTR,
			const ColorRGB& colorBL,
			const ColorRGB& colorBR,
			const ColorRGB& colorTL2,
			const ColorRGB& colorTR2,
			const ColorRGB& colorBL2,
			const ColorRGB& colorBR2
		);

		void onStart() override {}
		void draw() override;
		void update() override;
		void onDestruction() override {}

	private:
		ColorRGB colorTL_;
		ColorRGB colorTR_;
		ColorRGB colorBL_;
		ColorRGB colorBR_;

		ColorRGB colorTL2_;
		ColorRGB colorTR2_;
		ColorRGB colorBL2_;
		ColorRGB colorBR2_;
};

#endif