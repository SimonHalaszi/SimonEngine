#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <memory>

#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "GameObject2D.hpp"
#include "CollisionManager.hpp"
#include "SoundManager.hpp"

// Scene Class

class Scene {
	public:
		Scene(int updatesPerSecond = 244, int framesPerSeconds = 244, int animationUpdatesPerSecond = 10)
			: updatesPerSecond_(updatesPerSecond), 
			framesPerSeconds_(framesPerSeconds), 
			animationUpdatesPerSecond_(animationUpdatesPerSecond) {
		}

		virtual ~Scene() {}

		void addRootGameObject2D(std::unique_ptr<GameObject2D> gameObject) {
			if (!gameObject) {
				return;
			}

			rootObjects_.push_back(std::move(gameObject));

			rootObjects_.back()->rootOnStart();
		}

		void sceneInit() {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			init();
		}

		void sceneDeInit() {
			rootObjects_.clear();

			CollisionManager::getInstance().clear();
			TextureRegistry::getInstance().clearRegistry();
			SpriteRegistry::getInstance().clearRegistry();
			SpriteSheetRegistry::getInstance().clearRegistry();

			SoundManager::getInstance().clearSoundManager();

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

			for (auto& rootObject : rootObjects_) {
				rootObject->rootUpdate();
			}

			for (auto it = rootObjects_.begin(); it != rootObjects_.end();) {
				GameObject2D* rO = it->get();

				if (!rO->isAlive()) {
					rO->rootOnDestruction();
					it = rootObjects_.erase(it);
				}
				else {
					++it;
				}
			}

			CollisionManager::getInstance().checkAllCollisions();
		}

		int getUpdateSpeed() const { return updatesPerSecond_; }
		int getFrameSpeed() const { return framesPerSeconds_; }
		int getAnimationUpdateSpeed() const { return animationUpdatesPerSecond_; }

		void willDraw(bool willDraw) { isDrawing_ = willDraw; }
		void willUpdate(bool willUpdate) { isUpdating_ = willUpdate; }
		void willUpdateAnimations(bool willUpdateAnimations) { isUpdatingAnimations_ = willUpdateAnimations; }
		void setPauseFlag(bool pauseFlag) { pauseFlag_ = pauseFlag; }

		bool isDrawing() const { return isDrawing_; }
		bool isUpdating() const { return isUpdating_; }
		bool isUpdatingAnimations() const { return isUpdatingAnimations_; }
		bool isPauseFlagged() const { return pauseFlag_; }

		void incrementAnimationFrame() { ++animationFrame_; }
		int getAnimationFrame() const { return animationFrame_; }

		void incrementUpdateFrame() { ++updateFrame_; }
		int getUpdateFrame() const { return updateFrame_; }

	protected:
		// Scene specific functionalities handled here. GameObjects are updated AUTOMATICALLY based on per GameObject logic
		virtual void init() {} // Scene specific init (Stuff not attached to GameObjects)
		virtual void deInit() {} // Scene specific deInit (Stuff not attached to GameObjects)
		virtual void draw() const {} // Scene specific drawing (Stuff not attached to GameObjects)
		virtual void update() {} // Scene specific updating (Stuff not attached to GameObjects)

		// Scene root GameObjects
		std::vector<std::unique_ptr<GameObject2D>> rootObjects_;

		bool isDrawing_ = true, isUpdating_ = true, isUpdatingAnimations_ = true, pauseFlag_ = false;

		// Update Tick Speeds
		int updatesPerSecond_;
		int framesPerSeconds_;
		int animationUpdatesPerSecond_;
		int animationFrame_ = 0;
		int updateFrame_ = 0;
};

#endif // !GAME_HPP
