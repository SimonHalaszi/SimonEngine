#include "GameObject2D.hpp"

void GameObject2D::rootOnStart() {
	isAttachedToScene_ = true;
	onStart();

	isWorldTransformOutDated_ = true;

	for (auto& child : children_) {
		child->rootOnStart();
	}
}

// Runs once per update of the Scene
void GameObject2D::rootUpdate() {
	if (isWorldTransformOutDated_ || (parent_ && parent_->isWorldTransformOutDated_)) {
		updateWorldTransform();
	}
	
	update();

	// Iterate with index so we can safely remove children that self-destruct during update.
	for (auto it = children_.begin(); it != children_.end();) {
		GameObject2D* child = it->get();
		
		child->rootUpdate();

		if (child->isAlive()) {
			++it;
		}
		else {
			child->rootOnDestruction();
			it = children_.erase(it);
		}
	}
}

void GameObject2D::outDateWorldTransform() {
	isWorldTransformOutDated_ = true;

	for (auto& child : children_) {
		child->outDateWorldTransform();
	}
}

// Runs once per frame update of the Scene
void GameObject2D::rootDraw() {
	draw();

	for (auto& child : children_) {
		child->rootDraw();
	}
}

// Runs at the end of a frame after destroy in Scene update
void GameObject2D::rootOnDestruction() {
	isAttachedToScene_ = false;
	onDestruction();

	for (auto& child : children_) {
		child->rootOnDestruction();
	}
}

// Recalculate world transforms
void GameObject2D::updateWorldTransform() {
	if (parent_) {
		worldTransform_ = composeTransforms(parent_->getWorldTransform(), localTransform_);
	}
	else {
		worldTransform_ = localTransform_;
	}

	isWorldTransformOutDated_ = false;

	for (auto& child : children_) {
		child->updateWorldTransform();
	}
}

void GameObject2D::attachChild(std::unique_ptr<GameObject2D> child) {
	if (!child) {
		return;
	}

	// Simplified: caller must create the child and it must not already have a parent.
	if (child->parent_) {
		throw std::runtime_error("GameObject2D::attachChild : child already has a parent");
	}

	child->parent_ = this;
	children_.push_back(std::move(child));

	// If this parent is already attached to a Scene, initialize the newly attached child subtree immediately.
	if (isAttachedToScene_) {
		children_.back()->rootOnStart();
	}
}