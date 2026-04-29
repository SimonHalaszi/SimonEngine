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

	void loadMisc();
	void createBaseArea();
	void createMarshArea();
	void createFireArea();
	void createGrassArea();
	void createHouseArea();
	void createBackdrop();

	void spawnMonesers();
	void spawnPlayer();

private:

	// Scene Specific Stuff Goes Here (Stuff not related to a GameObject)
	Vector2D houseOrgin_;
};

#endif