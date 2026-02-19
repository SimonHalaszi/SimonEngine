#ifndef SCENE_HPP
#define SCENE_HPP

#include <IrrKlang/irrKlang.h>

#include <string>

#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"

// Scene Class

class Scene {
	public:
		Scene(int updatesPerSecond = 244, int framesPerSeconds = 244, int animationUpdatesPerSecond = 10)
			: updatesPerSecond_(updatesPerSecond), 
			framesPerSeconds_(framesPerSeconds), 
			animationUpdatesPerSecond_(animationUpdatesPerSecond) {
			soundEngine_ = irrklang::createIrrKlangDevice();
			animationFrame_ = 0;
		}

		virtual ~Scene() {
			if (soundEngine_) {
				soundEngine_->drop();
			}
		}

		virtual void init() = 0;

		virtual void draw() = 0;

		virtual void update() = 0;

		virtual void procSpecialKeys(int key, int x, int y) = 0;
		virtual void procSpecialKeysUp(int key, int x, int y) = 0;
		virtual void procKeys(unsigned char key, int x, int y) = 0;
		virtual void procMouse(int button, int state, int x, int y) = 0;

		int getUpdateSpeed() const { return updatesPerSecond_; }
		int getFrameSpeed() const { return framesPerSeconds_; }
		int getAnimationUpdateSpeed() const { return animationUpdatesPerSecond_; }

		void incrementAnimationFrame() { ++animationFrame_; }

	protected:
		// Registries
		TextureRegistry textures_;
		SpriteRegistry sprites_;
		SpriteSheetRegistry spriteSheets_;

		// Sound Engine
		irrklang::ISoundEngine* soundEngine_;

		// Update Tick Speeds
		int updatesPerSecond_;
		int framesPerSeconds_;
		int animationUpdatesPerSecond_;

		unsigned int animationFrame_;
};

#endif // !GAME_HPP
