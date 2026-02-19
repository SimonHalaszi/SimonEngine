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

#include "Scene.hpp"
#include "MainScene.hpp"

// Game Class

// The Game class, with a Singleton the SEXIEST design pattern
class Game {
	public:
		static Game& getInstance() {
			static Game instance;
			return instance;
		}

		void init();
		
		Scene* getCurrentScene() { return currentScene_; }

		// Public only so buffer functions can call them
		
		void frameTimer(int v);

		void updateTimer(int v);

		void animationTimer(int v);

		void changeScene(Scene* newScene) { delete currentScene_; currentScene_ = newScene; currentScene_->init(); }

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		Game() {
			currentScene_ = new MainScene();
		}

		~Game() {}

		Scene* currentScene_;

		void setupInputs();

};

#endif // !GAME_HPP
