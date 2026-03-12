#ifndef SCENE_HPP
#define SCENE_HPP

#include <IrrKlang/irrKlang.h>

#include <string>
#include <memory>

#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "GameObject2D.hpp"

// Scene Class

class Scene {
	public:
		Scene(int updatesPerSecond = 244, int framesPerSeconds = 244, int animationUpdatesPerSecond = 10)
			: updatesPerSecond_(updatesPerSecond), 
			framesPerSeconds_(framesPerSeconds), 
			animationUpdatesPerSecond_(animationUpdatesPerSecond) {
			soundEngine_ = irrklang::createIrrKlangDevice();
		}

		virtual ~Scene() {
			if (soundEngine_) {
				soundEngine_->drop();
			}
		}

		void addRootGameObject2D(std::unique_ptr<GameObject2D> gameObject) {
			if (!gameObject) {
				return;
			}

			rootObjects_.push_back(std::move(gameObject));

			rootObjects_.back()->rootOnStart();
		}

		void sceneInit() {
			init();
		}

		void sceneDeInit() {
			deInit();
		}

		void sceneDraw() const {
			draw();
			for (auto& rootObject : rootObjects_) {
				rootObject->rootDraw();
			}
		}
		
		void sceneUpdate() {
			update();
			for (auto it = rootObjects_.begin(); it != rootObjects_.end();) {
				GameObject2D* rO = it->get();
				
				rO->rootUpdate();

				if (rO->isAlive()) {
					++it;
				}
				else {
					rO->rootOnDestruction();
					it = rootObjects_.erase(it);
				}
			}
		}

		int getUpdateSpeed() const { return updatesPerSecond_; }
		int getFrameSpeed() const { return framesPerSeconds_; }
		int getAnimationUpdateSpeed() const { return animationUpdatesPerSecond_; }

		void isDrawing(bool willDraw) { isDrawing_ = willDraw; }
		void isUpdating(bool willUpdate) { isUpdating_ = willUpdate; }
		void isUpdatingAnimations(bool willUpdateAnimations) { isUpdatingAnimations_ = willUpdateAnimations; }

		bool isDrawing() const { return isDrawing_; }
		bool isUpdating() const { return isUpdating_; }
		bool isUpdatingAnimations() const { return isUpdatingAnimations_; }

		void incrementAnimationFrame() { ++animationFrame_; }
		int getAnimationFrame() const { return animationFrame_; }

	protected:
		// Scene specific functionalities handled here. GameObjects are updated AUTOMATICALLY based on per GameObject logic
		virtual void init() {}
		virtual void deInit() {}
		virtual void draw() const {} // Scene specific drawing (Stuff not attached to GameObjects)
		virtual void update() {} // Scene specific updating (Stuff not attached to GameObjects)

		// Scene root GameObjects
		std::vector<std::unique_ptr<GameObject2D>> rootObjects_;

		// Sound Engine
		irrklang::ISoundEngine* soundEngine_;

		bool isDrawing_ = true, isUpdating_ = true, isUpdatingAnimations_ = true;

		// Update Tick Speeds
		int updatesPerSecond_;
		int framesPerSeconds_;
		int animationUpdatesPerSecond_;
		int animationFrame_ = 0;
};

#endif // !GAME_HPP
