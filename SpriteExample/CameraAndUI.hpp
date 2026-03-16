#ifndef CAMERA_AND_UI_HPP
#define CAMERA_AND_UI_HPP

#include <string>

#include "GameObject2D.hpp"

#include "Game.hpp"
#include "DrawFunctions.hpp"

class CameraAndUI : public GameObject2D {
	public:
		CameraAndUI(Transform2D transform2D);

		void onStart() override;
		void draw() override {}
		void update() override;
		void onDestruction() override {}

	private:
};

#endif