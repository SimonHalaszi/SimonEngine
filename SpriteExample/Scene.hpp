#ifndef SCENE_HPP
#define SCENE_HPP

#include <IrrKlang/irrKlang.h>

#include <string>

#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "GameObject.hpp"

// Scene Class

class Scene {
	public:
		Scene(int updatesPerSecond = 244, int framesPerSeconds = 244, int animationUpdatesPerSecond = 10)
			: updatesPerSecond_(updatesPerSecond), 
			framesPerSeconds_(framesPerSeconds), 
			animationUpdatesPerSecond_(animationUpdatesPerSecond) {
			soundEngine_ = irrklang::createIrrKlangDevice();

			if (!soundEngine_) {
				std::cout << "ERROR: Failed to create irrKlang device!\n";
			}

			animationFrame_ = 0;
			deltaTime_ = (1.0f / updatesPerSecond_);
		}

		virtual ~Scene() {
			if (soundEngine_) {
				soundEngine_->drop();
			}
		}

		virtual void init() {
			for (const auto& gameObject : gameObjects_) {
				gameObject->init();
			}
		};

		virtual void draw() {
			for (const auto& gameObject : gameObjects_) {
				gameObject->draw();
			}
		}

		virtual void update() {
			for (auto* gameObject : gameObjects_) {
				gameObject->update();
			}

			for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ) {
				if (!(*it)->isAlive()) {
					(*it)->onDestruction();
					delete* it;
					it = gameObjects_.erase(it);
				}
				else {
					++it;
				}
			}
		}

		virtual void procSpecialKeys(int key, int x, int y) = 0;
		virtual void procSpecialKeysUp(int key, int x, int y) = 0;
		virtual void procKeys(unsigned char key, int x, int y) = 0;
		virtual void procMouse(int button, int state, int x, int y) = 0;

		int getUpdateSpeed() const { return updatesPerSecond_; }
		int getFrameSpeed() const { return framesPerSeconds_; }
		int getAnimationUpdateSpeed() const { return animationUpdatesPerSecond_; }

		void incrementAnimationFrame() { ++animationFrame_; }

	protected:
		// Asset Registries
		TextureRegistry textures_;
		SpriteRegistry sprites_;
		SpriteSheetRegistry spriteSheets_;

		// Scene Game Objects
		std::vector<GameObject*> gameObjects_;

		// Sound Engine
		irrklang::ISoundEngine* soundEngine_;

		// Update Tick Speeds
		int updatesPerSecond_;
		int framesPerSeconds_;
		int animationUpdatesPerSecond_;

		unsigned int animationFrame_;
		float deltaTime_;
};

#endif // !GAME_HPP
