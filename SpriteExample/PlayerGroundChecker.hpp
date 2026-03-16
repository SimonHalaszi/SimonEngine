#ifndef PLAYER_GROUND_CHECKER_HPP
#define PLAYER_GROUND_CHECKER_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "drawFunctions.hpp"

class PlayerGroundChecker : public CollisionObject2D {
public:
	PlayerGroundChecker(Transform2D transform2D);

	void onStart() override {}
	void draw() override;
	void update() override;
	void onDestruction() override {}
	void onCollision(CollisionObject2D& other) override;

	static bool getGroundStatus() { return onGround_; }

private:
	static bool onGround_;
	bool draw_ = false;
};

#endif
