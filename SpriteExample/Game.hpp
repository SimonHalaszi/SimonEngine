#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <string>
#include <memory>

#include "Scene.hpp"

#include "ArchiveScene.hpp"
#include "TemplateScene.hpp"

// Game Class

// The Game class, with a Singleton the SEXIEST design pattern
class Game {
	public:
		static Game& getInstance() {
			static Game instance;
			return instance;
		}

		void init();
		
		const Scene* getCurrentScene() { return currentScene_.get(); }
		void changeScene(std::unique_ptr<Scene> newScene);

		// Public only so buffer functions can call them
		void frameTimer(int v);
		void updateTimer(int v);
		void animationTimer(int v);

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		Game() : currentScene_(nullptr) {}

		Scene* getCurrentSceneNonConst() { return currentScene_.get(); }

		~Game() {}

		std::unique_ptr<Scene> currentScene_;
		std::unique_ptr<Scene> pendingScene_;
};

#endif
