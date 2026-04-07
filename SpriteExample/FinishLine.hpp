#ifndef FINISH_LINE_HPP
#define FINISH_LINE_HPP

#include <string>

#include "CollisionObject2D.hpp"

#include "Game.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include "DrawFunctions.hpp"
#include "SoundManager.hpp"

class FinishLine : public CollisionObject2D {
public:
	FinishLine(Transform2D transform2D, std::string spriteFilePath, std::string spriteKey);

	void onStart() override;
	void draw() override;
	void update() override;
	void onDestruction() override;
	void onCollision(CollisionObject2D& other) override;

	static bool isPopupShowing() { return isPopupShowing_; }
	static bool isGameCompleted() { return isGameCompleted_; }

private:
	const Sprite* finishLineSprite_;

	std::string gameWonSoundFilepath_;

	float popupTime_ = 1.5f;
	int popupTimeInUpdateFrames_ = 0;
	int popupFrame_ = 0;
	static bool isPopupShowing_;

	float sceneChangeDelayTime_ = 3.0f;
	int sceneChangeDelayTimeInUpdateFrames_ = 0;
	int sceneChangeDelayFrame_ = 0;
	static bool isGameCompleted_;
};

#endif
