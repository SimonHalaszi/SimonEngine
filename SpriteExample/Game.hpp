#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <string>

#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"

// The Game class, with a Singleton the SEXIEST design pattern
class Game {
	public:
		static Game& getInstance() {
			static Game instance;
			return instance;
		}

		void init();
		
		// Public only so buffer functions can call them
		void draw();
		void update(int v);
		void animationTimer(int v);

		void procSpecialKeys(int key, int x, int y);
		void procSpecialKeysUp(int key, int x, int y);
		void procKeys(unsigned char key, int x, int y);
		void procMouse(int button, int state, int x, int y);

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		Game();

		~Game() {}

		void updateCamera();
		void setupInputs();

		// Engine Registries Pointers
		TextureRegistry* textures;
		SpriteRegistry* sprites;
		SpriteSheetRegistry* spriteSheets;
		
		// Sound Engine
		irrklang::ISoundEngine* soundEngine;
		int currentAudioTrack = 0;
		const std::vector<std::string> audioTracks;

		// Update Tick Speeds
		int animationUpdatesPerSecond = 10;
		int physicsUpdatesPerSecond = 244;

		// Inputs
		bool keyLeftPressed = false;
		bool keyRightPressed = false;
		bool keyUpPressed = false;
		bool keyDownPressed = false;

		// Toggles
		bool drawAxes = true;
		bool screenOn = true;
		bool musicOn = true;

		// Camera Settings
		float zoomFactor = 1.0; // Global, if you want. Modified by user input. Initially 1.0
		float camX = 0, camY = 0, speed = 1; // Global for camera movement.

		// Animation Frame Counter
		unsigned int frame = 0;

		// Player Variables
		PositionXY playerPos = { 0, 0 };
		float moveX = 0, moveY = 0;
		bool movePressed = false;
		bool mirrorPlayer = false;

		// Variables for demo purposes
		ColorRGB squareColor1 = { 1, 0, 0 };
		ColorRGB squareColor2 = { 1, 0.8, 0.2 };
		ColorRGB triangleColor1 = { 0.0, 1, 0.0 };
		ColorRGB triangleColor2 = { 0.2, 1, 0.8 };
		float squareRotation = 0;
		float triangleRotation = 0;

		// Keys for registries
		std::string billsRunningSheetName;
		std::string brownsRunningSheetName;

		std::string billsSpriteName;
		std::string brownsSpriteName;
		
		// File Paths
		const std::string runningTilesBrownsFilepath;;
		const std::string runningTilesBillsFilepath;
};

#endif // !GAME_HPP
