#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
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

		virtual void init() override final;

		virtual void draw() override final;

		virtual void update() override final;

		virtual void procSpecialKeys(int key, int x, int y) override final;
		virtual void procSpecialKeysUp(int key, int x, int y) override final;
		virtual void procKeys(unsigned char key, int x, int y) override final;
		virtual void procMouse(int button, int state, int x, int y) override final;

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
		float zoomFactor_ = 1.0f;
		float camX_ = 0.0f, camY_ = 0.0f, speed_ = 1.0f;

		// Player Variables
		PositionXY playerPos_ = { 0.0f, 0.0f };
		float moveX_ = 0.0f, moveY_ = 0.0f;
		bool movePressed_ = false;
		bool mirrorPlayer_ = false;

		// Variables for demo purposes
		ColorRGB squareColor1_ = { 1.0f, 0.0f, 0.0f };
		ColorRGB squareColor2_ = { 1.0f, 0.8f, 0.2f };
		ColorRGB triangleColor1_ = { 0.0f, 1.0f, 0.0f };
		ColorRGB triangleColor2_ = { 0.2f, 1.0f, 0.8f };
		float squareRotation_ = 0.0f;
		float triangleRotation_ = 0.0f;

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