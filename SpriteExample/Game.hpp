#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <string>
#include <memory>

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
		void changeScene(std::unique_ptr<Scene> newScene) { currentScene_ = std::move(newScene); currentScene_->init(); }

		// Public only so buffer functions can call them
		void frameTimer(int v);
		void updateTimer(int v);
		void animationTimer(int v);

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		Game() : currentScene_(std::make_unique<MainScene>()) {}

		~Game() {}

		void setupInputs();

		std::unique_ptr<Scene> currentScene_;
};

#endif
