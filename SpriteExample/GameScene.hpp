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

	// Keys for assets
	std::string playerSpriteKey_;
};

#endif