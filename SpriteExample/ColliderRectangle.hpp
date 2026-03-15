#ifndef COLLIDER_SQUARE_HPP
#define COLLIDER_SQUARE_HPP

#include <string>

#include "CollisionObject2D.hpp"
#include "drawFunctions.hpp"

class ColliderRectangle : public CollisionObject2D {
public:
	ColliderRectangle(Transform2D transform2D = {}, std::string tag = "") {
		localTransform_ = transform2D;
		tag_ = tag;
	}

	void onStart() override {}
	void draw() override {
		Transform2D transform = getWorldTransform();

		drawRectangle(
			transform.position,
			transform.scale, transform.rotation,
			transform.mirror, transform.flip,
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f },
			ColorRGB{ 0.0f, 1.0f, 0.0f }
		);
	}
	void update() override {}
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override {}
};

#endif