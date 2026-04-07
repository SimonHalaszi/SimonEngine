#ifndef COLLIDER_SQUARE_HPP
#define COLLIDER_SQUARE_HPP

#include <string>

#include "CollisionObject2D.hpp"
#include "DrawFunctions.hpp"

class ColliderRectangle : public CollisionObject2D {
public:
	ColliderRectangle(Transform2D transform2D = {}, std::string tag = "") {
		localTransform_ = transform2D;
		tag_ = tag;
	}

	void onStart() override {}
	void draw() override {}
	void update() override {}
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override {}
};

#endif