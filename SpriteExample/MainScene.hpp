#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

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

#include "Scene.hpp"

class MainScene : public Scene {
	public:
		MainScene();

		~MainScene();

		virtual void init() override;

		// Public only so buffer functions can call them
		virtual void draw() override;

		virtual void update() override;

		virtual void procSpecialKeys(int key, int x, int y) override;
		virtual void procSpecialKeysUp(int key, int x, int y) override;
		virtual void procKeys(unsigned char key, int x, int y) override;
		virtual void procMouse(int button, int state, int x, int y) override;

	private:
		
		// Scene Specific Functions
		void updateCamera();

		// Scene Audio Tracks
		int currentAudioTrack_ = 0;
		const std::vector<std::string> audioTracks_;

		// Inputs
		bool keyLeftPressed_ = false;
		bool keyRightPressed_ = false;
		bool keyUpPressed_ = false;
		bool keyDownPressed_ = false;

		// Toggles
		bool drawAxes_ = true;
		bool screenOn_ = true;
		bool musicOn_ = true;

		// Camera Settings
		float zoomFactor_ = 1.0;
		float camX_ = 0, camY_ = 0, speed_ = 1;

		// Player Variables
		PositionXY playerPos_ = { 0, 0 };
		float moveX_ = 0, moveY_ = 0;
		bool movePressed_ = false;
		bool mirrorPlayer_ = false;

		// Variables for demo purposes
		ColorRGB squareColor1_ = { 1, 0, 0 };
		ColorRGB squareColor2_ = { 1, 0.8, 0.2 };
		ColorRGB triangleColor1_ = { 0.0, 1, 0.0 };
		ColorRGB triangleColor2_ = { 0.2, 1, 0.8 };
		float squareRotation_ = 0;
		float triangleRotation_ = 0;

		// Keys for registries
		std::string billsRunningSheetName_;
		std::string brownsRunningSheetName_;

		std::string billsSpriteName_;
		std::string brownsSpriteName_;

		// File Paths
		const std::string runningTilesBrownsFilepath_;
		const std::string runningTilesBillsFilepath_;
};

#endif