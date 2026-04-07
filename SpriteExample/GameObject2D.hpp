#ifndef GAME_OBJECT2D_HPP
#define GAME_OBJECT2D_HPP

#include "Utilities.hpp"
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>

class GameObject2D {
	public:
		GameObject2D() {}
		virtual ~GameObject2D() {}

		// Users really shouldnt override rootOnStart/Destruction unless they know what they are doing
		virtual void rootOnStart(); // Runs when attached to scene
		void rootUpdate(); // Runs once per update of the Scene
		void rootDraw(); // Runs once per frame update of the Scene
		virtual void rootOnDestruction(); // Runs after right before being unattached from scene

		bool isAlive() const { return isAlive_; }
		void destroy() { isAlive_ = false; } // Call this function or just change isAlive to delete GameObject

		bool hasParent() const { return parent_; }
		bool isAttachedToScene() const { return isAttachedToScene_; }
		bool isWorldTransformOutDated() const { return isWorldTransformOutDated_; }

		const Transform2D& getLocalTransform() const { return localTransform_; }
		const Transform2D& getWorldTransform() const { return worldTransform_; }

		void setPosition(Vector2D pos) { localTransform_.position = pos; outDateWorldTransform(); }
		void setScale(Vector2D scale) { localTransform_.scale = scale; outDateWorldTransform(); }
		void setRotation(float rotation) { localTransform_.rotation = rotation; outDateWorldTransform(); }

		void outDateWorldTransform();
		void updateWorldTransform();

		void attachChild(std::unique_ptr<GameObject2D> child); // Attaches a child to a GameObject

		std::string getTag() const { return tag_; }
		std::string getName() const { return name_; }
	
	protected:
		virtual void onStart() {} // Runs when attached to scene
		virtual void update() {} // Runs once per update of the Scene
		virtual void draw() {} // Runs once per frame update of the Scene
		virtual void onDestruction() {} // Runs after right before being unattached from scene

		GameObject2D* parent_ = nullptr;
		
		std::string tag_;
		std::string name_;
		Transform2D localTransform_;

		bool isAttachedToScene_ = false;

	private:
		void init(); // Runs to attach to scene
		void deInit(); // Runs to unattch from scene
		
		bool isWorldTransformOutDated_ = true;
		Transform2D worldTransform_;
		bool isAlive_ = true;

		std::vector<std::unique_ptr<GameObject2D>> children_ = {};
};

#endif