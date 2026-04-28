#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include "GameObject2D.hpp"
#include "Game.hpp"

// Simple camera GameObject
class Camera : public GameObject2D {
	public:
		Camera(const Transform2D& localTransform);

		void onStart() override {}
		void draw() override {}
		void update() override;
		void onDestruction() override {}
};

#endif