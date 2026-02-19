#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <string>
#include <memory>

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
		
		Scene* getCurrentScene() { return currentScene_.get(); }

		// Public only so buffer functions can call them
		
		void frameTimer(int v);

		void updateTimer(int v);

		void animationTimer(int v);

		void changeScene(std::unique_ptr<Scene> newScene) { currentScene_ = std::move(newScene); currentScene_->init(); }

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		Game() : currentScene_(std::make_unique<MainScene>()) {}

		~Game() {}

		std::unique_ptr<Scene> currentScene_;

		void setupInputs();

};

#endif // !GAME_HPP
