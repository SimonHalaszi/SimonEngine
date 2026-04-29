#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

// Needed Other Includes
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <IrrKlang/irrKlang.h>

// Needed C++ Includes
#include <string>
#include <memory>

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "InputManager.hpp"

// Game Objects Used
#include "NonColliderSprite.hpp"
#include "Moneser.hpp"
#include "ColliderSprite.hpp"
#include "Player.hpp"
//

class GameScene : public Scene {
public:
	GameScene();

	~GameScene();

	virtual void init() override final;

	virtual void draw() const override final;

	virtual void update() override final;

private:

	// Scene Specific Stuff Goes Here (Stuff not related to a GameObject)

	// File paths for loading textures
	std::string playerFilePath_;
	std::string baseGrassFilePath_;
	std::string appleTreeFilePath_;
	std::string orangeTreeFilePath_;
	std::string foxireFilePath_;
	std::string foxireSheetFilePath_;
	std::string ploistFilePath_;
	std::string ploistSheetFilePath_;
	std::string grandaFilePath_;
	std::string grandaSheetFilePath_;
	std::string norupFilePath_;
	std::string norupSheetFilePath_;
	std::string shadowFilePath_;

	// Keys for assets
	std::string playerSidewaysKey_;
	std::string playerUpKey_;
	std::string playerDownKey_;
	std::string baseGrassKey_;
	std::string appleTreeKey_;
	std::string orangeTreeKey_;
	std::string foxireKey_;
	std::string foxireSheetKey_;
	std::string ploistKey_;
	std::string ploistSheetKey_;
	std::string grandaKey_;
	std::string grandaSheetKey_;
	std::string norupKey_;
	std::string norupSheetKey_;
	std::string shadowKey_;
};

#endif