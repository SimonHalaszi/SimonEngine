#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>
#include <algorithm>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "DrawFunctions.hpp"
#include "Utilities.hpp"

class RotatingColorChangingTriangle : public GameObject2D {
	public:
		RotatingColorChangingTriangle(
			const Transform2D& transform2D,
			const ColorRGB& colorBL,
			const ColorRGB& colorBR,
			const ColorRGB& colorT,
			const ColorRGB& colorBL2,
			const ColorRGB& colorBR2,
			const ColorRGB& colorT2
		);

		void onStart() override {}
		void draw() override;
		void update() override;
		void onDestruction() override {}

	private:
		ColorRGB colorBL_;
		ColorRGB colorBR_;
		ColorRGB colorT_;

		ColorRGB colorBL2_;
		ColorRGB colorBR2_;
		ColorRGB colorT2_;
};

#endif